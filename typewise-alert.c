#include "typewise-alert.h"

int coolingTypeLimit[3][2] = {
  /* PASSIVE COOLING */
  {PASSIVE_COOLING_LOWLIMIT, PASSIVE_COOLING_HIGHLIMIT},
  /* MED ACTIVE COOLING */
  {MED_ACTIVE_COOLING_LOWLIMIT, MED_ACTIVE_COOLING_HIGHLIMIT},
  /* HI ACTIVE COOLING */
  {HI_ACTIVE_COOLING_LOWLIMIT, HI_ACTIVE_COOLING_HIGHLIMIT}
};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  return checkBreach(value, lowerLimit, upperLimit);
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
  int lowLimit = coolingTypeLimit[coolingType][LOWLIMIT];
  int highLimit = coolingTypeLimit[coolingType][HIGHLIMIT];
  return inferBreach(temperatureInC, lowLimit, highLimit);
}

void checkAndAlert( BatteryCharacter batteryChar, double temperatureInC, void (*alertType) (BreachType breachType)) {
  BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC );
  (*alertType) (breachType);
}

void sendToController(BreachType breachType) {
  noOfChar = THROW_CONTROLLERWARNING(breachType);
}

void sendToEmail(BreachType breachType) {
  noOfChar = THROW_MAILWARNING(breachType);
}
