extern relay_t oxValve;         // Refrence things from another file
extern relay_t fuelValve;
extern relay_t purgeValve;
extern relay_t igniter;
extern relay_t redLight;
extern relay_t yellowLight;
extern relay_t greenLight;
extern relay_t buzzer;
extern uint16_t heartbeatCount;
extern uint16_t safing;
extern uint16_t mode;
extern uint32_t timeStamp;
extern stateBuffer allStates;


void packetReadSafe() {     // If safing is active, only allow a packet to unsafe it

  while(safing != 0) {
    Serial.println(seqNum);
    Serial.println("safe loop");
    while(!Udp.parsePacket()) {
      if ( millis() > timeStamp + 1000) {      // Heartbeat while waiting for packet
        Udp.beginPacket("224.0.0.1", 8084);
        Udp.write((char*)&allStates, sizeof(stateBuffer));
        Udp.write((char*)&seqNum, sizeof(uint32_t));
        Udp.write((char*)&heartbeatCount, sizeof(uint16_t));
        Udp.endPacket();
        timeStamp = millis();
        heartbeatCount++;
      } 
    }
    Udp.read((char*)&packetBuffer, 8);
    
    if (packetBuffer.seqNum != seqNum + 1) {   // If the seqNum is not one greater than the current one, do not run that packet
      Serial.println(packetBuffer.seqNum);
      Serial.println("breakout");
      continue;
    }
    seqNum++;
  
    if (packetBuffer.controlNum == 900) {
      if (packetBuffer.state == 0) {
        mode = 0;
        Udp.beginPacket("224.0.0.1", 8085);
        Udp.write((char*)&seqNum, sizeof(uint32_t));
        Udp.write((char*)&mode, sizeof(uint16_t));
        Udp.write((char*)&safing, sizeof(uint16_t));
        Udp.endPacket();
      }
    } else if (packetBuffer.controlNum == 901 && mode == 0) {
      if (packetBuffer.state == 0) {
        Serial.println(" safing low"); 
        safing = 0;
        Udp.beginPacket("224.0.0.1", 8085);
        Udp.write((char*)&seqNum, sizeof(uint32_t));
        Udp.write((char*)&mode, sizeof(uint16_t));
        Udp.write((char*)&safing, sizeof(uint16_t));
        Udp.endPacket();
      }
    }
  }
  
}




