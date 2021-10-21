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

void RobotProtocol::leftWheelForward()
{
    analogWrite(leftSpeedWheelPin, leftWheelSpeed);
    digitalWrite(leftForwardWheelPin, HIGH);
    digitalWrite(leftBackwardWheelPin, LOW);
}

void RobotProtocol::leftWheelBackward()
{
    analogWrite(leftSpeedWheelPin, leftWheelSpeed);
    digitalWrite(leftForwardWheelPin, LOW);
    digitalWrite(leftBackwardWheelPin, HIGH);
}

void RobotProtocol::leftWheelStop()
{
    digitalWrite(leftSpeedWheelPin, LOW);
}

void RobotProtocol::rightWheelForward()
{
    analogWrite(rightSpeedWheelPin, rightWheelSpeed);
    digitalWrite(rightForwardWheelPin, HIGH);
    digitalWrite(rightBackwardWheelPin, LOW);
}

void RobotProtocol::rightWheelBackward()
{
    analogWrite(rightSpeedWheelPin, rightWheelSpeed);
    digitalWrite(rightForwardWheelPin, LOW);
    digitalWrite(rightBackwardWheelPin, HIGH);
}

void RobotProtocol::rightWheelStop()
{
    digitalWrite(rightSpeedWheelPin, LOW);
}

void RobotProtocol::moveForward(int distance)
{
    rightWheelForward();
    leftWheelForward();

    while ((this->distance) < distance)
    {
        //do nothing
    }
    stop();
    this->distance = 0;
}

void RobotProtocol::moveBackward(int distance) {
    rightWheelBackward();
    leftWheelBackward();

    while ((this->distance) < distance)
    {
        //do nothing
    }
    stop();
    this->distance = 0;
}

void RobotProtocol::incrementDistance() {
    (this -> distance)++;
}

void RobotProtocol::setSpeed(char speed) {
    this->LSpeed = LSpeed;
  this->RSpeed = RSpeed;
  analogWrite(RMotorSpeedPin,RSpeed);  
  analogWrite(LMotorSpeedPin,LSpeed);   
}