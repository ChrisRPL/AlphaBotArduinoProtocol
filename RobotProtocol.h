class RobotProtocol
{
public:
    RobotProtocol();
    void moveForward(int distance);
    void moveBackward(int distance);
    void rotateRight(int milis);
    void rotateLeft(int milis);
    void stop();
    void incrementDistance();
    void setSpeed(char speed);
    int getSonarValue();
    int getInfraredSensorValue();

private:
    int rightSpeedWheelPin;
    int rightForwardWheelPin;
    int rightBackwardWheelPin;

    int leftSpeedWheelPin;
    int leftForwardWheelPin;
    int leftBackwardWheelPin;

    static char leftWheelSpeed, rightWheelSpeed;
    static int distance;

    void leftWheelForward(char speed);
    void leftWheelBackward(char speed);
    void leftWheelStop();
    void rightWheelForward(char speed);
    void rightWheelBackward(char speed);
    void rightWheelStop();
}