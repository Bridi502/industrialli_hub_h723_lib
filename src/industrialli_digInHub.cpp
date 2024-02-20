#include "industrialli_digInHub.h"
// interrupt
volatile bool industrialli_digitalInputsHub::_input_00 = false;
volatile bool industrialli_digitalInputsHub::_input_01 = false;
volatile bool industrialli_digitalInputsHub::_input_02 = false;
volatile bool industrialli_digitalInputsHub::_input_03 = false;
volatile bool industrialli_digitalInputsHub::_input_04 = false;
volatile bool industrialli_digitalInputsHub::_input_05 = false;
volatile bool industrialli_digitalInputsHub::_input_06 = false;
volatile bool industrialli_digitalInputsHub::_input_07 = false;
volatile int countI01;
// ENCODER A (I01 - terminal A, I02 - terminal B)
volatile int _aState_ENCA;
volatile int _pulses_ENCA;
volatile bool _rotation_ENCA;
// ENCODER B (I03 - terminal A, I04 - terminal B)
volatile int _aState_ENCB;
volatile int _pulses_ENCB;
volatile bool _rotation_ENCB;
// ENCODER C (I05 - terminal A, I06 - terminal B)
volatile int _aState_ENCC;
volatile int _pulses_ENCC;
volatile bool _rotation_ENCC;
// ENCODER D (I07 - terminal A, I08 - terminal B)
volatile int _aState_ENCD;
volatile int _pulses_ENCD;
volatile bool _rotation_ENCD;

void industrialli_digitalInputsHub::begin()
{

  beginInterruptInput_00();
  beginInterruptInput_01();
  beginInterruptInput_02();
  beginInterruptInput_03();
  beginInterruptInput_04();
  beginInterruptInput_05();
  beginInterruptInput_06();
  beginInterruptInput_07();

  readDigitalInputsStatus();
}
void industrialli_digitalInputsHub::beginDigitalInput(int inputType1, int inputType2, int inputType3, int inputType4, int inputType5, int inputType6, int inputType7, int inputType8)
{
  // NPN Ativado -> LOW(LED APAGADO), Desativado -> HIGH(LED ACESO)
  // PNP Ativado -> HIGH(LED ACESO), Desativado -> LOW(LED APAGADO)
  _inputType[0] = inputType1;
  _inputType[1] = inputType1;
  _inputType[2] = inputType1;
  _inputType[3] = inputType1;
  _inputType[4] = inputType1;
  _inputType[5] = inputType1;
  _inputType[6] = inputType1;
  _inputType[7] = inputType1;
}
void industrialli_digitalInputsHub::readDigitalInputsStatus() // Verifica o valor das entradas
{
  if (digitalRead(EXTI_01) == 1)
  {
    _input_00 = false;
  }
  else
  {
    _input_00 = true;
  }

  if (digitalRead(EXTI_02) == 1)
  {
    _input_01 = false;
  }
  else
  {
    _input_01 = true;
  }

  if (digitalRead(EXTI_03) == 1)
  {
    _input_02 = false;
  }
  else
  {
    _input_02 = true;
  }

  if (digitalRead(EXTI_04) == 1)
  {
    _input_03 = false;
  }
  else
  {
    _input_03 = true;
  }

  if (digitalRead(EXTI_05) == 1)
  {
    _input_04 = false;
  }
  else
  {
    _input_04 = true;
  }

  if (digitalRead(EXTI_06) == 1)
  {
    _input_05 = false;
  }
  else
  {
    _input_05 = true;
  }

  if (digitalRead(EXTI_07) == 1)
  {
    _input_06 = false;
  }
  else
  {
    _input_06 = true;
  }

  if (digitalRead(EXTI_08) == 1)
  {
    _input_07 = false;
  }
  else
  {
    _input_07 = true;
  }
}
bool industrialli_digitalInputsHub::readDigitalInput(uint8_t pin) // Retorna o valor de uma entrada especifica
{
  _pin = pin - 1;
  switch (_pin)
  {
  case 0:
    readDigitalInputsStatus();

    return _input_00;
    break;
  case 1:
    readDigitalInputsStatus();

    return _input_01;
    break;
  case 2:
    readDigitalInputsStatus();

    return _input_02;

    break;
  case 3:
    readDigitalInputsStatus();

    return _input_03;
    break;
  case 4:
    readDigitalInputsStatus();

    return _input_04;

    break;
  case 5:
    readDigitalInputsStatus();

    return _input_05;
    break;

  case 6:
    readDigitalInputsStatus();

    return _input_06;
    break;
  case 7:
    readDigitalInputsStatus();

    return _input_07;
    break;

  default:
    break;
  }
}
void industrialli_digitalInputsHub::updateDigitalInputsLeds() // Atualiza o valor dos LEDs
{
  // NPN Ativado -> LOW(LED APAGADO), Desativado -> HIGH(LED ACESO)
  // PNP Ativado -> HIGH(LED ACESO), Desativado -> LOW(LED APAGADO)

  if (_input_00)
  {
    ledsCtrl.ledOn(4);
  }
  else
  {
    ledsCtrl.ledOff(4);
  }

  if (_input_01)
  {
    ledsCtrl.ledOn(5);
  }
  else
  {
    ledsCtrl.ledOff(5);
  }

  if (_input_02)
  {
    ledsCtrl.ledOn(6);
  }
  else
  {
    ledsCtrl.ledOff(6);
  }

  if (_input_03)
  {
    ledsCtrl.ledOn(7);
  }
  else
  {
    ledsCtrl.ledOff(7);
  }

  if (_input_04)
  {
    ledsCtrl.ledOn(8);
  }
  else
  {
    ledsCtrl.ledOff(8);
  }

  if (_input_05)
  {
    ledsCtrl.ledOn(9);
  }
  else
  {
    ledsCtrl.ledOff(9);
  }

  if (_input_06)
  {
    ledsCtrl.ledOn(10);
  }
  else
  {
    ledsCtrl.ledOff(10);
  }

  if (_input_07)
  {
    ledsCtrl.ledOn(11);
  }
  else
  {
    ledsCtrl.ledOff(11);
  }
}
int industrialli_digitalInputsHub::getPulsesEncoderA(void) // Retorna o valor dos pulsos do encoder A
{
  return _pulses_ENCA;
}
bool industrialli_digitalInputsHub::getRotationEncoderA(void) // Retorna a direcao de rotacao do encoder A (VERDADEIRO para o sentido HORARIO)
{
  return _rotation_ENCA;
}
int industrialli_digitalInputsHub::getCountI01(void)
{
  return countI01;
}
void industrialli_digitalInputsHub::clearCount01(void)
{
  countI01 = 0;
}