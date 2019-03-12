#include "kangaroo.h"


Ckangaroo::Ckangaroo(string portName){
    m_isOpened=(m_serialPortOutput.open(portName.c_str(),9600)!=-1);
    m_init=init();
}


bool Ckangaroo::isOperationnal(){return m_isOpened&&m_init;}

bool Ckangaroo::init(){
    bool retour=false;
    if(m_isOpened)
    {
        retour=true;
        start(drive);
            retour=retour&&m_serialPortOutput.puts("D, UNITS 628 mm = 160000 lines\r\n");
            retour=retour&&m_serialPortOutput.puts("D,p0s0\r\n");
        start(turn);
            retour=retour&&m_serialPortOutput.puts("T, UNITS 360 degrees = 246400 lines\r\n");
            retour=retour&&m_serialPortOutput.puts("T,p0s0\r\n");
    }
    return retour;
}

bool Ckangaroo::putCommand(char mode,string cmd){
    bool retour=false;
    string commande="";
    if(m_isOpened){
        commande+=mode;
        commande+=cmd;
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    return retour;
}

bool Ckangaroo::start(mode m){
    m_current_mode=m;
    return putCommand((char)m,",start\r\n");}

bool Ckangaroo::powerdown(mode m){return putCommand((char)m,",powerdown\r\n");}

void Ckangaroo::downZero(){
    if(m_isOpened)
    {
        start(moteur1);
            m_serialPortOutput.puts("1,home\r\n");
        start(moteur2);
            m_serialPortOutput.puts("2,home\r\n");
        start(drive);
            m_serialPortOutput.puts("D,p0s0\r\n");
        start(turn);
            m_serialPortOutput.puts("T,p0s0\r\n");
    }
}

bool Ckangaroo::forwardNB(int distance, int v, bool verbose){
    bool retour=false;
    start(drive);
    if(m_isOpened)
    {
        string commande="D,p"+std::to_string((int)(distance*5.6666))+"s"+std::to_string(v)+"\r\n";
        if(verbose) cout << commande << endl;
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    return  retour; 
}

bool Ckangaroo::forwardB(int distance, int v, bool verbose){
    bool retour=false;
    start(drive);
    if(m_isOpened)
    {
        string commande="D,p"+std::to_string((int)(distance*5.6666))+"s"+std::to_string(v)+"\r\n";
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    do{
        if(verbose)
            cout << getPosition(drive) << endl;
    }while(!isIdle());
    return  retour;
}

bool Ckangaroo::turnB(int angle, int v, bool verbose){
    bool retour=false;
    start(turn);
    if(m_isOpened)
    {
        string commande="T,p"+std::to_string((int)(angle*13.89))+"s"+std::to_string(v)+"\r\n";
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    do{
        if(verbose)
            cout << getPosition(turn) << endl;
    }while(!isIdle());
    return  retour;
}

bool Ckangaroo::turnNB(int angle, int v, bool verbose){
    bool retour=false;
    start(turn);
    if(m_isOpened)
    {
        string commande="T,p"+std::to_string((int)(angle*13.89))+"s"+std::to_string(v)+"\r\n";
        if(verbose) cout << commande << endl;
        retour=m_serialPortOutput.puts(commande.c_str());
    }
}

int Ckangaroo::getSpeed(mode m){
    string tempo="";
    int codeErreur=-1;
    
    if(m_isOpened){
        string reponse=getPosition(m);
        if(reponse[2]!='E'){
            for(int i=3;i<reponse.length()-2;i++)
            {
                tempo+=reponse[i];
            }
            return std::stoi(tempo);
        }
        else{
            tempo+=reponse[2];
            tempo+=reponse[3];
            codeErreur=std::stoi(tempo);
        }
    }
    return codeErreur;
}

char Ckangaroo::getState(mode m){
    string reponse="";
    char lastChar;
    
    if(m_isOpened){
        if(putCommand((char)m,",getp\r\n"))
        {
            do
            {
                if(m_serialPortOutput.dataAvailable()!=-1)
                {
                    m_serialPortOutput.getchar(&lastChar);
                    reponse+=lastChar;
                }
            }while(lastChar!='\n');
        }
    }
    return reponse[2];
}

bool Ckangaroo::isIdle(){return(this->getState(m_current_mode)=='P');}

string Ckangaroo::getPosition(mode m)
{
    string reponse="";
    char lastChar;
    unsigned int errorCount=0;
    
    if(m_isOpened){
        if(putCommand((char)m,",getp\r\n")){
            do{
                if(m_serialPortOutput.dataAvailable()!=-1){
                    m_serialPortOutput.getchar(&lastChar);
                    reponse+=lastChar;
                }
            }while(lastChar!='\n' && errorCount++<100);
        }
    }
    return reponse;
}


int Ckangaroo::getPositionMax (mode m, int &positionMax)
{
    char commande[100]={0};
    char reponse[100]={0};
    int codeErreur=0;
    char tempo[10]={0};
    int nb=0;
    char cm=(char)m;

    if(m_isOpened)
    {

        strcpy(commande,&cm);
        strcat(commande,",getmax\r\n");
        if(m_serialPortOutput.puts(commande))
        {
            unsigned int i=0;
            do
            {
                nb=m_serialPortOutput.dataAvailable();
                if(nb!=-1)
                {
                    m_serialPortOutput.getchar(&reponse[i]);
                    i++;
                }
            }while(reponse[i-1]!='\n' && i<99);
            reponse[i]='\0';
            if(reponse[2]!='E')
            {
                int j=0;
                for( i=3;i<strlen(reponse)-2;i++)
                {
                    tempo[j++]=reponse[i];
                }
                positionMax=atoi(tempo);
            }
            else
            {
                tempo[0]=reponse[2];
                tempo[1]=reponse[3];
                codeErreur=atoi(tempo);
            }
        }

    }
    return codeErreur;



}


int Ckangaroo::getPositionMin (mode m , int &positionMin)
{
    char commande[100]={0};
    char reponse[100]={0};
    int codeErreur=0;
    char tempo[10]={0};
    int nb=0;
    char cm=(char)m;

    if(m_isOpened)
    {

        strcpy(commande,&cm);
        strcat(commande,",getmin\r\n");
        if(m_serialPortOutput.puts(commande))
        {
            unsigned int i=0;
            do
            {
                nb=m_serialPortOutput.dataAvailable();
                if(nb!=-1)
                {
                    m_serialPortOutput.getchar(&reponse[i]);
                    i++;
                }
            }while(reponse[i-1]!='\n' && i<99);
            reponse[i]='\0';
            if(reponse[2]!='E')
            {
                int j=0;
                for( i=3;i<strlen(reponse)-2;i++)
                {
                    tempo[j++]=reponse[i];
                }
                positionMin=atoi(tempo);
            }
            else
            {
                tempo[0]=reponse[2];
                tempo[1]=reponse[3];
                codeErreur=atoi(tempo);
            }
        }

    }
    return codeErreur;


}


Ckangaroo::~Ckangaroo()
{
   // m_serialPortOutput.flush();
}

