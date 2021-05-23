#include "constants.h"
#include "fotores.h"
#include "ir.h"
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

//1 normal mode
int IRCmd = 0;

void setup() {
  servohori.attach(10);
  servohori.write(0);
  servoverti.attach(9);
  servoverti.write(0);
  Serial.begin(9600);
  delay(500);
  irrecv.enableIRIn();
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
  const int newIRCmd = IR::Receive();

  if (newIRCmd != -2) {
    IRCmd = newIRCmd;
  }

  if (IRCmd != 0) {
    switch (IRCmd) {
      case 1:
        returnHome();
      break;

      case 2:
        moveTop();
      break;

      case 5:
        moveBottom();
      break;

      case 4:
        moveLeft();
      break;

      case 6:
        moveRight();
      break;
    }
    IRCmd = -1;
   return;
  }

  if(FotoRes::isThresholdExceeded()) {
    return;  
  }
 if(avgTop < avgBottom) {
    moveBottom();
  } else if (avgBottom < avgTop) {
    moveTop();
  } else {
    servoverti.write(servov);
  }
  
  if (avgLeft > avgRight) {
    moveLeft();
  } else if (avgRight > avgLeft) {
    moveRight();
  } else {
    servohori.write(servoh);
  }
//  delay(50);/
}

void moveBottom() {
  servoverti.write(servov +1);
  if (servov > servovLimitHigh) { 
    servov = servovLimitHigh;
  }
  delay(2);
}

void moveTop() {
  servoverti.write(servov -1);
  if (servov < servovLimitLow) {
    servov = servovLimitLow;
  }
  delay(2);  
}

void moveLeft() {
  servohori.write(servoh +1);
  if (servoh > servohLimitHigh) {
    servoh = servohLimitHigh;
  }
  delay(2);  
}

void moveRight() {
  servohori.write(servoh -1);
  if (servoh < servohLimitLow) {
   servoh = servohLimitLow;
   }
  delay(2);
}
