#include "typewise-alert.h"
#include <stdio.h>

int sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
  return SUCCESS;
}

int sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  if(breachType == TOO_LOW)
  {
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
  }
  else if(breachType == TOO_HIGH)
  {
	  printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
  }
  return SUCCESS;
}
