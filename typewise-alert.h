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

#define PASSIVE_COOLING_LOWLIMIT     0
#define PASSIVE_COOLING_HIGHLIMIT    35
#define MED_ACTIVE_COOLING_LOWLIMIT  36
#define MED_ACTIVE_COOLING_HIGHLIMIT 40
#define HI_ACTIVE_COOLING_LOWLIMIT   41
#define HI_ACTIVE_COOLING_HIGHLIMIT  45
#define setLowLimit(message) message##_LOWLIMIT
#define setHighLimit(message) message##_HIGHLIMIT

#define MSG_TOO_LOW      "Hi, the temperature is too low\n"
#define MSG_TOO_HIGH     "Hi, the temperature is too high\n"
#define Print(message) MSG_##message 

#define THROW_WARNING(message, recepient)                   \
({                                                          \
    printf("To: %s\n", recepient);                          \
    printf("%s", Print(message));                           \
})

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

#define checkBreach(currentValue, lowerLimit, upperLimit)   \
({                                                          \
    BreachType checkResult = NORMAL;                        \
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
