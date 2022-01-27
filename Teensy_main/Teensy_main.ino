
#include <NativeEthernet.h>         // Initialize Ethernet libraries
#include <NativeEthernetUdp.h>

uint32_t seqNum = 0;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED      // Set the Mac Address
  
};
IPAddress ip(10, 10, 10, 75);      // Set the Teensy IP address

unsigned int localPort = 8080;      // local port to listen on

EthernetUDP Udp;

typedef struct {            // Struct for anything attached to the relay
  uint16_t pin;
  uint16_t currentState;
  uint16_t controlNum;
} relay_t;

typedef struct {          // Struct for the incoming command from GS
  uint32_t seqNum;
  uint16_t controlNum;
  uint16_t state;
} ec_command_t;

typedef struct {          // Struct for the incoming command from GS
  uint16_t sol1;
  uint16_t sol2;
  uint16_t sol3;
  uint32_t seqNum;
} __attribute__((packed)) solReplyBuffer;

typedef struct {          // Struct for the incoming command from GS
  uint16_t igniter1;
  uint32_t seqNum;
} __attribute__((packed)) ignReplyBuffer;

typedef struct {          // Struct for the incoming command from GS
  uint16_t LED_G;
  uint16_t LED_Y;
  uint16_t LED_R;
  uint16_t buzz;
  uint32_t seqNum;
} __attribute__((packed)) lightReplyBuffer;


solReplyBuffer solenoids = {0, 0, 0, 0};
ignReplyBuffer igniters = {0, 0};
lightReplyBuffer light = {0, 0, 0, 0, 0};


ec_command_t packetBuffer;          // Initialize packetBuffer

relay_t oxValve = {16, 0, 100};       // Initialize all objects planned to be used 
relay_t fuelValve = {17, 0, 101};
relay_t purgeValve = {18, 0, 102};
relay_t igniter = {19, 0, 200};
relay_t redLight = {20, 0, 300};
relay_t yellowLight = {21, 0, 301};
relay_t greenLight = {22, 0, 302};
relay_t buzzer = {23, 0, 303};

void setup() {
  Ethernet.begin(mac, ip);    // Initialize Ethernet
  Serial.begin(9600);


  if (Ethernet.hardwareStatus() == EthernetNoHardware) {    // If the ethernet hardware isn't detected, infinitely loop to prevent anything from running
    while (true) {  
      delay(1);
    }
  }
  pinMode(oxValve.pin, OUTPUT);       // Initialize the pins which will connect from Teensy to relay
  digitalWrite(oxValve.pin, HIGH);
  pinMode(fuelValve.pin, OUTPUT);
  digitalWrite(fuelValve.pin, HIGH);
  pinMode(purgeValve.pin, OUTPUT);
  digitalWrite(purgeValve.pin, HIGH);
  pinMode(igniter.pin, OUTPUT);
  digitalWrite(igniter.pin, HIGH);
  pinMode(redLight.pin, OUTPUT);
  digitalWrite(redLight.pin, HIGH);
  pinMode(yellowLight.pin, OUTPUT);
  digitalWrite(yellowLight.pin, HIGH);
  pinMode(greenLight.pin, OUTPUT);
  digitalWrite(greenLight.pin, HIGH);
  pinMode(buzzer.pin, OUTPUT);
  digitalWrite(buzzer.pin, HIGH);
  
  Udp.begin(localPort);
  Udp.beginPacket("224.0.0.1", 8080);   
  Udp.write((char*)&seqNum, sizeof(uint32_t));      
  Udp.endPacket();   
}



void loop() {

  packetRead();     // Main program, just reads and writes packets
  packetSend();

}
