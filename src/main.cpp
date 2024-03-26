#include <Arduino.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <ArduinoRS485.h>
/*
foi preciso modificar  o arquivo "RS485.cpp"

#ifdef RS485_SERIAL_PORT
RS485Class RS485(RS485_SERIAL_PORT, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);
#else
//RS485Class RS485(SERIAL_PORT_HARDWARE, RS485_DEFAULT_TX_PIN, RS485_DEFAULT_DE_PIN, RS485_DEFAULT_RE_PIN);
#endif
*/
#include <ArduinoModbus.h>
#include <HardwareSerial.h>

#include "industrialli_isoOutHub.h"
#include "industrialli_ledsHub.h"
#include "industrialli_anlgInHub.h"
#include "industrialli_digInHub.h"
#include "industrialli_pwrStatusHub.h"
#include "industrialli_dipHub.h"
#include "ethernet2_testHub.h"

industrialli_ledsHubCtrl ledsCtrl;
industrialli_isoOutHubCtrl isoOutHub;
industrialli_analogInputsHub anlgInHub;
industrialli_digitalInputsHub digInHub;
industrialli_pwrStatusHub pwrStatusHub;
industrialli_dipHub dipHub;

#define DEBUG_LED PB10

#define RS485_MOD_UART7_RX PE7
#define RS485_MOD_UART7_TX PE8
#define RS485_MOD_UART7_DE PE9

#define RS485_TER_SEL PE10
#define RS485_USART2_RX PD6
#define RS485_USART2_TX PD5
#define RS485_USART2_DE PD4

HardwareSerial Serial7(RS485_MOD_UART7_RX, RS485_MOD_UART7_TX);
HardwareSerial Serial2(RS485_USART2_RX, RS485_USART2_TX);

RS485Class RS485(Serial2, RS485_USART2_TX, -1, RS485_USART2_DE);
RS485Class RS485_MOD(Serial7, RS485_MOD_UART7_TX, -1, RS485_MOD_UART7_DE);
bool sec = true;
bool up = true;
int turnOn = 1;

TIM_TypeDef *Instance1 = TIM1;
HardwareTimer *MyTim1 = new HardwareTimer(Instance1);
// put function declarations here:
void seconds();
void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  Serial2.begin(115200); // MODULOS DE EXPANSAO
  Serial7.begin(115200); // RS485

  RS485.setPins(RS485_USART2_TX, RS485_USART2_DE, -1);
  RS485_MOD.setPins(RS485_MOD_UART7_TX, RS485_MOD_UART7_DE, -1);

  RS485.begin(115200);
  RS485_MOD.begin(115200);

  ModbusRTUClient.begin(115200);

  pinMode(DEBUG_LED, OUTPUT);
  pinMode(RS485_TER_SEL, OUTPUT);

  ledsCtrl.begin();
  isoOutHub.begin();
  anlgInHub.begin();
  digInHub.begin();
  pwrStatusHub.begin();
  dipHub.begin();
  digInHub.initTestInterrupts();
  isoOutHub.enableOutputs();
  anlgInHub.setAnalogResolution(BITS_16);

  anlgInHub.setReadMode(A01, READ_020);
  anlgInHub.setReadMode(A02, READ_020);
  anlgInHub.setReadMode(A03, READ_020);
  anlgInHub.setReadMode(A04, READ_020);

  /*
    anlgInHub.setReadMode(A01, READ_010);
    anlgInHub.setReadMode(A02, READ_010);
    anlgInHub.setReadMode(A03, READ_010);
    anlgInHub.setReadMode(A04, READ_010);
  */

  MyTim1->setOverflow(1000000, MICROSEC_FORMAT);
  MyTim1->attachInterrupt(seconds);
  MyTim1->resume();
}

void loop()
{
  // put your main code here, to run repeatedly:
  isoOutHub.getPowerLedsStaus();
  digInHub.updateDigitalInputsLeds();
  ledsCtrl.ledsUpdate();
  dipHub.test();
  digInHub.testDigitalInputs();
  //isoOutHub.test(HIGH);
}

// put function definitions here:
void seconds()
{
  sec = !sec;
  digitalWrite(DEBUG_LED, !digitalRead(DEBUG_LED));
}