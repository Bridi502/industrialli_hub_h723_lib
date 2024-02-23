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

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};
IPAddress ip(192, 168, 137, 254);
IPAddress gateway(172, 16, 80, 1);
IPAddress subnet(255, 255, 252, 0);

// telnet defaults to port 23
EthernetServer server(23);
boolean gotAMessage = false; // whether or not you got a message from the client yet

// put function declarations here:
int myFunction(int, int);

void setup()
{
  // put your setup code here, to run once:
  SerialUSB.begin(115200);
  pinMode(W5500_RST, OUTPUT);
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



  

  while (!SerialUSB) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
    SPI.setMISO(SPI2_MISO);
  SPI.setMOSI(SPI2_MOSI);
  SPI.setSCLK(SPI2_SCK);
  SPI.begin();
Ethernet.init(SPI2_NSS);
delay(1000);

  // start the Ethernet connection:
  //SerialUSB.println("Trying to get an IP address using DHCP");
 // if (Ethernet.begin(mac) == 0) {
   // SerialUSB.println("Failed to configure Ethernet using DHCP");
    // initialize the ethernet device not using DHCP:
    Ethernet.begin(mac, ip, gateway, subnet);
  //}
  // print your local IP address:
  SerialUSB.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    SerialUSB.print(ip[thisByte], DEC);
    SerialUSB.print(".");
  }
  SerialUSB.println();
  // start listening for clients
  server.begin();





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
      SPI.setMISO(SPI2_MISO);
  SPI.setMOSI(SPI2_MOSI);
  SPI.setSCLK(SPI2_SCK);
  SPI.begin();
Ethernet.init(SPI2_NSS);
  EthernetClient client = server.available();

  // when the client sends the first byte, say hello:
  if (client) {
    if (!gotAMessage) {
      SerialUSB.println("We have a new client");
      client.println("Hello, client!");
      gotAMessage = true;
    }

    // read the bytes incoming from the client:
    char thisChar = client.read();
    // echo the bytes back to the client:
    server.write(thisChar);
    // echo the bytes to the server as well:
    Serial.print(thisChar);
  }



}

// put function definitions here:
int myFunction(int x, int y)
{
  return x + y;
}