#ifndef industrialli_digitalInputsHub_H
#define industrialli_digitalInputsHub_H
#include <Arduino.h>
#include <stdlib.h>
#include "industrialli_ledsHub.h"
extern industrialli_ledsHubCtrl ledsCtrl;
extern volatile int _aState_ENCA;
extern volatile int _pulses_ENCA;
extern volatile bool _rotation_ENCA;
extern volatile int countI01;

extern uint32_t _userMode00;
extern callback_function_t _userFunction00;

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

#define PNP 0 // Ativado -> HIGH(LED ACESO), Desativado -> LOW(LED APAGADO)
#define NPN 1 // Ativado -> LOW(LED APAGADO), Desativado -> HIGH(LED ACESO)

#define ENCODER_A 11
#define ENCODER_B 12
#define ENCODER_C 13
#define ENCODER_D 14

class industrialli_digitalIsolatedInputsHub
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

    static void beginUserInterruptInput_00() // EXTI01 USER
    {
        pinMode(EXTI_01, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_01), _userFunction00, _userMode00);
    }
    /*
    static void beginInterruptInput_00() // EXTI01 CHANGE
        {
            pinMode(EXTI_01, INPUT);
            attachInterrupt(digitalPinToInterrupt(EXTI_01), interruptInput_00, CHANGE);
        }
        static void interruptInput_00(void)
        {
            noInterrupts();
            _input_00 = !_input_00;
            // if(digitalRead(EXTI_01) == false){
            //   countI01++;
            //}
            interrupts();
        }

        static void beginInterruptInputFalling_00() // EXTI01 FALLING
        {
            pinMode(EXTI_01, INPUT);
            attachInterrupt(digitalPinToInterrupt(EXTI_01), interruptInputFalling_00, FALLING);
        }
        static void interruptInputFalling_00(void)
        {
            noInterrupts();
            _input_00 = !_input_00;

            // encoder
            _aState_ENCA = _input_00;
            if (_input_01 != _aState_ENCA)
            {
                _pulses_ENCA++;
                _rotation_ENCA = true;
            }
            else
            {
                _pulses_ENCA--;
                _rotation_ENCA = false;
            }
            interrupts();
        }

        static void beginInterruptInputRising_00() // EXTI01 RISING
        {
            pinMode(EXTI_01, INPUT);
            attachInterrupt(digitalPinToInterrupt(EXTI_01), interruptInputRising_00, RISING);
        }
        static void interruptInputRising_00(void)
        {
            noInterrupts();
            _input_00 = !_input_00;
            interrupts();
        }


    */

    static void beginInterruptInput_01() // EXTI02 CHANGE
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

    static void beginInterruptInputFalling_01() // EXTI02 FALLING
    {
        pinMode(EXTI_02, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_02), interruptInputFalling_01, FALLING);
    }
    static void interruptInputFalling_01(void)
    {
        noInterrupts();
        _input_01 = !_input_01;
        interrupts();
    }

    static void beginInterruptInputRising_01() // EXTI02 RISING
    {
        pinMode(EXTI_02, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_02), interruptInputRising_01, RISING);
    }
    static void interruptInputRising_01(void)
    {
        noInterrupts();
        _input_01 = !_input_01;
        interrupts();
    }

    static void beginInterruptInput_02() // EXTI03 CHANGE
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

    static void beginInterruptInputFalling_02() // EXTI03 FALLING
    {
        pinMode(EXTI_03, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_03), interruptInputFalling_02, FALLING);
    }
    static void interruptInputFalling_02(void)
    {
        noInterrupts();
        _input_02 = !_input_02;
        interrupts();
    }

    static void beginInterruptInputRising_02() // EXTI03 RISING
    {
        pinMode(EXTI_03, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_03), interruptInputRising_02, RISING);
    }
    static void interruptInputRising_02(void)
    {
        noInterrupts();
        _input_02 = !_input_02;
        interrupts();
    }

    static void beginInterruptInput_03() // EXTI04 CHANGE
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

    static void beginInterruptInputFalling_03() // EXTI04 FALLING
    {
        pinMode(EXTI_04, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_04), interruptInputFalling_03, FALLING);
    }
    static void interruptInputFalling_03(void)
    {
        noInterrupts();
        _input_03 = !_input_03;
        interrupts();
    }

    static void beginInterruptInputRising_03() // EXTI04 RISING
    {
        pinMode(EXTI_04, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_04), interruptInputRising_03, RISING);
    }
    static void interruptInputRising_03(void)
    {
        noInterrupts();
        _input_03 = !_input_03;
        interrupts();
    }

    static void beginInterruptInput_04() // EXTI05 CHANGE
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

    static void beginInterruptInputFalling_04() // EXTI05 FALLING
    {
        pinMode(EXTI_05, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_05), interruptInputFalling_04, FALLING);
    }
    static void interruptInputFalling_04(void)
    {
        noInterrupts();
        _input_04 = !_input_04;
        interrupts();
    }

    static void beginInterruptInputRising_04() // EXTI05 RISING
    {
        pinMode(EXTI_05, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_05), interruptInputRising_04, RISING);
    }
    static void interruptInputRising_04(void)
    {
        noInterrupts();
        _input_04 = !_input_04;
        interrupts();
    }

    static void beginInterruptInput_05() // EXTI06 CHANGE
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

    static void beginInterruptInputFalling_05() // EXTI06 FALLING
    {
        pinMode(EXTI_06, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_06), interruptInputFalling_05, FALLING);
    }
    static void interruptInputFalling_05(void)
    {
        noInterrupts();
        _input_05 = !_input_05;
        interrupts();
    }

    static void beginInterruptInputRising_05() // EXTI06 RISING
    {
        pinMode(EXTI_06, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_06), interruptInputRising_05, RISING);
    }
    static void interruptInputRising_05(void)
    {
        noInterrupts();
        _input_05 = !_input_05;
        interrupts();
    }

    static void beginInterruptInput_06() // EXTI07 CHANGE
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

    static void beginInterruptInputFalling_06() // EXTI07 FALLING
    {
        pinMode(EXTI_07, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_07), interruptInputFalling_06, FALLING);
    }
    static void interruptInputFalling_06(void)
    {
        noInterrupts();
        _input_06 = !_input_06;
        interrupts();
    }

    static void beginInterruptInputRising_06() // EXTI07 RISING
    {
        pinMode(EXTI_07, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_07), interruptInputRising_06, RISING);
    }
    static void interruptInputRising_06(void)
    {
        noInterrupts();
        _input_06 = !_input_06;
        interrupts();
    }

    static void beginInterruptInput_07() // EXTI08 CHANGE
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

    static void beginInterruptInputFalling_07() // EXTI08 FALLING
    {
        pinMode(EXTI_08, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_08), interruptInputFalling_07, FALLING);
    }
    static void interruptInputFalling_07(void)
    {
        noInterrupts();
        _input_07 = !_input_07;
        interrupts();
    }

    static void beginInterruptInputRising_07() // EXTI08 RISING
    {
        pinMode(EXTI_08, INPUT);
        attachInterrupt(digitalPinToInterrupt(EXTI_08), interruptInputRising_07, RISING);
    }
    static void interruptInputRising_07(void)
    {
        noInterrupts();
        _input_07 = !_input_07;
        interrupts();
    }

    void begin();
    void beginDigitalInput(int inputType1, int inputType2, int inputType3, int inputType4, int inputType5, int inputType6, int inputType7, int iputType8);
    bool readDigitalInput(uint8_t pin);
    void updateDigitalInputsLeds();
    int getPulsesEncoderA(void); // Retorna o valor dos pulos do encoder A (I01-I02)
    bool getRotationEncoderA(void);

    int getCountI01(void);   // Retorna a contagem na entrata I01
    void clearCount01(void); // Limpa o valor da contagem na entrada I01
    void beginDigitalInputI01(callback_function_t userFunction, uint32_t mode, bool sensorType);
    void beginUserInputI01();

private:
    void readDigitalInputsStatus();
    int _pin;
    int _inputType[8] = {
        _inputType[0] = -1,
        _inputType[1] = -1,
        _inputType[2] = -1,
        _inputType[3] = -1,
        _inputType[4] = -1,
        _inputType[5] = -1,
        _inputType[6] = -1,
        _inputType[7] = -1

    };
    bool _sensorType = 0;
};

#endif