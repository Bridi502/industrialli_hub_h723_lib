#include "industrialli_digInHub.h"
uint32_t _userMode;

callback_function_t _userFunction;

volatile int _count_00;
volatile int _count_01;
volatile int _count_02;
volatile int _count_03;
volatile int _count_04;
volatile int _count_05;
volatile int _count_06;
volatile int _count_07;

volatile bool _upOrDown;
// interrupt
volatile bool industrialli_digitalInputsHub::_input_00 = false;
volatile bool industrialli_digitalInputsHub::_input_01 = false;
volatile bool industrialli_digitalInputsHub::_input_02 = false;
volatile bool industrialli_digitalInputsHub::_input_03 = false;
volatile bool industrialli_digitalInputsHub::_input_04 = false;
volatile bool industrialli_digitalInputsHub::_input_05 = false;
volatile bool industrialli_digitalInputsHub::_input_06 = false;
volatile bool industrialli_digitalInputsHub::_input_07 = false;

// ENCODER

volatile int _aStateEncoder_I01_I02;
volatile int _aStateEncoder_I03_I04;
volatile int _aStateEncoder_I05_I06;
volatile int _aStateEncoder_I07_I08;

volatile int _pulsesEncoder_I01_I02;
volatile int _pulsesEncoder_I03_I04;
volatile int _pulsesEncoder_I05_I06;
volatile int _pulsesEncoder_I07_I08;

volatile bool _rotationEncoder_I01_I02;
volatile bool _rotationEncoder_I03_I04;
volatile bool _rotationEncoder_I05_I06;
volatile bool _rotationEncoder_I07_I08;

void testFunction()
{
}

void industrialli_digitalInputsHub::updateDigitalInputsLeds() // Atualiza o valor dos LEDs
{

    _ledStatus[0] = digitalRead(EXTI_01);
    _ledStatus[1] = digitalRead(EXTI_02);
    _ledStatus[2] = digitalRead(EXTI_03);
    _ledStatus[3] = digitalRead(EXTI_04);
    _ledStatus[4] = digitalRead(EXTI_05);
    _ledStatus[5] = digitalRead(EXTI_06);
    _ledStatus[6] = digitalRead(EXTI_07);
    _ledStatus[7] = digitalRead(EXTI_08);

    // PNP 0 // Ativado -> HIGH(LED ACESO), Desativado -> LOW(LED APAGADO)
    // NPN 1 // Ativado -> LOW(LED APAGADO), Desativado -> HIGH(LED ACESO)

    // INPUT CONNECTOR: LOW -> OUTPUT OPTO: HIGH
    // INPUT CONNECTOR: HIGH -> OUTPUT OPTO: LOW

    for (int i = 0; i < 8; i++)
    {
        if (_sensorType[i] == 0) // Sensor PNP
        {
            if (_ledStatus[i] == 1)
            {
                ledsCtrl.ledOff(4 + i); // PNP desativado
            }
            else
            {
                ledsCtrl.ledOn(4 + i); // PNP ativado
            }
        }
        else if (_sensorType[i] == 1) // Sensor NPN
        {
            if (_ledStatus[i] == 1)
            {
                ledsCtrl.ledOn(4 + i); // NPN ativado
            }
            else
            {
                ledsCtrl.ledOff(4 + i); // NPN desativado
            }
        }
    }
}
void industrialli_digitalInputsHub::beginEncoder(uint8_t encoder, bool sensorType)
{
}
int industrialli_digitalInputsHub::getPulsesEncoder(uint8_t encoder)
{
    _encoder = encoder;
    // ENCODER_01_02 0
    // ENCODER_03_04 1
    // ENCODER_05_06 2
    // ENCODER_07_08 3
    
    switch (_encoder)
    {
    case 0:
        return _pulsesEncoder_I01_I02;
        break;
    case 1:
        return _pulsesEncoder_I03_I04;
        break;
    case 2:
        return _pulsesEncoder_I05_I06;
        break;
    case 3:
        return _pulsesEncoder_I07_I08;
        break;

    default:
        break;
    }
}

void industrialli_digitalInputsHub::beginDigitalInputCounting(uint8_t pin, bool sensorType, bool upOrDown)
{
    _pin = pin - 1;
    _sensorType[_pin] = sensorType;
    _upOrDown = upOrDown;
    // PNP 0
    // NPN 1
    switch (_pin)
    {
    case 0:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_00();
        }
        else // NPN
        {
            beginInterruptInputRising_00();
        }

        break;
    case 1:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_01();
        }
        else // NPN
        {
            beginInterruptInputRising_01();
        }
        break;
    case 2:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_02();
        }
        else // NPN
        {
            beginInterruptInputRising_02();
        }
        break;
    case 3:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_03();
        }
        else // NPN
        {
            beginInterruptInputRising_03();
        }
        break;
    case 4:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_04();
        }
        else // NPN
        {
            beginInterruptInputRising_04();
        }
        break;
    case 5:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_05();
        }
        else // NPN
        {
            beginInterruptInputRising_05();
        }
        break;
    case 6:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_06();
        }
        else // NPN
        {
            beginInterruptInputRising_06();
        }
        break;
    case 7:
        if (_sensorType == 0) // PNP
        {
            beginInterruptInputFalling_07();
        }
        else // NPN
        {
            beginInterruptInputRising_07();
        }
        break;

    default:
        break;
    }
}

void industrialli_digitalInputsHub::clearCount(uint8_t pin)
{
    _pin = pin - 1;
    switch (_pin)
    {
    case 0:
        _count_00 = 0;
        break;
    case 1:
        _count_01 = 0;
        break;
    case 2:
        _count_02 = 0;
        break;
    case 3:
        _count_03 = 0;
        break;
    case 4:
        _count_04 = 0;
        break;
    case 5:
        _count_05 = 0;
        break;
    case 6:
        _count_06 = 0;
        break;
    case 7:
        _count_07 = 0;
        break;

    default:
        break;
    }
}

void industrialli_digitalInputsHub::beginUserDigitalInput(uint8_t pin, callback_function_t userFunction, uint32_t mode, bool sensorType)
{
    _pin = pin - 1;
    _userMode = mode;
    _userFunction = userFunction;
    _sensorType[_pin] = sensorType;
    switch (_pin)
    {
    case 0:
        beginUserInterruptInput_00();
        break;
    case 1:
        beginUserInterruptInput_01();
        break;
    case 2:
        beginUserInterruptInput_02();
        break;
    case 3:
        beginUserInterruptInput_03();
        break;
    case 4:
        beginUserInterruptInput_04();
        break;
    case 5:
        beginUserInterruptInput_05();
        break;
    case 6:
        beginUserInterruptInput_06();
        break;
    case 7:
        beginUserInterruptInput_07();
        break;

    default:
        break;
    }
}
void industrialli_digitalInputsHub::initTestInterrupts()
{
    _userMode = FALLING;
    _userFunction = testFunction;
    for (int i = 0; i < 8; i++)
    {
        _sensorType[i] = PNP;
    }

    beginUserInterruptInput_00();
    beginUserInterruptInput_01();
    beginUserInterruptInput_02();
    beginUserInterruptInput_03();
    beginUserInterruptInput_04();
    beginUserInterruptInput_05();
    beginUserInterruptInput_06();
    beginUserInterruptInput_07();
}
void industrialli_digitalInputsHub::testDigitalInputs()
{
    SerialUSB.print(digitalRead(EXTI_01));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_02));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_03));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_04));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_05));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_06));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_07));
    SerialUSB.print(" ");
    SerialUSB.print(digitalRead(EXTI_08));
    SerialUSB.print(" ");
    SerialUSB.println();
}