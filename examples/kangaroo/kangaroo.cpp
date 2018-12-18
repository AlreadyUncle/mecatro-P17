#include "kangaroo.h"


Ckangaroo::Ckangaroo(const char * portName)
{
    if(m_serialPortOutput.open(portName,9600)==-1)
        m_isOpened=false;
    else
        m_isOpened=true;
    m_init=init();
}


bool Ckangaroo::isOperationnal()
{
    return m_isOpened&&m_init;
}

bool Ckangaroo::init()
{
    bool retour=false;

    if(m_isOpened)
    {
        retour =true;
        start(drive);
            retour=retour&&m_serialPortOutput.puts("D, UNITS 628 mm = 160000 lines\r\n");
            retour=retour&&m_serialPortOutput.puts("D,p0s0\r\n");
        start(turn);
            retour=retour&&m_serialPortOutput.puts("T, UNITS 360 degrees = 246400 lines\r\n");
            retour=retour&&m_serialPortOutput.puts("T,p0s0\r\n");
    }
    return retour;
}


bool Ckangaroo::start(mode m)
{
    bool retour=false;
    char cm;
    char commande[100]={0};
    cm=(char)m;
    if(m_isOpened)

    {
        strcpy(commande,&cm);
        strcat(commande,",start\r\n");
        retour=m_serialPortOutput.puts((const char*)commande);
    }
    return retour;
}

bool Ckangaroo::powerdown(mode m)
{

    char commande[100]={0};
    char cm=(char)m;
    bool retour=false;

    if(m_isOpened)
    {
        strcpy(commande,&cm);
        strcat(commande,",powerdown\r\n");
        retour=m_serialPortOutput.puts(commande);
    }
    return retour;

}

void Ckangaroo::downZero()
{
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

bool Ckangaroo::setVitesse(vitesse v)
{

//    char commande[100]={0};
//    QString tempo;
//    bool retour  = false;
//    init();
//    start(drive);
//    if(m_isOpened)
//    {
//        strcpy(commande,"D,s");
//        tempo=QString::number(v);
//        strcat(commande,tempo.toStdString().c_str());
//        strcat(commande,"\r\n");
//        retour=m_serialPortOutput.puts(commande);
//
//    }
//
//    return  retour;
    return false;

}




bool Ckangaroo::forwardNB(int distance, int v, unite u)
{
    bool retour=false;
    start(drive);
    if(m_isOpened)
    {
        string commande="D,p"+std::to_string(u*distance)+"s"+std::to_string(v)+"\r\n";
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    return  retour; 
}

bool Ckangaroo::forwardB(int distance, int v, unite u){
    bool retour=false;
    start(drive);
    if(m_isOpened)
    {
        string commande="D,p"+std::to_string(u*distance)+"s"+std::to_string(v)+"\r\n";
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    
    char rep;
    do{
        rep=getState(drive);
    }while(rep!='P');
    return  retour;
}

bool Ckangaroo::turnB(int v, int angle){
    bool retour=false;
    start(turn);
    if(m_isOpened)
    {
        string commande="T,p"+std::to_string(angle*degre)+"s"+std::to_string(v)+"\r\n";
        retour=m_serialPortOutput.puts(commande.c_str());
    }
    
    char rep;
    do{
        rep=getState(turn);
    }while(rep!='P');
    return  retour;
}

bool Ckangaroo::turnNB(int v, int angle){
    bool retour=false;
    start(turn);
    if(m_isOpened)
    {
        string commande="T,p"+std::to_string(angle*degre)+"s"+std::to_string(v)+"\r\n";
        retour=m_serialPortOutput.puts(commande.c_str());
    }
}

//retourne un code erreur
//0 pas d'erreur
int Ckangaroo::getPosition(mode m,int &position)
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
        strcat(commande,",getp\r\n");
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
                position=atoi(tempo);
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


int Ckangaroo::getSpeed(mode m, int &speed)
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
        strcat(commande,",gets\r\n");
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
                speed=atoi(tempo);
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

char Ckangaroo::getState(mode m)
{
    string commande;
    string reponse="";
    char lastChar;
    
    if(m_isOpened)
    {
        commande=(char)m;
        commande+=",getp\r\n";
        if(m_serialPortOutput.puts(commande.c_str()))
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

