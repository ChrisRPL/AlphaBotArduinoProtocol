#include "RobotProtocol.h"

RobotProtocol robot;
char command;
int commandArgument;

void setup()
{
    robot = RobotProtocol();
}

void loop()
{
    if (Serial.available() > 0)
    {
        command = Serial.peek();
        commandArgument = Serial.parseInt();

        switch (command)
        {
        case 'm':
            if (commandArgument > 0)
            {
                robot.moveForward(commandArgument);
            }
            else
                robot.moveBackward(commandArgument);
            break;
        case 'r':
            if (commandArgument > 0)
            {
                robot.rotateRight(commandArgument);
            }
            else
                robot.rotateLeft(commandArgument);
            break;
        case 'v':
            if (commandArgument * robot.leftWheelSpeed < 0)
            {
                Serial.print("Please use speed value of the same sign as robot speed value\n\n");
            }
            else
                robot.setSpeed(commandArgument);
            break;
        case 's':
            robot.stop();
            break;
        case 'b':
            robot.getSonarValue();
            break;
        case 'i':
            robot.getInfraredSensorValue();
            break;
        default:
            break;
        }
    }
}
