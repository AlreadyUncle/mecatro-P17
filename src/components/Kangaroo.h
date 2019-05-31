#ifndef KANGAROO_H
#define KANGAROO_H

#include "SerialPort.h"
#include <stdlib.h>
#include "loguru.hpp"

enum mode {
    moteur1 = 0x31, moteur2 = 0x32, drive = 0x44, turn = 0x54
};

enum vitesse {
    km0 = 0,
    km05 = 200,
    km1 = 400,
    km15 = 600,
    km2 = 800,
    km25 = 1000,
    km3 = 1200,
    km35 = 1400,
    km4 = 1600,
    km45 = 1800,
    km5 = 2000
};

class Kangaroo {

public:
    Kangaroo(string portName);

    bool isOperational();

    /**
     * Send a command to the Kangaroo to start a straight move, forward or backward depending on the sign of `distance`.
     * @param distance : distance to do, in units !
     * @param v : speed (in units/s ?)
     * @return If sending the command was a success or not
     */
    bool startStraightMove(int distance, int v);

    bool startTurnMove(int angle, int v);

    /**
     *
     * @return The current distance traveled, in units
     */
    int getPosition();

    /**
     *
     * @return True is the `getp` command returns a string starting with a capital P
     */
    bool isMoveCompleted();

    /**
     *
     * @return A string with channel number, a comma, character p or P, position in units,
     * followed by a return and a newline
     */
    string getRawPosition();

    /**
     * Go to a pos 0 at speed 0, in drive then in turn mode
     */
    void stop();

    int getPositionMax(mode m, int &positionMax); // retourne le range de position maximal
    int getPositionMin(mode m, int &positionMin); //retourne le range de position minimal
    int getSpeed(mode m, int &speed); //retourne la vitesse

    // to refactor ?
    bool forwardB(int distance, int v, bool verbose = false);

    bool setVitesse(vitesse v);

    bool turnB(int angle, int v, bool verbose = false);

    // Turn off the Sabertooth, to go free wheel. If you wish to stop the robot and resume movement later,
    // prefer starting a move to position 0, with speed 0
    bool powerdown(mode m);

    void downZero();

private:
    bool init();

    bool start(mode m);

    bool putCommand(char mode, string cmd);


    mode current_mode;
    SerialPort m_serialPortOutput;
    bool m_isOpened;
    bool m_init;
};

#endif // KANGAROO_H
