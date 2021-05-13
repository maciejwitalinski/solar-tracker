 #ifndef FOTO_RES
#define FOTO_RES
#include "constants.h"

namespace FotoRes {
  float getResValue(int pinNum) {
    return analogRead(pinNum);
  }

  int getAverage(String dir) {
    if(dir == "top") {
      return (getResValue(fotoTopLeftPin) + getResValue(fotoTopRightPin));
    } else if(dir == "bottom") {
      return (getResValue(fotoBottomLeftPin) + getResValue(fotoBottomRightPin));
    } else if(dir == "right") {
      return (getResValue(fotoTopRightPin) + getResValue(fotoBottomRightPin));
    } else if(dir == "left") {
      return (getResValue(fotoTopLeftPin) + getResValue(fotoBottomLeftPin));
    }
  }

  float calculateAvgPercents(float val, float avg) {
    return abs(100 - (100 * val / avg));
  }

  bool isThresholdExceeded() {
    float bottomLeft = getResValue(fotoBottomLeftPin);
    float bottomRight = getResValue(fotoBottomRightPin);
    float topLeft = getResValue(fotoTopLeftPin);
    float topRight = getResValue(fotoTopRightPin);

    float avg = (bottomLeft + bottomRight + topLeft + topRight) / 4;

    float bottomLeftPercent = calculateAvgPercents(bottomLeft, avg);
    float bottomRightPercent = calculateAvgPercents(bottomRight, avg);
    float topLeftPercent = calculateAvgPercents(topLeft, avg);
    float topRightPercent = calculateAvgPercents(topRight, avg);

    if(
      bottomLeftPercent > sensivityThreshold ||
      bottomRightPercent > sensivityThreshold ||
      topLeftPercent > sensivityThreshold ||
      topRightPercent > sensivityThreshold
     ) {
      return false; 
     }

     return true;
  }

  bool enoughLight() {
    int avg = (getResValue(fotoTopLeftPin) + getResValue(fotoTopRightPin) + getResValue(fotoBottomLeftPin) + getResValue(fotoBottomRightPin)) / 4;
    return avg >= minLightValue;
  }
}

#endif
