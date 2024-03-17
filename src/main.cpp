#include <Arduino.h>
#include <SPI.h>
#include <Ethernet2.h>

#include "industrialli_isoOutHub.h"
#include "industrialli_ledsHub.h"
#include "industrialli_anlgInHub.h"
#include "industrialli_digInHub.h"
#include "industrialli_pwrStatusHub.h"
#include "ethernet2_testHub.h"



industrialli_ledsHubCtrl ledsCtrl;
industrialli_isoOutHubCtrl isoOutHub;
industrialli_analogInputsHub anlgInHub;
industrialli_digitalInputsHub digInHub;
industrialli_pwrStatusHub pwrStatusHub;



#define W5500_RST PD7
#define W5500_INT PD3
#define DEBUG_LED PB10


// put function declarations here:
int myFunction(int, int);
void ledOn();

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  pinMode(W5500_RST, OUTPUT);
  pinMode(W5500_INT, INPUT);
  pinMode(DEBUG_LED, OUTPUT);
  digitalWrite(W5500_RST, LOW);
  delay(1000);
  digitalWrite(W5500_RST, HIGH);
  int result = myFunction(2, 3);
  ledsCtrl.begin();
  isoOutHub.begin();
  // isoOutHub.enableOutputs();
  isoOutHub.disableOutputs();
  anlgInHub.setAnalogResolution(BITS_16);
  anlgInHub.begin();
  pwrStatusHub.begin();
 
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

  

  
}


void loop()
{
  // put your main code here, to run repeatedly:
  isoOutHub.writeDigitalOutput(8, HIGH);
  isoOutHub.writeDigitalOutput(16, HIGH);
  isoOutHub.getPowerLedsStaus();
  //digInHub.updateDigitalInputsLeds();
  ledsCtrl.ledsUpdate();
  SerialUSB.println("hello!");


  }




// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}
void ledOn(){
  digitalWrite(DEBUG_LED, !digitalRead(DEBUG_LED));
}


