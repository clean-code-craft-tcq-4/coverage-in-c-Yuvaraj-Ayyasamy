#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(-1, PASSIVE_COOLING_LOWLIMIT, PASSIVE_COOLING_HIGHLIMIT) == TOO_LOW);
  REQUIRE(inferBreach(30, PASSIVE_COOLING_LOWLIMIT, PASSIVE_COOLING_HIGHLIMIT) == NORMAL);
  REQUIRE(inferBreach(36, PASSIVE_COOLING_LOWLIMIT, PASSIVE_COOLING_HIGHLIMIT) == TOO_HIGH);
  REQUIRE(inferBreach(-1, MED_ACTIVE_COOLING_LOWLIMIT, MED_ACTIVE_COOLING_HIGHLIMIT) == TOO_LOW);
  REQUIRE(inferBreach(12, MED_ACTIVE_COOLING_LOWLIMIT, MED_ACTIVE_COOLING_HIGHLIMIT) == NORMAL);
  REQUIRE(inferBreach(41, MED_ACTIVE_COOLING_LOWLIMIT, MED_ACTIVE_COOLING_HIGHLIMIT) == TOO_HIGH);
  REQUIRE(inferBreach(-1, HI_ACTIVE_COOLING_LOWLIMIT, HI_ACTIVE_COOLING_HIGHLIMIT) == TOO_LOW);
  REQUIRE(inferBreach(40, HI_ACTIVE_COOLING_LOWLIMIT, HI_ACTIVE_COOLING_HIGHLIMIT) == NORMAL);
  REQUIRE(inferBreach(46, HI_ACTIVE_COOLING_LOWLIMIT, HI_ACTIVE_COOLING_HIGHLIMIT) == TOO_HIGH);
}

TEST_CASE("classify breach")
{
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -1) == TOO_LOW);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1) == TOO_LOW);

    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 20) == NORMAL);
    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 35) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == NORMAL);

    REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 36) == TOO_HIGH);
    REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41) == TOO_HIGH);
}

TEST_CASE("check classify and alert")
{
    BatteryCharacter batteryAttribute = {PASSIVE_COOLING, "LUMINOUS"};
    checkAndAlert(batteryAttribute, 36, sendToController);

    BatteryCharacter batteryCharacter = {MED_ACTIVE_COOLING, "EXIDE"};
    checkAndAlert(batteryCharacter, 46, sendToEmail);

    BatteryCharacter batteryCharacter1 = {PASSIVE_COOLING, "AMARON"};
    checkAndAlert(batteryCharacter1, -1, sendToEmail);
}
