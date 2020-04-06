#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "__My_Disco__";
const char *password = "andy1996";

unsigned int localPort = 8888;      // local port to listen on

char packetBuffer[20]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "ACK";       // a string to send back

String data = "";

WiFiUDP Udp;

void setup() {

  Serial.begin(74880);
  Serial.println();
  Serial.print("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.println("HTTP server started");

  Udp.begin(localPort);
}

void loop() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    
    //Serial.print("port ");
    //Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    data = packetBuffer;
    clearPacketBuffer ();
    Serial.println(data);
    

    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();
  }
}

void clearPacketBuffer ()
{
  for(int i =0;i<20;i++)packetBuffer[i]='\0';
}
