#ifndef HELPER_H
#define HELPER_H

#include <Arduino.h>
#include <TimeLib.h>

void PrintTime()
{
  time_t t = now();
  Serial.println("Current time is " + String(hour(t)) + ":" + String(minute(t)) + ":" + String(second(t)) + " " + String(day(t)) + "." + String(month(t)) + "." + String(year(t)));
}

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
