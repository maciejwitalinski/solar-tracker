#include "constants.h"
#include "fotores.h"
#include <Servo.h>
Servo servohori;
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 60;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 60;

int offTime = 0;

void setup() {
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(0);
  Serial.begin(9600);
  delay(500);
}

void returnHome() {
  servohori.write(0);
  servoverti.write(0);
  delay(10);
}

void loop() {
  servoh = servohori.read();
  servov = servoverti.read();

  int avgTop = FotoRes::getAverage("top");
  int avgBottom = FotoRes::getAverage("bottom");
  int avgLeft = FotoRes::getAverage("left");
  int avgRight = FotoRes::getAverage("right");

//  if(!FotoRes::enoughLight()) {
//    offTime += 1000;
//    delay(1000);
//  } else {
//    offTime = 0;
//  }
//  if (offTime > offTimeMinThreshold) {
//    returnHome();
//    return; 
//  }

  if(FotoRes::isThresholdExceeded()) {
    return;  
  }
 if(avgTop < avgBottom) {
    servoverti.write(servov +1);
    if (servov > servovLimitHigh) { 
      servov = servovLimitHigh;
    }
    delay(2);
  } else if (avgBottom < avgTop) {
    servoverti.write(servov -1);
    if (servov < servovLimitLow) {
      servov = servovLimitLow;
    }
    delay(2);
  } else {
    servoverti.write(servov);
  }
  
  if (avgLeft > avgRight) {
    servohori.write(servoh +1);
    if (servoh > servohLimitHigh) {
      servoh = servohLimitHigh;
    }
    delay(2);
  } else if (avgRight > avgLeft) {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow) {
     servoh = servohLimitLow;
     }
    delay(2);
  } else {
    servohori.write(servoh);
  }
//  delay(50);/
}
