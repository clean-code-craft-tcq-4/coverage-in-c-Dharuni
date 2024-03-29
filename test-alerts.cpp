#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
  REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
  REQUIRE(inferBreach(22, 20, 30) == NORMAL);
}

TEST_CASE("Check the temperature limits based on the coolingType") {
  TemperatureLimit tempLimit;
  
  //Test Lower & Upper Limits of PASSIVE_COOLING
  tempLimit = checkTempLimits(PASSIVE_COOLING);
  REQUIRE(tempLimit.lowerLimit == PASSIVE_COOLING_LOWER_LIMIT);
  REQUIRE(tempLimit.upperLimit == PASSIVE_COOLING_UPPER_LIMIT);
  
  //Test Lower & Upper Limits of HI_ACTIVE_COOLING
  tempLimit = checkTempLimits(HI_ACTIVE_COOLING);
  REQUIRE(tempLimit.lowerLimit == HI_ACTIVE_COOLING_LOWER_LIMIT);
  REQUIRE(tempLimit.upperLimit == HI_ACTIVE_COOLING_UPPER_LIMIT);
  
  //Test Lower & Upper Limits of MED_ACTIVE_COOLING
  tempLimit = checkTempLimits(MED_ACTIVE_COOLING);
  REQUIRE(tempLimit.lowerLimit == MED_ACTIVE_COOLING_LOWER_LIMIT);
  REQUIRE(tempLimit.upperLimit == MED_ACTIVE_COOLING_UPPER_LIMIT);
}

TEST_CASE("Check and Alert the Temperature Breach based on coolingType ") {
  BatteryCharacter batteryChar;
  
  batteryChar.coolingType = PASSIVE_COOLING;
  assert(checkAndAlert(TO_CONTROLLER,batteryChar,0)==SUCCESS);	// Controller alert for temp in range
  assert(checkAndAlert(TO_EMAIL,batteryChar,35)==SUCCESS);		//Email alert for temp in range
}

TEST_CASE("Alert via Email") {
  REQUIRE(sendToEmail(TOO_LOW)== SUCCESS);	//Alert for Too-Low Temperature
  REQUIRE(sendToEmail(TOO_HIGH)== SUCCESS); //Alert for Too-High Temperature
}
