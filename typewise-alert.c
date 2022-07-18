#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return checkBreach(value, lowerLimit, upperLimit);
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  return inferBreach(temperatureInC, setLowLimit(coolingType), setHighLimit(coolingType));
}

void checkAndAlert( AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC );
  if( TO_CONTROLLER == alertTarget) {
      sendToController(breachType);
  } else {
      sendToEmail(breachType);
  }
}

void sendToController(BreachType breachType) {
  THROW_CONTROLLERWARNING(breachType);
}

void sendToEmail(BreachType breachType) {
  THROW_MAILWARNING(breachType);
}
