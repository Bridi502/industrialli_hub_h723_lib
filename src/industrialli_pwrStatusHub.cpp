#include "industrialli_pwrStatusHub.h"
void industrialli_pwrStatusHub::begin()
{
    pinMode(PGOOD1,INPUT);
    pinMode(PGOOD2, INPUT);
}
bool industrialli_pwrStatusHub::statusPGOOD1()
{
    bool pwrStatus = digitalRead(PGOOD1);
    if (pwrStatus)
        return true;
    else
        return false;
}
bool industrialli_pwrStatusHub::statusPGOOD2()
{
    bool pwrStatus = digitalRead(PGOOD2);
    if (pwrStatus)
        return true;
    else
        return false;
}
void industrialli_pwrStatusHub::test(){
SerialUSB.print(statusPGOOD1());
SerialUSB.print(" ");
SerialUSB.print(statusPGOOD2());
SerialUSB.println();
}