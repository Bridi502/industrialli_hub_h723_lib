#ifndef INDUSTRIALLI_DIPHUB_H
#define INDUSTRIALLI_DIPHUB_H

#include <Arduino.h>
#include <stdlib.h>

#define DIP_01 PD10
#define DIP_02 PD14
#define DIP_03 PD11
#define DIP_04 PA8

#define DIP01 1
#define DIP02 2
#define DIP03 3
#define DIP04 4

class industrialli_dipHub
{

private:
uint8_t _dipPin;
bool _dipVal[4] = {
   _dipVal[0],
   _dipVal[1],
   _dipVal[2],
   _dipVal[3]
};
public:
void begin();
bool readDIP(uint8_t dipPin);
void test();


};



#endif