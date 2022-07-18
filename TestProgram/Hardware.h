#ifndef HARDWARE_H
#define HARDWARE_H

#include <Button.h>
#include <DCF77.h>

#define BUTTON_PIN 53
Button FastForwardButton(BUTTON_PIN);

#define DCF_PIN 2
#define DCF_INTERRUPT 0

class DCFClock
{
public:
  DCFClock() : m_dcf(DCF_PIN,DCF_INTERRUPT)
  {
    m_dcf.Start();
  }

  bool UpdateTime()
  {
    time_t DCFtime = m_dcf.getTime();
    if (DCFtime!=0)
    {
      setTime(DCFtime);
      return true;
    }   
    return false; 
  }

private:
  DCF77 m_dcf; 
};

#endif //HARDWARE_H
