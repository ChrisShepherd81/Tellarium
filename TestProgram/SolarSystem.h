
#ifndef SOLARSYSTEM_H

#define SOLARSYSTEM_H

#include "Planet.h"

#define NUMBER_OF_PLANETS 4
#define MOTOR_DEGREES_PER_STEP 3.6
#define MOTOR_STEPS_PER_RESOLUTION 100 // 360degree / MOTOR_DEGREES_PER_STEP

#define MERCURY_PINS 46, 47, 48, 49
#define MERCURY_ZERO_POS_PIN 50 
#define MERCURY_REAL_STEPS_PER_ORBIT 300
#define MERCURY_REAL_SECONDS_PER_STEP 26322
Planet Mercury("Mercury", PlanetType::Mercury, MOTOR_STEPS_PER_RESOLUTION, MERCURY_PINS, MERCURY_ZERO_POS_PIN, MERCURY_REAL_STEPS_PER_ORBIT, MERCURY_REAL_SECONDS_PER_STEP);

#define VENUS_PINS 38, 39, 40, 41
#define VENUS_ZERO_POS_PIN 42
#define VENUS_REAL_STEPS_PER_ORBIT 300
#define VENUS_REAL_SECONDS_PER_STEP 67234
Planet Venus("Venus", PlanetType::Venus, MOTOR_STEPS_PER_RESOLUTION, VENUS_PINS, VENUS_ZERO_POS_PIN, VENUS_REAL_STEPS_PER_ORBIT, VENUS_REAL_SECONDS_PER_STEP);

#define EARTH_PINS 30, 31, 32, 33
#define EARTH_ZERO_POS_PIN 34 
#define EARTH_REAL_STEPS_PER_ORBIT 300
#define EARTH_REAL_SECONDS_PER_STEP 109290
Planet Earth("Earth", PlanetType::Earth, MOTOR_STEPS_PER_RESOLUTION, EARTH_PINS, EARTH_ZERO_POS_PIN, EARTH_REAL_STEPS_PER_ORBIT, EARTH_REAL_SECONDS_PER_STEP);

#define MARS_PINS 22, 23, 24, 25
#define MARS_ZERO_POS_PIN 26
#define MARS_REAL_STEPS_PER_ORBIT 300
#define MARS_REAL_SECONDS_PER_STEP 205554
Planet Mars("Mars", PlanetType::Mars, MOTOR_STEPS_PER_RESOLUTION, MARS_PINS, MARS_ZERO_POS_PIN, MARS_REAL_STEPS_PER_ORBIT, MARS_REAL_SECONDS_PER_STEP);

#define GLOBAL_STEP_DELAY 4L * 60L * 1000L * 1000L / MOTOR_STEPS_PER_RESOLUTION / 10L

Planet* SolarSystem[NUMBER_OF_PLANETS];
void SetUpSolarSystem()
{
  Mercury.setSpeed(10);
  Venus.setSpeed(10);
  Earth.setSpeed(10);
  Mars.setSpeed(10);
  SolarSystem[0] = &Mercury;
  SolarSystem[1] = &Venus;
  SolarSystem[2] = &Earth;
  SolarSystem[3] = &Mars;
}

bool AllPlanetsInReferencePosition()
{
  for(int i = 0; i < NUMBER_OF_PLANETS; ++i)
  {
    if(!SolarSystem[i]->isReferencePositionReached())
    {
      return false;
    }
  }

  return true;
}

void StopAllMotors()
{
  for(int i = 0; i < NUMBER_OF_PLANETS; ++i)
  {
    SolarSystem[i]->stopMotor();
  }
}

void SolarSystemStep(int steps, bool keep_in_reference_position = true)
{
  unsigned long last_step_time = 0;
  
  while (steps > 0)
  {
    unsigned long now = micros();
    // move only if the appropriate delay has passed:
    if (now - last_step_time >= GLOBAL_STEP_DELAY)
    {
      // get the timeStamp of when you stepped:
      last_step_time = now;
      // decrement the steps left:
      steps--;
      for(int i = 0; i < NUMBER_OF_PLANETS; ++i)
      {
        if(keep_in_reference_position && SolarSystem[i]->isReferencePositionReached())
          continue;
        else  
          SolarSystem[i]->makeSteps(1);
      }
    }
  }
}

void GoToStartPosition()
{
  SetUpSolarSystem();
  SolarSystemStep(5, false);

  while(!AllPlanetsInReferencePosition())
  {
    SolarSystemStep(1);
  }
  
  StopAllMotors();
}

#endif // SOLARSYSTEM_H
