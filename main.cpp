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
    robot.executeCommand();
}
