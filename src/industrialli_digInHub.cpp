#include "industrialli_digInHub.h"

volatile bool industrialli_digitalInputsHub::_input_00 = false; // interrupt
volatile bool industrialli_digitalInputsHub::_input_01 = false;
volatile bool industrialli_digitalInputsHub::_input_02 = false;
volatile bool industrialli_digitalInputsHub::_input_03 = false;
volatile bool industrialli_digitalInputsHub::_input_04 = false;
volatile bool industrialli_digitalInputsHub::_input_05 = false;
volatile bool industrialli_digitalInputsHub::_input_06 = false;
volatile bool industrialli_digitalInputsHub::_input_07 = false;

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
void industrialli_digitalInputsHub::readDigitalInputsStatus()
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

bool industrialli_digitalInputsHub::readDigitalInput(uint8_t pin)
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
void industrialli_digitalInputsHub::updateDigitalInputsLeds()
{

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