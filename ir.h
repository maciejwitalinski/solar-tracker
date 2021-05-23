 #ifndef IR
#define IR
#include "constants.h"
#include <IRremote.h>
IRrecv irrecv(IRPin);
decode_results signals;

int Receive() {
  if (irrecv.decode(&signals)) {
    irrecv.resume();
    if (signals.value == 0xFFA857) {
      return 0;
    }

    if (signals.value == 0xFFE01F) {
      return -1;
    }

    if (signals.value == 0xFF30CF) {
      return 1;
    }

    if (signals.value == 0xFF18E7) {
      return 2;
    }

    if (signals.value == 0xFF38C7) {
      return 5;
    }

    if (signals.value == 0xFF10EF) {
      return 4;
    }
    
    if (signals.value == 0xFF5AA5) {
      return 6;
    }
  }

  return -2;
}

#endif
