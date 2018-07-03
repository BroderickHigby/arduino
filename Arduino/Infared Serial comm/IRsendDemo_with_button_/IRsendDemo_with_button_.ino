/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */


#include <IRremote.h>
const int button = 12;
IRsend irsend;
   
void setup()
{
}

void loop() 
{
  if(button == HIGH)
  {
    	for (int i = 0; i < 3; i++) 
    	{
    		irsend.sendSony(0xa90, 12);
    		delay(40);
    	}
  }
  else
  {
      Serial.print("Button not pressed");
  }
  

	delay(1000); //5 second delay between each signal burst
}
