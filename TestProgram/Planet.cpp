#include "Planet.h"
#include <TimeLib.h>

Planet::Planet(String name, PlanetType type,
     int steps_per_360_degree,
     int pin_1, int pin_2, int pin_3, int pin_4,
     int reed_pin,
     unsigned int step_for_sidereal_orbit,
     unsigned long long real_seconds_per_orbit)
  : m_Name(name)
  , m_Type(type)
  , m_Stepper(steps_per_360_degree, pin_1, pin_2, pin_3, pin_4)
  , m_ReedContact(reed_pin)
  , m_StepsPerOrbit(step_for_sidereal_orbit)
  , m_RealSecondsPerOrbit(real_seconds_per_orbit)
{
  pinMode(m_ReedContact, INPUT);
  m_Pins[0] = pin_1;
  m_Pins[1] = pin_2;
  m_Pins[2] = pin_3;
  m_Pins[3] = pin_4;
}

PlanetType Planet::getType() const
{
  return m_Type;
}

unsigned long Planet::getSteps() const
{
  return m_StepsMade;
}

void Planet::resetSteps()
{
  m_StepsMade = 0;
}

void Planet::makeStep()
{
  makeSteps(1);
}

void Planet::makeSteps(int steps)
{
  //Reverse direction
  m_Stepper.step(-steps);
  m_StepsMade += steps;
}

void Planet::setSpeed(int speed)
{
  m_Stepper.setSpeed(speed);
}

unsigned long long Planet::getSecondsBetweenSteps() const
{
  return m_RealSecondsPerOrbit / m_StepsPerOrbit;
}

unsigned int Planet::getPositionForCurrentTime() const
{
  unsigned long long seconds_for_current_position = now() % m_RealSecondsPerOrbit;
  return seconds_for_current_position / getSecondsBetweenSteps();
}

void Planet::stopMotor()
{
  for(int i=0; i<4; ++i)
  {
    digitalWrite(m_Pins[i], LOW);
  }
}

String Planet::getName() const
{
  return m_Name;
}

bool Planet::isReferencePositionReached()
{
  for(int i=0; i < 100; ++i)
  {
    if(digitalRead(m_ReedContact) == 1)
      return true;
  }
  return digitalRead(m_ReedContact) == 1;
}
