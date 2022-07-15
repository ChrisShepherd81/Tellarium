#include "SolarSystem.h"
#include "Hardware.h"
#include "Helper.h"


void setup() {
  Serial.begin(9600);
  Serial.print("TestProgram Planetarium\n"
               "(c) 2021 Astronomische Arbeitskreis Salzkammergut\n"
               "\n\n");

  FastForwardButton.begin();
  SetUpSolarSystem();
}

void loop() {
  PrintQuery();

  switch(ReadIntFromSerial())
  {
  case 1:
	  RunPlanet();
	  break;
  case 2:
	  RunAllPlanets();
	  break;
  case 3:
    SearchForZeroPosition(); 
	  break;
  case 4:
	  PrintTime();
	  break;
  case 5:
    ReadButtonState();
    break;
  default:
  	  Serial.println("No valid choice");
  }

  Serial.println("-----------------------");
}

void PrintQuery()
{
  ClearSerial();
  Serial.println("Choose test routine to run:");
  Serial.println("1: Run a single planet (speed=30RPM)");
  Serial.println("2: Run all planets (speed=15RPM)");
  Serial.println("3: Search planet's zero position");
  Serial.println("4: Print current time");
  Serial.println("5: Read fast forward button state");
  Serial.println("Enter your choice:");
}

void SearchForZeroPosition()
{
  Planet* planet = ChoosePlanet();
  if(!planet)
  {
    Serial.println("No valid choice");
    return;
  }

  Serial.println("Searching Zero Position for " + planet->getName());
  planet->setSpeed(30);
  planet->resetSteps();

  bool zeroReachedOnes = false;  
  while(Serial.available() <= 0)
  {
    if(!planet->isReferencePositionReached())
    {
      planet->makeStep();
    }
    else
    {
      Serial.println("Reference position reached");
      Serial.println(planet->getName() + " made " +  planet->getSteps() + " steps to zero position");
      if(!zeroReachedOnes)
      {
         zeroReachedOnes = true;
         planet->resetSteps();
         //One step enough?
         planet->makeStep();
         //planet->makeSteps(5);
      }
      else
      {
        break;
      }
    }
  }

  Serial.println("Terminating zero search ...");
}

void RunPlanet()
{
  Planet* choosenPlanet = ChoosePlanet();
  if(!choosenPlanet)
  {
    Serial.println("No valid choice");
    return;
  }

  RunPlanet(choosenPlanet);
}

Planet* ChoosePlanet()
{
  Serial.print("Enter planet:\n"
                 "1: Mercury\n"
                 "2: Venus\n"
                 "3: Earth\n"
                 "4: Mars\n"
                 "Enter your choice:\n");

  switch(ReadIntFromSerial())
  {
  case 1:
    return &Mercury;
    break;
  case 2:
    return &Venus;
    break;
  case 3:
    return &Earth;
    break;
  case 4:
    return &Mars;
    break;
  default:
    return nullptr;
  }
}

void RunPlanet(Planet* planet)
{
  Serial.println("Running planet " + planet->getName());
  planet->setSpeed(30);
  while(Serial.available() <= 0)
  {
    planet->makeStep();
  }
}

void RunAllPlanets()
{
  Serial.println("Running solar system");
  
  for(int i=0; i < NUMBER_OF_PLANETS; ++i)
  {
    Serial.println("Set speed for " + SolarSystem[i]->getName());
    SolarSystem[i]->setSpeed(15);
  }

  while(Serial.available() <= 0)
  {
    for(int i=0; i < NUMBER_OF_PLANETS; ++i)
    {
      SolarSystem[i]->makeStep();
    }
  }
}

void ReadButtonState()
{
  while(Serial.available() <= 0)
  {
    if(FastForwardButton.pressed())
    {
      Serial.println("FastForwardButton pressed");
    }
    else
    {
      Serial.println("FastForwardButton released");
    }
  }
}
