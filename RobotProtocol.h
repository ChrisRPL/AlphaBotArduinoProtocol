class RobotProtocol
{
public:
    RobotProtocol();
    void moveForward(int distance);
    void moveBackward(int distance);
    void rotateRight(int angle);
    void rotateLeft(int angle);
    void stop();
    void incrementDistance();
    void setSpeed(char speed);
    void getSonarValue();
    void getInfraredSensorValue();

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

    static char leftWheelSpeed, rightWheelSpeed;
    static int distance;

    void leftWheelForward();
    void leftWheelBackward();
    void leftWheelStop();
    void rightWheelForward();
    void rightWheelBackward();
    void rightWheelStop();
}