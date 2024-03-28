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
#include <LoRaMESH.h>

#include "industrialli_hubInit.h"
#include "industrialli_isoOutHub.h"
#include "industrialli_ledsHub.h"
#include "industrialli_anlgInHub.h"
#include "industrialli_digInHub.h"
#include "industrialli_pwrStatusHub.h"
#include "industrialli_dipHub.h"
#include "ethernet2_testHub.h"
industrialli_hubInit startHub;
industrialli_ledsHubCtrl ledsCtrl;
industrialli_isoOutHubCtrl isoOutHub;
industrialli_analogInputsHub anlgInHub;
industrialli_digitalInputsHub digInHub;
industrialli_pwrStatusHub pwrStatusHub;
industrialli_dipHub dipHub;

#define RS485_MOD_UART7_RX PE7
#define RS485_MOD_UART7_TX PE8
#define RS485_MOD_UART7_DE PE9


#define RS485_USART2_RX PD6
#define RS485_USART2_TX PD5
#define RS485_USART2_DE PD4

#define LORA_GPIO PB11
#define LORA_CMD_UART8_RX PE0
#define LORA_CMD_UART8_TX PE1
#define LORA_TRN_USART6_RX PC7
#define LORA_TRN_USART6_TX PC6



HardwareSerial Serial7(RS485_MOD_UART7_RX, RS485_MOD_UART7_TX); //Modulos de expansao
HardwareSerial Serial2(RS485_USART2_RX, RS485_USART2_TX); //RS485 nao isolado
HardwareSerial Serial8(LORA_CMD_UART8_RX, LORA_CMD_UART8_TX); //LoRa CMD
HardwareSerial Serial6(LORA_TRN_USART6_RX, LORA_TRN_USART6_TX); //LoRa TRN



RS485Class RS485(Serial2, RS485_USART2_TX, -1, RS485_USART2_DE);
RS485Class RS485_MOD(Serial7, RS485_MOD_UART7_TX, -1, RS485_MOD_UART7_DE);

/*LoRaMESH*/
LoRaMESH lora(&Serial8);
uint8_t ID = 1;
bool loraLed = false;

TIM_TypeDef *Instance1 = TIM1;
HardwareTimer *MyTim1 = new HardwareTimer(Instance1);
// put function declarations here:
void seconds();
void setup()
{
  // put your setup code here, to run once:
  startHub.begin();
  pinMode(LORA_GPIO, INPUT);
  SerialUSB.begin(115200);
  /*
    while(!SerialUSB){
    ;;
  }
  */

  Serial2.begin(115200); // MODULOS DE EXPANSAO
  Serial7.begin(115200); // RS485
  Serial8.begin(9600); // LoRa CMD
  Serial6.begin(9600); // LoRa TRN

  RS485.setPins(RS485_USART2_TX, RS485_USART2_DE, -1);
  RS485_MOD.setPins(RS485_MOD_UART7_TX, RS485_MOD_UART7_DE, -1);

  RS485.begin(115200);
  RS485_MOD.begin(115200);

  ModbusRTUClient.begin(115200);

  /*LoRaMESH*/
  lora.begin(false);

    if(lora.localId != ID)
  {
    if(!lora.setNetworkID(ID)){
      SerialUSB.println("Erro ao definir o novo ID");
      while(1);
    }

    SerialUSB.println("ID configurado com sucesso!");

    if(!lora.setBPS(BW500, SF7, CR4_5)){
      SerialUSB.println("Erro ao configurar bps");
      while(1);
    }

    SerialUSB.println("Parametros LoRa configurados com sucesso!");
    
    if(!lora.setClass(CLASS_C, WINDOW_15s)){
      SerialUSB.println("Erro ao configurar a classe");
      while(1);
    }

    SerialUSB.println("Modo de operacao configurado com sucesso!");

    if(!lora.setPassword(123)){
      SerialUSB.println("Erro ao gravar a senha ou a senha gravada não condiz com a senha definida");
      while(1);
    }

    SerialUSB.println("Senha configurada com sucesso!");
  }



  if(ID == 1)
    lora.pinMode(1, 0x00, INOUT_DIGITAL_OUTPUT, LOW);

  SerialUSB.println("LocalID: " + String(lora.localId));
  SerialUSB.println("UniqueID: " + String(lora.localUniqueId));
  SerialUSB.println("Pass <= 65535: " + String(lora.registered_password));




  /*HOUSEKEEPING*/
  ledsCtrl.begin();
  pwrStatusHub.begin();
  dipHub.begin();
  /*DIGITAL OUTPUTS*/
  isoOutHub.begin();
  isoOutHub.enableOutputs();
  /*ANALOG INPUTS*/
  anlgInHub.begin();  
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
  /*DIGITAL INPUTS*/
  digInHub.begin();
  digInHub.beginEncoder(ENCODER_01_02, PNP);
  digInHub.beginDigitalInputCounting(I03, PNP, UP);
  digInHub.beginDigitalInputCounting(I04, NPN, UP);




  MyTim1->setOverflow(10000000, MICROSEC_FORMAT);
  MyTim1->attachInterrupt(seconds);
  MyTim1->resume();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(ID == 1){
    
      lora.digitalWrite(1, 0x00, loraLed);
    loraLed = !loraLed;
   
  }
  if(digitalRead(LORA_GPIO)){
    digitalWrite(DEBUG_LED, HIGH);
  }
  else{
    digitalWrite(DEBUG_LED, LOW);
  }
 delay(1000);
  /*
    isoOutHub.getPowerLedsStaus();
  digInHub.updateDigitalInputsLeds();
  ledsCtrl.ledsUpdate();
  SerialUSB.print("Encoder: ");
  SerialUSB.print(digInHub.getPulsesEncoder(ENCODER_01_02));
  SerialUSB.print(" ");
  SerialUSB.print("Sensor PNP: ");
  SerialUSB.print(digInHub.getCountVal(I03));
  SerialUSB.print(" ");
  SerialUSB.print("Sensor NPN: ");
  SerialUSB.print(digInHub.getCountVal(I04));
  SerialUSB.println();
  
  */

  
}

// put function definitions here:
void seconds()
{
 // digitalWrite(DEBUG_LED, !digitalRead(DEBUG_LED));
}