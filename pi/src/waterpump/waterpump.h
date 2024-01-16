#ifndef WATERPUMP_H
#define WATERPUMP_H

class Waterpump {
public:
    void extrude(int in, int time); // Keep 'int in' as a parameter
    void printStart();
    void printEnd();
};

#endif // WATERPUMP_H