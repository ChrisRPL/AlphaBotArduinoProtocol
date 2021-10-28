#include "Arduino.h"
class RobotProtocol
{
public:
RobotProtocol();
void moveForward(int distance);
void moveBackward(int distance);
void rotateRight(int angle);
void rotateLeft(int angle);
void stop();
static void incrementDistance();
void setSpeed(char speed);
void getSonarValue();
void getInfraredSensorValue();
	
static int leftWheelSpeed, rightWheelSpeed;

static int distance;

private:
    int rightSpeedWheelPin;
    int rightForwardWheelPin;
    int rightBackwardWheelPin;

    int leftSpeedWheelPin;
    int leftForwardWheelPin;
    int leftBackwardWheelPin;

    int ultrasonicTriggerPin;
    int ultrasonicReceiverPin;

    int leftInfraredPin;
    int rightInfraredPin;

    

    void leftWheelForward();
    void leftWheelBackward();
    void leftWheelStop();
    void rightWheelForward();
    void rightWheelBackward();
    void rightWheelStop();
};
