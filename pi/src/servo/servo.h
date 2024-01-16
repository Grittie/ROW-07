#ifndef SERVO_H
#define SERVO_H

class Servo {
public:
    void left(int in); // Keep 'int in' as a parameter
    void right(int in); // Keep 'int in' as a parameter
    void printLeft();
    void printRight();
    void printDone();
};

#endif // SERVO_H