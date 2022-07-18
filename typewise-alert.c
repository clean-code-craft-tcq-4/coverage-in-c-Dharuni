#include "typewise-alert.h"
#include <stdio.h>

TemperatureLimit checkTempLimits(CoolingType coolingType)
{
    TemperatureLimit tempLimit;
  if(coolingType == PASSIVE_COOLING){
	  tempLimit.lowerLimit = PASSIVE_COOLING_LOWER_LIMIT;
	  tempLimit.upperLimit = PASSIVE_COOLING_UPPER_LIMIT;
  }
  else if(coolingType == HI_ACTIVE_COOLING){
	  tempLimit.lowerLimit = HI_ACTIVE_COOLING_LOWER_LIMIT;
	  tempLimit.upperLimit = HI_ACTIVE_COOLING_UPPER_LIMIT;
  }
  else{
	 tempLimit.lowerLimit = MED_ACTIVE_COOLING_LOWER_LIMIT;
	 tempLimit.upperLimit = MED_ACTIVE_COOLING_UPPER_LIMIT;
  }
  return tempLimit;
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
    TemperatureLimit tempLimit;
    tempLimit = checkTempLimits (coolingType);
  return inferBreach(temperatureInC, tempLimit.lowerLimit, tempLimit.upperLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
}
