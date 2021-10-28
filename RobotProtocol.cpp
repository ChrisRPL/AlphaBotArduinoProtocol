#include "RobotProtocol.h"

int RobotProtocol::leftWheelSpeed = 255;
int RobotProtocol::rightWheelSpeed = 255;
int RobotProtocol::distance = 0;

RobotProtocol::RobotProtocol()
{
    this->rightSpeedWheelPin = 6;
    this->rightForwardWheelPin = A3;
    this->rightBackwardWheelPin = A2;

    this->leftSpeedWheelPin = 5;
    this->leftForwardWheelPin = A0;
    this->leftBackwardWheelPin = A1;

    this->ultrasonicReceiverPin = 12;
    this->ultrasonicTriggerPin = 11;

    this->leftInfraredPin = 7;
    this->rightInfraredPin = 8;

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

    attachInterrupt(digitalPinToInterrupt(3), incrementDistance, FALLING);
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
        executeCommand();
    }
    stop();
    this->distance = 0;
}

void RobotProtocol::moveBackward(int distance)
{
    rightWheelBackward();
    leftWheelBackward();

    distance *= -1;

    while ((this->distance) < distance)
    {
        executeCommand();
    }
    stop();
    this->distance = 0;
}

void RobotProtocol::incrementDistance()
{
    (RobotProtocol::distance)++;
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
    delay(500);
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
    float distance = (signalTime) / 58; //(signal_time * speed_of_sound) / 2

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

void RobotProtocol::stop()
{
    leftWheelStop();
    rightWheelStop();
}

void RobotProtocol::executeCommand()
{
    char command;
    int commandArgument;

    if (Serial.available() > 0)
    {
        command = Serial.peek();
        commandArgument = Serial.parseInt();

        switch (command)
        {
        case 'm':
            if (commandArgument > 0)
            {
                moveForward(commandArgument);
            }
            else
                moveBackward(commandArgument);
            break;
        case 'r':
            if (commandArgument > 0)
            {
                rotateRight(commandArgument);
            }
            else
                rotateLeft(commandArgument);
            break;
        case 'v':
            if (commandArgument * leftWheelSpeed < 0)
            {
                Serial.print("Please use speed value of the same sign as robot speed value\n\n");
            }
            else
                setSpeed(commandArgument);
            break;
        case 's':
            stop();
            break;
        case 'b':
            getSonarValue();
            break;
        case 'i':
            getInfraredSensorValue();
            break;
        default:
            break;
        }
    }
}