void packetRead() {                     // Read incoming packet and parse it

  while(!Udp.parsePacket()) {
    if ( millis() > timeStamp + 1000) {      // Heartbeat while waiting for packet
      Udp.beginPacket("224.0.0.1", 8084);
      Udp.write((char*)&allStates, sizeof(stateBuffer));
      Udp.write((char*)&seqNum, sizeof(uint32_t));
      Udp.write((char*)&heartbeatCount, sizeof(uint16_t));
      Udp.endPacket();
      timeStamp = millis();
      heartbeatCount++;
    }

    if (Ethernet.linkStatus() == LinkOFF) {
      safing = 1;
    }
  }

  Udp.read((char*)&packetBuffer, 8);  // Read the next packet and assign it to packetBuffer

  if (packetBuffer.seqNum != seqNum + 1) {   // If the seqNum is not one greater than the current one, do not run that packet
    return;
  }
  
  if (mode != 0) {
    if (oxValve.controlNum == packetBuffer.controlNum) {          // A million if elses to see what states to change and what pins to activate
      if(packetBuffer.state == 0) {
        allStates.solenoids.sol1 = 0;
        digitalWrite(oxValve.pin, HIGH);
        seqNum++;
      } else {
        allStates.solenoids.sol1 = 1;
        digitalWrite(oxValve.pin, LOW);
        seqNum++;
      }
    } else if (fuelValve.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.solenoids.sol2 = 0;
        digitalWrite(fuelValve.pin, HIGH);
        seqNum++;
      } else {
        allStates.solenoids.sol2 = 1;
        digitalWrite(fuelValve.pin, LOW);
        seqNum++;
      }
    } else if (purgeValve.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.solenoids.sol3 = 0;
        digitalWrite(purgeValve.pin, HIGH);
        seqNum++;
      } else {
        allStates.solenoids.sol3 = 1;
        digitalWrite(purgeValve.pin, LOW);
        seqNum++;
      }
    } else if (purgeValve2.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.solenoids.sol4 = 0;
        digitalWrite(purgeValve2.pin, HIGH);
        seqNum++;
      } else {
        allStates.solenoids.sol4 = 1;
        digitalWrite(purgeValve2.pin, LOW);
        seqNum++;
      }
     } else if (igniter.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.igniters.igniter1 = 0;
        digitalWrite(igniter.pin, HIGH);
        seqNum++;
      } else {
        allStates.igniters.igniter1 = 1;
        digitalWrite(igniter.pin, LOW);
        seqNum++;
      }
    } else if (redLight.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.LED_R = 0;
        digitalWrite(redLight.pin, HIGH);
        seqNum++;
      } else {
        allStates.light.LED_R = 1;
        digitalWrite(redLight.pin, LOW);
        seqNum++;
      }
    } else if (yellowLight.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.LED_Y = 0;
        digitalWrite(yellowLight.pin, HIGH);
        seqNum++;
      } else {
        allStates.light.LED_Y = 1;
        digitalWrite(yellowLight.pin, LOW);
        seqNum++;
      }
    } else if (greenLight.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.LED_G = 0;
        digitalWrite(greenLight.pin, HIGH);
        seqNum++;
      } else {
        allStates.light.LED_G = 1;
        digitalWrite(greenLight.pin, LOW);
        seqNum++;
      }
    } else if (buzzer.controlNum == packetBuffer.controlNum) {
      if(packetBuffer.state == 0){
        allStates.light.buzz = 0;
        digitalWrite(buzzer.pin, HIGH);
        seqNum++;
      } else {
        allStates.light.buzz = 1;
        digitalWrite(buzzer.pin, LOW);
        seqNum++;
      }
    }
  }
  
    
    if (packetBuffer.controlNum == 900) {
    if (packetBuffer.state == 0) {
      if (allStates.solenoids.sol1 != 0 || allStates.solenoids.sol2 != 0 || allStates.solenoids.sol3 != 0) {
        seqNum--;
        return;
      }
      mode = 0;
      Udp.beginPacket("224.0.0.1", 8085);
      seqNum++;
      Udp.write((char*)&seqNum, sizeof(uint32_t));
      Udp.write((char*)&mode, sizeof(uint16_t));
      Udp.write((char*)&safing, sizeof(uint16_t));
      Udp.endPacket();
      
    } else if (packetBuffer.state == 1) {
      mode = 1;
      seqNum++;
      Udp.beginPacket("224.0.0.1", 8085);
      Udp.write((char*)&seqNum, sizeof(uint32_t));
      Udp.write((char*)&mode, sizeof(uint16_t));
      Udp.write((char*)&safing, sizeof(uint16_t));
      Udp.endPacket();
    } else if (packetBuffer.state == 99) {
      mode = 99;
      seqNum++;
      Udp.beginPacket("224.0.0.1", 8085);
      Udp.write((char*)&seqNum, sizeof(uint32_t));
      Udp.write((char*)&mode, sizeof(uint16_t));
      Udp.write((char*)&safing, sizeof(uint16_t));
      Udp.endPacket();
    } else if (packetBuffer.state == 69) {
      mode = 69;
      seqNum++;
      Udp.beginPacket("224.0.0.1", 8085);
      Udp.write((char*)&seqNum, sizeof(uint32_t));
      Udp.write((char*)&mode, sizeof(uint16_t));
      Udp.write((char*)&safing, sizeof(uint16_t));
      Udp.endPacket();
    }
    } else if (packetBuffer.controlNum == 901) {
      if (packetBuffer.state == 1) {
        safing = 1;
        seqNum++;
        Serial.print("safing high");
        Udp.beginPacket("224.0.0.1", 8085);
        Udp.write((char*)&seqNum, sizeof(uint32_t));
        Udp.write((char*)&mode, sizeof(uint16_t));
        Udp.write((char*)&safing, sizeof(uint16_t));
        Udp.endPacket();
        safe();
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
    Udp.write((char*)&heartbeatCount, sizeof(uint16_t));
    Udp.endPacket();
  } 
}
