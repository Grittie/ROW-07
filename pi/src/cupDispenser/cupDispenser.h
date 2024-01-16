#ifndef CUPDISPENSER_H
#define CUPDISPENSER_H

class CupDispenser {
public:
    void dispense(int dispenserPin, int time);
    bool cupholder(int buttonPin);

private:
    void printStart();
    void printEnd();
};

#endif // CUPDISPENSER_H
