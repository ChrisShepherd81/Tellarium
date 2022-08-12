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
  case 6:
    ReadPin();
    break;
  case 7:
    SetTime();
    break;
  case 8:
    GoToStartPosition();
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
  Serial.println("1: Run a single planet (speed=100RPM)");
  Serial.println("2: Run all planets (speed=30RPM)");
  Serial.println("3: Search planet's zero position");
  Serial.println("4: Print current time");
  Serial.println("5: Read fast forward button state");
  Serial.println("6: Read PIN");
  Serial.println("7: Set DCF77 Clock");
  Serial.println("8: Go to Start");
  Serial.println("Enter your choice:");
}

void SetTime()
{
  DCFClock dcf_clock;
  Serial.println("Waiting for DCF77 time ... ");
  Serial.println("It will take at least 2 minutes before a first time update.");
  
  while(Serial.available() <= 1)
  {
    if(dcf_clock.UpdateTime())
    {
      Serial.println("Time successfully update");
      PrintTime();
      return;
    }
    
    delay(1000);
    Serial.println("Please wait...");
  }
}

void ReadPin()
{
  Serial.println("Enter pin number:");
  int choose_pin = ReadIntFromSerial();
  Serial.println("Reading value from Pin: " + String(choose_pin));  
  
  pinMode(choose_pin, INPUT);
    
  while(Serial.available() <= 1)
  {
    Serial.println("Pin value: " + String(digitalRead(choose_pin)));
  }
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
  planet->setSpeed(10);
  planet->resetSteps(); 

  while(Serial.available() <= 1)
  {
    if(!planet->isReferencePositionReached())
    {
      planet->makeStep();
    }
    else
    {
        break;
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
  planet->setSpeed(100);
  while(Serial.available() <= 0)
  {
    planet->makeStep();
  }
  planet->stopMotor();
}

void RunAllPlanets()
{
  Serial.println("Running solar system");
  
  for(int i=0; i < NUMBER_OF_PLANETS; ++i)
  {
    Serial.println("Set speed for " + SolarSystem[i]->getName());
    SolarSystem[i]->setSpeed(30);
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
