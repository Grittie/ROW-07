#include <wiringPiI2C.h> // je kan ook pigpio gebruiken
#include <wiringPi.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define WHEEL_ADDRESS 0x32



struct termios orig_termios;
    
    void disableRawMode() {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }
    
    void enableRawMode() {
      tcgetattr(STDIN_FILENO, &orig_termios);
      atexit(disableRawMode);
    
      struct termios raw = orig_termios;
      raw.c_lflag &= ~(ECHO | ICANON);
    
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }

int main()
{   
    int fd = wiringPiI2CSetup(WHEEL_ADDRESS);
    enableRawMode();
    
    char c;

    uint8_t stop[7] = {0x07,0xff,0x00,0x00,0xff,0x00,0x00};  

    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'x') {
        if (iscntrl(c)) {
            printf("%d\n", c);
        } else {
            printf("%c\n", c);
            switch (c)
            {
                case 'W':                    // 00 = stil, 01 = naar voren, 02 == naar achteren
                    {                        //hoeveelheid bits, rechts high, low, direction, left high, low, direction
                        uint8_t forwardHard[7] = {7,9,0xA5,1,9,0xA5,1};
                        write(fd,&forwardHard[0],7);
                    }
                    break;
                case 'w':
                    {
                        uint8_t Forward[7] = {7,2,0xA5,1,2,0xA5,1};
                        write(fd,&Forward[0],7);
                    }
                    break;
                case 'S':
                    {
                        uint8_t backwardHard[7] = {7,9,0xA5,2,9,0xA5,2};        
                        write(fd,&backwardHard[0],7);
                    }
                    break;
                case 's':
                    {
                        uint8_t backward[7] = {7,2,0xA5,2,2,0xA5,2};        
                        write(fd,&backward[0],7);
                    }
                    break;
                case 'q':
                    {
                        uint8_t leftDiag[7] = {7,3,0xA5,1,0,0xA5,0};         
                        write(fd,&leftDiag[0],7);
                    }
                    break;
                case 'A':
                    {
                        uint8_t leftHard[7] = {7,9,0xA5,1,9,0xA5,2};         
                        write(fd,&leftHard[0],7);
                    }
                    break;
                case 'a':
                    {
                        uint8_t left[7] = {7,2,0xA5,1,2,0xA5,2};         
                        write(fd,&left[0],7);
                    }
                    break;
                case 'e':
                    {
                        uint8_t rightDiag[7] = {7,0,0xA5,0,3,0xA5,1};        
                        write(fd,&rightDiag[0],7);
                    }
                    break;
                case 'D':
                    {
                        uint8_t rightHard[7] = {7,9,0xA5,2,9,0xA5,1};        
                        write(fd,&rightHard[0],7);
                    }
                    break;
                case 'd':
                    {
                        uint8_t right[7] = {7,2,0xA5,2,2,0xA5,1};        
                        write(fd,&right[0],7);
                    }
                    break;
                case 'c':
                    {
                        uint8_t rightDiagBack[7] = {7,0,0xA5,0,3,0xA5,2};        
                        write(fd,&rightDiagBack[0],7);
                    }
                    break;
                case 'z':
                    {
                        uint8_t leftDiagBack[7] = {7,3,0xA5,2,0,0xA5,0};        
                        write(fd,&leftDiagBack[0],7);
                    }
                    break;
                case 'f':
                    {      
                        write(fd,&stop[0],7);
                    }
                    break;
                default:
                    {
                        write(fd,&stop,7);
                    }
                    break;
            }
        }
    }
    write(fd,&stop,7);
    return 0;   
}    