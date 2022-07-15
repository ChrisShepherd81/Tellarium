#include "Planet.h"

Planet::Planet(String name, PlanetType type,
     int steps_per_360_degree,
     int pin_1, int pin_2, int pin_3, int pin_4,
     int reed_pin,
     unsigned long real_seconds_per_step)
  : m_Name(name)
  , m_Type(type)
  , m_Stepper(steps_per_360_degree, pin_1, pin_2, pin_3, pin_4)
  , m_ReedContact(reed_pin)
  , m_RealSecondsPerStep(real_seconds_per_step)
{
  m_ReedContact.begin();
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
  m_Stepper.step(steps);
  m_StepsMade += steps;
}

void Planet::setSpeed(int speed)
{
  m_Stepper.setSpeed(speed);
}

String Planet::getName() const
{
  return m_Name;
}

bool Planet::isReferencePositionReached()
{
  return m_ReedContact.pressed();
}
