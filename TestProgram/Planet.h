#ifndef PLANET_H
#define PLANET_H

#include <Arduino.h>
#include <Stepper.h>
#include <Button.h>

enum class PlanetType{Mercury, Venus, Earth, Mars, Invalid};

class Planet
{
public:
  Planet(String name, PlanetType type,
         int steps_per_360_degree,
         int pin_1, int pin_2, int pin_3, int pin_4,
         int reed_pin,
         unsigned long real_seconds_per_step);

  PlanetType getType() const;  
  String getName() const;
  unsigned long getSteps() const;

  bool isReferencePositionReached();
  void resetSteps();

  void makeStep();
  void makeSteps(int steps);
  void setSpeed(int speed);
  void searchZeroPosition();

private:
  String m_Name;
  PlanetType m_Type;
  Stepper m_Stepper;
  Button m_ReedContact;
  unsigned long m_RealSecondsPerStep;
  
  unsigned long m_StepsMade = 0;
};

#endif // PLANET_H
