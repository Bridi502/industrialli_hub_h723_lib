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



#define DEBUG_LED PB10


// put function declarations here:


void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  pinMode(DEBUG_LED, OUTPUT);

 
  ledsCtrl.begin();
  isoOutHub.begin();
  isoOutHub.enableOutputs();
  anlgInHub.setAnalogResolution(BITS_16);
  anlgInHub.begin();
  pwrStatusHub.begin();
  digInHub.begin();
  digInHub.beginDigitalInputCounting(I01, PNP, UP);
  /*
    digInHub.beginDigitalInputCounting(I02, PNP, UP);
  digInHub.beginDigitalInputCounting(I03, PNP, UP);
  digInHub.beginDigitalInputCounting(I04, PNP, UP);
  digInHub.beginDigitalInputCounting(I05, PNP, UP);
  digInHub.beginDigitalInputCounting(I06, PNP, UP);
  digInHub.beginDigitalInputCounting(I07, PNP, UP);
  digInHub.beginDigitalInputCounting(I08, PNP, UP);
  */



 
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
  isoOutHub.getPowerLedsStaus();
  digInHub.updateDigitalInputsLeds();
  SerialUSB.println(digInHub.getCountVal(I01));
  ledsCtrl.ledsUpdate();



  }




// put function definitions here:



