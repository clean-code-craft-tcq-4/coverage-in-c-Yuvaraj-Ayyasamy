#ifndef TYPEWISE_ALERT_H
#define TYPEWISE_ALERT_H
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

extern char SndMsg[];

#define RECEPIENT                    "a.b@c.com"
#define PRINT(message)               printf("%s", message)
#define PASSIVE_COOLING_LOWLIMIT     0
#define PASSIVE_COOLING_HIGHLIMIT    35
#define MED_ACTIVE_COOLING_LOWLIMIT  PASSIVE_COOLING_LOWLIMIT
#define MED_ACTIVE_COOLING_HIGHLIMIT 40
#define HI_ACTIVE_COOLING_LOWLIMIT   PASSIVE_COOLING_LOWLIMIT
#define HI_ACTIVE_COOLING_HIGHLIMIT  45

#define MSG_HEADER 0xfeed
#define THROW_CONTROLLERWARNING(breachType)                \
({                                                         \
    sprintf(SndMsg, "%x : %x\n", MSG_HEADER, breachType);  \
    PRINT(SndMsg);                                         \
})

#define MSG_TOO_LOW      "Hi, the temperature is too low\n"
#define MSG_TOO_HIGH     "Hi, the temperature is too high\n"
#define MSG(message) MSG_##message 
#define THROW_MAILWARNING(message)                                \
({                                                                \
    if (TOO_LOW == message) {                                     \
        sprintf(SndMsg, "To: %s\n %s", RECEPIENT, MSG(TOO_LOW));  \
    } else {                                                      \
        sprintf(SndMsg, "To: %s\n %s", RECEPIENT, MSG(TOO_HIGH)); \
    }                                                             \
    PRINT(SndMsg);                                                \
})

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

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);
void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

#endif // TYPEWISE_ALERT_H
