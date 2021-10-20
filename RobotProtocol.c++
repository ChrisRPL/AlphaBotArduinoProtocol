#include "RobotProtocol.h"

char RobotProtocol::leftWheelSpeed = 255;
char RobotProtocol::rightWheelSpeed = 255;
int RobotProtocol::distance = 0;

RobotProtocol::RobotProtocol()
{
    this->rightSpeedWheelPin = 6;
    this->rightForwardWheelPin = A3;
    this->rightBackwardWheelPin = A2;

    this->leftSpeedWheelPin = 6;
    this->leftForwardWheelPin = A0;
    this->leftBackwardWheelPin = A1;

    pinMode(leftSpeedWheelPin, OUTPUT);
    pinMode(leftForwardWheelPin, OUTPUT);
    pinMode(leftBackwardWheelPin, OUTPUT);

    pinMode(rightSpeedWheelPin, OUTPUT);
    pinMode(rightForwardWheelPin, OUTPUT);
    pinMode(rightBackwardWheelPin, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(rightBackwardWheelPin), incrementDistance, FALLING);
}