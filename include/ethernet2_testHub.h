#include <Arduino.h>
#include <SPI.h>
#include <Ethernet2.h>
#include <EthernetUdp2.h>

#define SPI2_MOSI PB15
#define SPI2_MISO PB14
#define SPI2_NSS PB12
#define SPI2_SCK PB13

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
// IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "www.google.com"; // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void initEthernetIPCheckHub(){
     SPI.setMISO(SPI2_MISO);
    SPI.setMOSI(SPI2_MOSI);
    SPI.setSCLK(SPI2_SCK);
    Ethernet.init(SPI2_NSS);
  // this check is only needed on the Leonardo:
  while (!SerialUSB) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    SerialUSB.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
  }
  // print your local IP address:
  SerialUSB.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    SerialUSB.print(Ethernet.localIP()[thisByte], DEC);
    SerialUSB.print(".");
  }
  SerialUSB.println();   
}

void initEthernetWebClientHub()
{
    SPI.setMISO(SPI2_MISO);
    SPI.setMOSI(SPI2_MOSI);
    SPI.setSCLK(SPI2_SCK);
    Ethernet.init(SPI2_NSS);
    while (!SerialUSB)
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }

    // start the Ethernet connection:
    if (Ethernet.begin(mac) == 0)
    {
        SerialUSB.println("Failed to configure Ethernet using DHCP");
        // no point in carrying on, so do nothing forevermore:
        // try to congifure using IP address instead of DHCP:
        Ethernet.begin(mac, ip);
    }
    // give the Ethernet shield a second to initialize:
    delay(1000);
    Serial.println("connecting...");

    // if you get a connection, report back via serial:
    if (client.connect(server, 80))
    {
        SerialUSB.println("connected");
        // Make a HTTP request:
        client.println("GET /search?q=arduino HTTP/1.1");
        client.println("Host: www.google.com");
        client.println("Connection: close");
        client.println();
    }
    else
    {
        // kf you didn't get a connection to the server:
        SerialUSB.println("connection failed");
    }
}




void webClientTest()
{
    SPI.setMISO(SPI2_MISO);
    SPI.setMOSI(SPI2_MOSI);
    SPI.setSCLK(SPI2_SCK);
    SPI.begin();
    if (client.available())
    {
        char c = client.read();
        SerialUSB.print(c);
    }

    // if the server's disconnected, stop the client:
    if (!client.connected())
    {
        SerialUSB.println();
        SerialUSB.println("disconnecting.");
        client.stop();

        // do nothing forevermore:
        while (true)
            ;
    }
    SPI.end();
}




