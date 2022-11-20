#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>

void WaitForSerialInput()
{
  while(Serial.available() <= 0)
  {
    delay(10);
  }
}

void ClearSerial()
{
  while(Serial.available() > 0)
    Serial.read();
}

int ReadIntFromSerial()
{
  WaitForSerialInput();
  int value = Serial.parseInt();
  ClearSerial();
  return value;
}

#endif // HELPER_H
