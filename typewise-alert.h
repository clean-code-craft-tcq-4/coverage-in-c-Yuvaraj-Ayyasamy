#pragma once

typedef enum {
  PASSIVE_COOLING,
  MED_ACTIVE_COOLING,
  HI_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

#define checkBreach(currentValue, lowerLimit, upperLimit)   \
({                                                          \
    BreachType checkResult = NORMAL;                               \
    if (currentValue < lowerLimit) {                        \
        checkResult = TOO_LOW;                              \
    } else if(currentValue > upperLimit) {                  \
        checkResult = TOO_HIGH;                             \
    } else {                                                \
    }                                                       \
    checkResult;                                            \
})

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
