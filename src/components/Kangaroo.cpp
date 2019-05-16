#include "Kangaroo.h"


Kangaroo::Kangaroo(string portName) {
    m_isOpened = (m_serialPortOutput.open(portName.c_str(), 9600) != -1);
    m_init = init();
}


bool Kangaroo::isOperational() {
    if (!m_isOpened)
        LOG_F(ERROR, "Port is not opened");
    if (!m_init)
        LOG_F(ERROR, "Could not init the Kangaroo");
    return m_isOpened && m_init;
}

bool Kangaroo::init() {
    bool retour = false;
    if (m_isOpened) {
        retour = true;
        start(drive);
        retour = retour && m_serialPortOutput.puts("D, UNITS 628 mm = 160000 lines\r\n");
        retour = retour && m_serialPortOutput.puts("D,p0s0\r\n");
        start(turn);
        retour = retour && m_serialPortOutput.puts("T, UNITS 360 degrees = 246400 lines\r\n");
        retour = retour && m_serialPortOutput.puts("T,p0s0\r\n");
    }
    return retour;
}

bool Kangaroo::start(mode m) {
    current_mode = m;
    return putCommand((char) m, ",start\r\n");
}

bool Kangaroo::startStraightMove(int distance, int v) {
    bool success = false;
    start(drive);
    if (m_isOpened) {
        string command = "D,p" + std::to_string(distance) + "s" + std::to_string(v) + "\r\n";
        success = m_serialPortOutput.puts(command.c_str());
    }
    LOG_IF_F(INFO, success, "starting straight move ; goal : distance = %d units, speed = %d", distance, v);
    LOG_IF_F(ERROR, !success, "could not start straight move ! (goal : distance = %d units, speed = %d)", distance, v);

    return success;
}

bool Kangaroo::startTurnMove(int angle, int v) {
    bool retour = false;
    start(turn);
    if (m_isOpened) {
        string commande = "T,p" + std::to_string(angle) + "s" + std::to_string(v) + "\r\n";
        retour = m_serialPortOutput.puts(commande.c_str());
    }
}

string Kangaroo::getRawPosition() {
    string commande;
    string reponse = "";
    char lastChar;

    if (m_isOpened) {
        commande = (char) current_mode;
        commande += ",getp\r\n";
        if (m_serialPortOutput.puts(commande.c_str())) {
            do {
                if (m_serialPortOutput.dataAvailable() != -1) {
                    m_serialPortOutput.getchar(&lastChar);
                    reponse += lastChar;
                }
            } while (lastChar != '\n');
        }
    }
    return reponse;
}

int Kangaroo::getPosition() {
    string rawPosition = getRawPosition();
    int position;

    try {
        position = stoi(rawPosition.substr(3));
    } catch (...) {
        LOG_F(ERROR, "could not convert raw kangaroo position (%s) to an int", rawPosition.c_str());
        throw;
    }

    return position;
}

bool Kangaroo::isMoveCompleted() {
    return getRawPosition()[2] == 'P';
}

// to remove ??

bool Kangaroo::putCommand(char mode, string cmd) {
    bool retour = false;
    string commande = "";
    if (m_isOpened) {
        commande += mode;
        commande += cmd;
        retour = m_serialPortOutput.puts(commande.c_str());
    }
    return retour;
}

bool Kangaroo::powerdown(mode m) { return putCommand((char) m, ",powerdown\r\n"); }

void Kangaroo::downZero() {
    if (m_isOpened) {
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

int Kangaroo::getSpeed(mode m, int &speed) {
    string reponse = "";
    string tempo = "";
    char lastChar;
    unsigned int errorCount = 0;
    int codeErreur = -1;

    if (m_isOpened) {
        if (putCommand((char) m, ",getp\r\n")) {
            do {
                if (m_serialPortOutput.dataAvailable() != -1) {
                    m_serialPortOutput.getchar(&lastChar);
                    reponse += lastChar;
                }
            } while (lastChar != '\n' && errorCount++ < 100);
            if (reponse[2] != 'E') {
                for (int i = 3; i < reponse.length() - 2; i++) {
                    tempo += reponse[i];
                }
                speed = std::stoi(tempo);
            } else {
                tempo += reponse[2];
                tempo += reponse[3];
                codeErreur = std::stoi(tempo);
            }
        }
    }
    return codeErreur;
}

int Kangaroo::getPositionMax(mode m, int &positionMax) {
    char commande[100] = {0};
    char reponse[100] = {0};
    int codeErreur = 0;
    char tempo[10] = {0};
    int nb = 0;
    char cm = (char) m;

    if (m_isOpened) {

        strcpy(commande, &cm);
        strcat(commande, ",getmax\r\n");
        if (m_serialPortOutput.puts(commande)) {
            unsigned int i = 0;
            do {
                nb = m_serialPortOutput.dataAvailable();
                if (nb != -1) {
                    m_serialPortOutput.getchar(&reponse[i]);
                    i++;
                }
            } while (reponse[i - 1] != '\n' && i < 99);
            reponse[i] = '\0';
            if (reponse[2] != 'E') {
                int j = 0;
                for (i = 3; i < strlen(reponse) - 2; i++) {
                    tempo[j++] = reponse[i];
                }
                positionMax = atoi(tempo);
            } else {
                tempo[0] = reponse[2];
                tempo[1] = reponse[3];
                codeErreur = atoi(tempo);
            }
        }

    }
    return codeErreur;


}

int Kangaroo::getPositionMin(mode m, int &positionMin) {
    char commande[100] = {0};
    char reponse[100] = {0};
    int codeErreur = 0;
    char tempo[10] = {0};
    int nb = 0;
    char cm = (char) m;

    if (m_isOpened) {

        strcpy(commande, &cm);
        strcat(commande, ",getmin\r\n");
        if (m_serialPortOutput.puts(commande)) {
            unsigned int i = 0;
            do {
                nb = m_serialPortOutput.dataAvailable();
                if (nb != -1) {
                    m_serialPortOutput.getchar(&reponse[i]);
                    i++;
                }
            } while (reponse[i - 1] != '\n' && i < 99);
            reponse[i] = '\0';
            if (reponse[2] != 'E') {
                int j = 0;
                for (i = 3; i < strlen(reponse) - 2; i++) {
                    tempo[j++] = reponse[i];
                }
                positionMin = atoi(tempo);
            } else {
                tempo[0] = reponse[2];
                tempo[1] = reponse[3];
                codeErreur = atoi(tempo);
            }
        }

    }
    return codeErreur;


}

bool Kangaroo::forwardB(int distance, int v, bool verbose) {
    bool retour = false;
    start(drive);
    if (m_isOpened) {
        string commande = "D,p" + std::to_string((int) (distance)) + "s" + std::to_string(v) + "\r\n";
        retour = m_serialPortOutput.puts(commande.c_str());
    }

    bool moveCompleted;
    do {
        if (verbose)
            cout << getRawPosition() << endl;
        moveCompleted = isMoveCompleted();
    } while (!moveCompleted);
    return retour;
}

bool Kangaroo::turnB(int angle, int v, bool verbose) {
    bool retour = false;
    start(turn);
    if (m_isOpened) {
        string commande = "T,p" + std::to_string((int) (angle)) + "s" + std::to_string(v) + "\r\n";
        retour = m_serialPortOutput.puts(commande.c_str());
    }

    bool moveCompleted;
    do {
        if (verbose)
            cout << getRawPosition() << endl;
        moveCompleted = isMoveCompleted();
    } while (!moveCompleted);
    return retour;
}
