#include "RobotProtocol.h"

RobotProtocol robot = RobotProtocol();
char command;
int commandArgument;

void setup()
{
    // nothing to setup
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
            robot.setSpeed(commandArgument);

            if (commandArgument > 0)
            {
                /* code */
            }
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
