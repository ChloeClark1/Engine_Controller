extern relay_t oxValve;         // Refrence things from another file
extern relay_t fuelValve;
extern relay_t purgeValve;
extern relay_t igniter;
extern relay_t redLight;
extern relay_t yellowLight;
extern relay_t greenLight;
extern relay_t buzzer;
extern uint16_t safing;
extern uint16_t mode;
extern stateBuffer allStates;


void packetReadSafe() {     // If safing is active, only allow a packet to unsafe it

  while(!Udp.parsePacket()) {
    yield();
    if (Ethernet.linkStatus() == LinkOFF){   // if the link is down, safe the engine and try not to let it blow up
      safing = 1;
      engineSafe();         // Change?
    }
  }
  if (packetBuffer.seqNum != seqNum + 1) {   // If the seqNum is not one greater than the current one, do not run that packet
    return;
  }
  seqNum++;

  if (packetBuffer.controlNum == 901) {
    if (packetBuffer.state == 0) {
      safing = 0;
    }
  } 
}




void packetRead() {                     // Read incoming packet and parse it

  while (!Udp.parsePacket()){           // If there is not packet to read, check if the ethernet link is still up
   yield();
   if (Ethernet.linkStatus() == LinkOFF){   // if the link is down, safe the engine and try not to let it blow up
      safing = 1;
     // Implement with engine_states
   }

   if (millis() > 10000) {
    Udp.beginPacket("224.0.0.1", 8084);
    Udp.write((char*)&allStates, sizeof(stateBuffer));
    Udp.write((char*)&seqNum+1, sizeof(uint32_t));
    Udp.endPacket();
   }
   /* if (e stop pressed){
    * safing = 1
    *                           // if the estop is pressed, enter safe modes
    *
    */
  }

  Serial.print("packet available");

  Udp.read((char*)&packetBuffer, 8);  // Read the next packet and assign it to packetBuffer

  Serial.print("packet received");

  while (packetBuffer.seqNum != seqNum + 1) {   // If the seqNum is not one greater than the current one, do not run that packet
    return;
  }
  seqNum++;

    if (oxValve.controlNum == packetBuffer.controlNum) {          // A million if elses to see what states to change and what pins to activate
      if(packetBuffer.state == 0) {
        allStates.solenoids.sol1 = 0;
        digitalWrite(oxValve.pin, HIGH);
      } else {
        allStates.solenoids.sol1 = 1;
        digitalWrite(oxValve.pin, LOW);
      }
    } else if (fuelValve.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.solenoids.sol2 = 0;
        digitalWrite(fuelValve.pin, HIGH);
      } else {
        allStates.solenoids.sol2 = 1;
        digitalWrite(fuelValve.pin, LOW);
      }
    } else if (purgeValve.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.solenoids.sol3 = 0;
        digitalWrite(purgeValve.pin, HIGH);
      } else {
        allStates.solenoids.sol3 = 1;
        digitalWrite(purgeValve.pin, LOW);
      }
    } else if (igniter.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.igniters.igniter1 = 0;
        digitalWrite(igniter.pin, HIGH);
      } else {
        allStates.igniters.igniter1 = 1;
        digitalWrite(igniter.pin, LOW);
      }
    } else if (redLight.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.LED_R = 0;
        digitalWrite(redLight.pin, HIGH);
      } else {
        allStates.light.LED_R = 1;
        digitalWrite(redLight.pin, LOW);
      }
    } else if (yellowLight.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.LED_Y = 0;
        digitalWrite(yellowLight.pin, HIGH);
      } else {
        allStates.light.LED_Y = 1;
        digitalWrite(yellowLight.pin, LOW);
      }
    } else if (greenLight.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.LED_G = 0;
        digitalWrite(greenLight.pin, HIGH);
      } else {
        allStates.light.LED_G = 1;
        digitalWrite(greenLight.pin, LOW);
      }
    } else if (buzzer.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.buzz = 0;
        digitalWrite(buzzer.pin, HIGH);
      } else {
        allStates.light.buzz = 1;
        digitalWrite(buzzer.pin, LOW);
      }
    } else if (packetBuffer.controlNum == 900) {
      safing = 1;
    if (packetBuffer.state == 0) {
      mode = 0;
      disabled();
    } else if (packetBuffer.state == 1) {
      mode = 1;
      coldFail();
    } else if (packetBuffer.state == 99) {
      mode = 99;
      hotFail();
    }
    } else if (packetBuffer.controlNum == 901) {
      if (packetBuffer.state == 1) {
        safing = 1;
        // implement with engine_states
      }
  }
  Serial.print(seqNum);

}


void packetSend() {                      // Send packet back with response and telemetry
  if (packetBuffer.controlNum >= 100 && packetBuffer.controlNum <= 199) {
    Udp.beginPacket("224.0.0.1", 8081);   // Start a packet to be sent to the specified IP and port
    Udp.write((char*)&allStates.solenoids, sizeof(solReplyBuffer));    
    Udp.write((char*)&seqNum, sizeof(uint32_t));
    Udp.endPacket();                          // End the packet
  } else if (packetBuffer.controlNum >= 200 && packetBuffer.controlNum <= 299) {
    Udp.beginPacket("224.0.0.1", 8082);
    Udp.write((char*)&allStates.igniters, sizeof(ignReplyBuffer));
    Udp.write((char*)&seqNum, sizeof(uint32_t));
    Udp.endPacket();
  } else if (packetBuffer.controlNum >= 300 && packetBuffer.controlNum <= 399) {
    Udp.beginPacket("224.0.0.1", 8083);
    Udp.write((char*)&allStates.light, sizeof(lightReplyBuffer));
    Udp.write((char*)&seqNum, sizeof(uint32_t));
    Udp.endPacket();
  } else if (packetBuffer.controlNum >= 900 && packetBuffer.controlNum <= 999) {
    Udp.beginPacket("224.0.0.1", 8084);
    Udp.write((char*)&allStates, sizeof(stateBuffer));
    Udp.write((char*)&seqNum, sizeof(uint32_t));
    Udp.endPacket();
  } else {
    Serial.print(" Invalid controlNum ");
  }

  Serial.print(" packet sent ");

}
