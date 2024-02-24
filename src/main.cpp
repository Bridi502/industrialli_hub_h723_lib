#include <Arduino.h>
#include <SPI.h>
#include <Ethernet2.h>
#include "industrialli_isoOutHub.h"
#include "industrialli_ledsHub.h"
#include "industrialli_anlgInHub.h"
#include "industrialli_digInHub.h"

industrialli_ledsHubCtrl ledsCtrl;
industrialli_isoOutHubCtrl isoOutHub;
industrialli_analogInputsHub anlgInHub;
industrialli_digitalInputsHub digInHub;

#define SPI2_MOSI PB15
#define SPI2_MISO PB14
#define SPI2_NSS PB12
#define SPI2_SCK PB13
#define W5500_RST PD7
#define DEBUG_LED PB10



// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  pinMode(W5500_RST, OUTPUT);
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(1000);
  digitalWrite(W5500_RST, HIGH);
  int result = myFunction(2, 3);
  ledsCtrl.begin();
  isoOutHub.begin();
  // isoOutHub.enableOutputs();
  isoOutHub.disableOutputs();
  anlgInHub.begin();
  digInHub.begin();







/*
  anlgInHub.setReadMode(A01, READ_010);
  anlgInHub.setReadMode(A02, READ_010);
  anlgInHub.setReadMode(A03, READ_010);
  anlgInHub.setReadMode(A04, READ_010);
*/
  anlgInHub.setReadMode(A01, READ_020);
  anlgInHub.setReadMode(A02, READ_020);
  anlgInHub.setReadMode(A03, READ_020);
  anlgInHub.setReadMode(A04, READ_020);
}

void loop()
{
  // put your main code here, to run repeatedly:
  isoOutHub.writeDigitalOutput(8, HIGH);
  isoOutHub.writeDigitalOutput(16, HIGH);
  isoOutHub.getPowerLedsStaus();
  digInHub.updateDigitalInputsLeds();

  // ledsCtrl.ledOn(16);
  ledsCtrl.ledsUpdate();
  // SerialUSB.println(isoOutHub.getOut9to16Status());
/*
  SerialUSB.print(anlgInHub.get010V(A01));
  //SerialUSB.print(anlgInHub.get020mA(A01));
  SerialUSB.print(" ");
  SerialUSB.print(anlgInHub.get010V(A02));
  // SerialUSB.print(anlgInHub.get020mA(A02));
  SerialUSB.print(" ");
  SerialUSB.print(anlgInHub.get010V(A03));
  //SerialUSB.print(anlgInHub.get020mA(A03));
  SerialUSB.print(" ");
  SerialUSB.println(anlgInHub.get010V(A04));
  //SerialUSB.println(anlgInHub.get020mA(A04));
*/
/*
SerialUSB.print(digInHub.readDigitalInput(I01));
SerialUSB.print(" ");
SerialUSB.print(digInHub.readDigitalInput(I02));
SerialUSB.print(" ");
SerialUSB.print(digInHub.readDigitalInput(I03));
SerialUSB.print(" ");
SerialUSB.print(digInHub.readDigitalInput(I04));
SerialUSB.print(" ");
SerialUSB.print(digInHub.readDigitalInput(I05));
SerialUSB.print(" ");
SerialUSB.print(digInHub.readDigitalInput(I06));
SerialUSB.print(" ");
SerialUSB.print(digInHub.readDigitalInput(I07));
SerialUSB.print(" ");
SerialUSB.println(digInHub.readDigitalInput(I08));
*/
//SerialUSB.println(digInHub.getCountI01());
//SerialUSB.print(digInHub.getRotationEncoderA());
//SerialUSB.print(" ");
//SerialUSB.println(digInHub.getPulsesEncoderA());
  // wait for a new client:

digitalWrite(DEBUG_LED, !digitalRead(DEBUG_LED));
delay(1000);

}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}