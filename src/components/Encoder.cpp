//
// Created by Alexandre Thomas on 2019-05-25.
//

#include "Encoder.h"


int Encoder::pinA = 8;
int Encoder::pinB = 9;
int Encoder::globalBarrelCounter= 0;
bool Encoder::pinASet;
bool Encoder::pinBSet;


Encoder::Encoder() {
    if (wiringPiSetup() == -1)
        LOG_F(ERROR, "Trying to initialize Encoder, could not initialise wiringPi : %s", strerror(errno));

    pinMode(pinA, INPUT);
    pinMode(pinB, INPUT);

    pullUpDnControl(pinA, PUD_UP);
    pullUpDnControl(pinB, PUD_UP);

    wiringPiISR(pinA, INT_EDGE_BOTH, &Encoder::changePinA);
    wiringPiISR(pinB, INT_EDGE_BOTH, &Encoder::changePinB);

    LOG_F(INFO, "Succeeded to initialise EncoderPinA %d", pinA);
    LOG_F(INFO, "Succeeded to initialise EncoderPinB %d", pinB);
}

// Interrupt on A changing state
void Encoder::changePinA() {
    // Test transition
    pinASet = digitalRead(pinA) == HIGH;
    // and adjust counter + if A leads B
    globalBarrelCounter += (pinASet != pinBSet) ? +1 : -1;
}

// Interrupt on B changing state
void Encoder::changePinB() {
    // Test transition
    pinBSet = digitalRead(pinB) == HIGH;
    // and adjust counter + if B follows A
    globalBarrelCounter += (pinASet == pinBSet) ? +1 : -1;
}

