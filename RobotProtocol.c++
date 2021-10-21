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

    this->ultrasonicReceiverPin = 12;
    this->ultrasonicTriggerPin = 11;

    this -> leftInfraredPin = 7;
    this -> rightInfraredPin = 8;

    pinMode(leftSpeedWheelPin, OUTPUT);
    pinMode(leftForwardWheelPin, OUTPUT);
    pinMode(leftBackwardWheelPin, OUTPUT);

    pinMode(rightSpeedWheelPin, OUTPUT);
    pinMode(rightForwardWheelPin, OUTPUT);
    pinMode(rightBackwardWheelPin, OUTPUT);

    pinMode(ultrasonicReceiverPin, INPUT);
    pinMode(ultrasonicTriggerPin, OUTPUT);

    pinMode(leftInfraredPin, INPUT);
    pinMode(rightInfraredPin, INPUT);

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

void RobotProtocol::moveBackward(int distance)
{
    rightWheelBackward();
    leftWheelBackward();

    while ((this->distance) < distance)
    {
        //do nothing
    }
    stop();
    this->distance = 0;
}

void RobotProtocol::incrementDistance()
{
    (this->distance)++;
}

void RobotProtocol::setSpeed(char speed)
{
    this->leftWheelSpeed = speed;
    this->rightWheelSpeed = speed;
    analogWrite(rightSpeedWheelPin, rightWheelSpeed);
    analogWrite(leftSpeedWheelPin, leftWheelSpeed);
}

void RobotProtocol::rotateLeft(int angle)
{
    int milis = angle / 45; // 1ms = 45 degrees

    leftWheelBackward();
    rightWheelForward();
    delay(milis);
    stop();
}

void RobotProtocol::rotateRight(int angle)
{
    int milis = angle / 45; // 1ms = 45 degrees

    leftWheelForward();
    rightWheelBackward();
    delay(milis);
    stop();
}

void RobotProtocol::getSonarValue()
{
    digitalWrite(ultrasonicTriggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicTriggerPin, HIGH);
    delayMicroseconds(10); //high level signal to control the pin TRIG to trigger distance measurement
    digitalWrite(ultrasonicTriggerPin, LOW);
    float signalTime = pulseIn(ultrasonicReceiverPin, HIGH);
    float distance = (signalTime * 340) / 2; //(signal_time * speed_of_sound) / 2

    Serial.print("Distance:"); //print distance
    Serial.print(distance);
    Serial.print("cm\n\n");
}

void RobotProtocol::getInfraredSensorValue()
{
    int leftSensorValue = analogRead(leftInfraredPin);
    int rightSensorvalue = analogRead(rightInfraredPin);

    Serial.print("Left pin distance:"); //print distance
    Serial.print(leftSensorValue);
    Serial.print("cm\n\n");

    Serial.print("Right pin distance:"); //print distance
    Serial.print(rightInfraredPin);
    Serial.print("cm\n\n");
}