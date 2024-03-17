#include "industrialli_dipHub.h"

void industrialli_dipHub::begin()
{
    pinMode(DIP_01, INPUT);
    pinMode(DIP_02, INPUT);
    pinMode(DIP_03, INPUT);
    pinMode(DIP_04, INPUT);
}
bool industrialli_dipHub::readDIP(uint8_t dipPin)
{

    _dipPin = dipPin - 1;
    switch (_dipPin)
    {
    case 0:
        _dipVal[0] = digitalRead(DIP_01);
        return _dipVal[0];
        break;
    case 1:
        _dipVal[1] = digitalRead(DIP_02);
        return _dipVal[1];
        break;
    case 2:
        _dipVal[2] = digitalRead(DIP_03);
        return _dipVal[2];
        break;
    case 3:
        _dipVal[3] = digitalRead(DIP_04);
        return _dipVal[3];
        break;

    default:
        return -1;
        break;
    }
}
void industrialli_dipHub::test()
{
    SerialUSB.print(readDIP(DIP01));
    SerialUSB.print(" ");
    SerialUSB.print(readDIP(DIP02));
    SerialUSB.print(" ");
    SerialUSB.print(readDIP(DIP03));
    SerialUSB.print(" ");
    SerialUSB.print(readDIP(DIP04));
    SerialUSB.print(" ");
    SerialUSB.println();
}