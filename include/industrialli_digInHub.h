#ifndef INDUSTRIALLI_DIGINHUB_H
#define INDUSTRIALLI_DIGINHUB_H
#include <Arduino.h>
#include <stdlib.h>
#include "industrialli_ledsHub.h"
extern industrialli_ledsHubCtrl ledsCtrl;
//extern int aState;
//extern int counter;
//extern bool rotation;

// Input dig.
#define EXTI_01 PE15
#define EXTI_02 PE14
#define EXTI_03 PE13
#define EXTI_04 PE12
#define EXTI_05 PB4
#define EXTI_06 PB5
#define EXTI_07 PB6
#define EXTI_08 PB7

#define I01 1
#define I02 2
#define I03 3
#define I04 4
#define I05 5
#define I06 6
#define I07 7
#define I08 8


class industrialli_digitalInputsHub
{
public:
    static volatile bool _input_00; // interrupt
    static volatile bool _input_01;
    static volatile bool _input_02;
    static volatile bool _input_03;
    static volatile bool _input_04;
    static volatile bool _input_05;

    static volatile bool _input_06;
    static volatile bool _input_07;

    static void beginInterruptInput_00() // interrupt
    {
        pinMode(EXTI_01, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_01), interruptInput_00, CHANGE);
    }
    static void interruptInput_00(void)
    {
        noInterrupts();
        _input_00 = !_input_00;
/*
//encoder
        aState = _input_00;
        if( _input_01 != aState){
            counter++;
            rotation = true;

        }
        else{
            counter--;
            rotation = false;
        }
        interrupts();
*/
        
    }

    static void beginInterruptInput_01() // interrupt
    {
        pinMode(EXTI_02, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_02), interruptInput_01, CHANGE);
    }
    static void interruptInput_01(void)
    {
        noInterrupts();
        _input_01 = !_input_01;
        interrupts();
    }

    static void beginInterruptInput_02() // interrupt
    {
        pinMode(EXTI_03, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_03), interruptInput_02, CHANGE);
    }
    static void interruptInput_02(void)
    {
        noInterrupts();
        _input_02 = !_input_02;
        interrupts();
    }

    static void beginInterruptInput_03() // interrupt
    {
        pinMode(EXTI_04, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_04), interruptInput_03, CHANGE);
    }
    static void interruptInput_03(void)
    {
        noInterrupts();
        _input_03 = !_input_03;
        interrupts();
    }

    static void beginInterruptInput_04() // interrupt
    {
        pinMode(EXTI_05, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_05), interruptInput_04, CHANGE);
    }
    static void interruptInput_04(void)
    {
        noInterrupts();
        _input_04 = !_input_04;
        interrupts();
    }

    static void beginInterruptInput_05() // interrupt
    {
        pinMode(EXTI_06, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_06), interruptInput_05, CHANGE);
    }
    static void interruptInput_05(void)
    {
        noInterrupts();
        _input_05 = !_input_05;
        interrupts();
    }

    static void beginInterruptInput_06() // interrupt
    {
        pinMode(EXTI_07, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_07), interruptInput_06, CHANGE);
    }
    static void interruptInput_06(void)
    {
        noInterrupts();
        _input_06 = !_input_06;
        interrupts();
    }

    static void beginInterruptInput_07() // interrupt
    {
        pinMode(EXTI_08, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_08), interruptInput_07, CHANGE);
    }
    static void interruptInput_07(void)
    {
        noInterrupts();
        _input_07 = !_input_07;
        interrupts();
    }

    void begin();
    bool readDigitalInput(uint8_t pin);
    void updateDigitalInputsLeds();

private:
    void readDigitalInputsStatus();
    int _pin;
};

#endif