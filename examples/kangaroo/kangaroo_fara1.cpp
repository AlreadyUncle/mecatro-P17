#include "kangaroo.h"


Ckangaroo::Ckangaroo(const char * portName)
{


    if( m_serialPort.open(portName,9600)==-1)
        m_isOpened=false;
    else
        m_isOpened=true;

}

bool Ckangaroo::init()
{
    bool retour=false;

    if(m_isOpened)
    {

        start(drive);
            m_serialPort.puts("D, UNITS 628 mm = 160000 lines\r\n");
            m_serialPort.puts("D,p0s0\r\n");
        start(turn);
            m_serialPort.puts("T, UNITS 360 degrees = 246400 lines\r\n");
            m_serialPort.puts("T,p0s0\r\n");
    }
    return retour;
}


bool Ckangaroo::start(mode m)
{
    char commande[100]={0};
    bool retour=false;
    char cm;
    cm=(char)m; //?
    if(m_isOpened)
    {
        strcpy(commande,&cm);		//Copie la chaine cm dans commande
        strcat(commande,",start\r\n");		// " Rajoute ,start\r\n " à la fin de commande
        retour=m_serialPort.puts((const char*)commande);
    }
    return retour;
}

bool Ckangaroo::powerdown(mode m) // Eteindre le systeme 
{
    char commande[100]={0};
    char cm=(char)m;
    bool retour=false;

    if(m_isOpened)
    {
        strcpy(commande,&cm);
        strcat(commande,",powerdown\r\n");
        retour=m_serialPort.puts(commande);
    }
    return retour;

}

void Ckangaroo::downZero()
{


    if(m_isOpened)
    {

        start(moteur1);
            m_serialPort.puts("1,home\r\n");
        start(moteur2);
            m_serialPort.puts("2,home\r\n");
        start(drive);
            m_serialPort.puts("D,p0s0\r\n");
        start(turn);
            m_serialPort.puts("T,p0s0\r\n");
    }

}

bool Ckangaroo::setVitesse(vitesse v)
{

    char commande[100]={0};
    QString tempo;
    bool retour  = false;
    init();
    start(drive);
    if(m_isOpened)
    {
        strcpy(commande,"D,s");
        tempo=QString::number(v);
        strcat(commande,tempo.toStdString().c_str());
        strcat(commande,"\r\n");
        retour=m_serialPort.puts(commande);

    }

    return  retour;


}




bool Ckangaroo::allerEn(vitesse v, int distance, unite u)
{
    char commande[100]={0};
    QString tempo;
    bool retour  = false;
    init();
    start(drive);
    if(m_isOpened)
    {
        strcpy(commande,"D,p");// Copie " D,p " dans commande avec D signifiant avancer/reculer et p la position 
        distance=u*distance;
        tempo=QString::number(distance);
        strcat(commande,tempo.toStdString().c_str()); // Ajoute la donée pour la position 
        strcat(commande,"s"); // Ajoute s pour la vitesse

        tempo=QString::number(v);
        strcat(commande,tempo.toStdString().c_str());// Ajoute la donnée pour la vitesse
        strcat(commande,"\r\n");
        retour=m_serialPort.puts(commande); // Envoie de la commande 

    }

    return  retour;
    //droite = bas
    // gauche = haut
}

bool Ckangaroo::tourner(vitesse v, int angle)
{

    char commande[100]={0};
     QString tempo;
    bool retour  = true;

    init();
    start(turn);
    if(m_isOpened)
    {
        strcpy(commande,"T,p");		// Copie " T,p " dans commande avec T signifiant droite/gauche et p la position
        angle=angle*degre;
        tempo=QString::number(angle);
        strcat(commande,tempo.toStdString().c_str());		// Ajoute la donnée 
        strcat(commande,"s");		// Ajoute s pour l'angle ?

        tempo=QString::number(v);
        strcat(commande,tempo.toStdString().c_str()); //Ajoute la donée pour l'angle ?
        strcat(commande,"\r\n");
        retour=m_serialPort.puts(commande); // Envoie de la commande 
    }
    return  retour;


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
        if(m_serialPort.puts(commande))
        {
            unsigned int i=0;
            do
            {
                nb=m_serialPort.dataAvailable();// Regarde si il y a quelques chose à recuperer et sa taille
                if(nb!=-1)
                {
                    m_serialPort.getchar(&reponse[i]);
                    i++;
                }
            }while(reponse[i-1]!='\n' && i<99);// Recupere les caracteres tant que le derniers caracteres n'est pas "\n"
            reponse[i]='\0';
            if(reponse[2]!='E')// Si le deuxieme caratere est different de E c à dire pas d'erreur on recupere la vitesse
            {
                int j=0;
                for( i=3;i<strlen(reponse)-2;i++) // Recupere la chaine de caractere correspondant à la vitesse
                {
                    tempo[j++]=reponse[i];
                }
                position=atoi(tempo); // transforme la chaine de caractere en entier
            }
            else // On recupere le message d'erreur
            {
                tempo[0]=reponse[2];
                tempo[1]=reponse[3];
                codeErreur=atoi(tempo); // transforme la chaine de caractere en entier
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
        if(m_serialPort.puts(commande))
        {
            unsigned int i=0;
            do
            {
                nb=m_serialPort.dataAvailable();
                if(nb!=-1)
                {
                    m_serialPort.getchar(&reponse[i]);
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
        if(m_serialPort.puts(commande))
        {
            unsigned int i=0;
            do
            {
                nb=m_serialPort.dataAvailable();
                if(nb!=-1)
                {
                    m_serialPort.getchar(&reponse[i]);
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
        if(m_serialPort.puts(commande))
        {
            unsigned int i=0;
            do
            {
                nb=m_serialPort.dataAvailable();
                if(nb!=-1)
                {
                    m_serialPort.getchar(&reponse[i]);
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
   // m_serialPort.flush();

}
