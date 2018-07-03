void setup() 
{
  Serial.begin(115200);
  //The servo attaches to the servo potentiometer
  base.attach(sp1);
  lArm.attach(sp2);
  uArm.attach(sp3);
  armRotate.attach(sp4);
  wrist.attach(sp5);
  hand.attach(sp6);
  
  pinMode(pp1, INPUT);
  pinMode(pp2, INPUT);
  pinMode(pp3, INPUT);
  pinMode(pp4, INPUT);
  pinMode(pp5, INPUT);
  pinMode(pp6, INPUT);
  
  pinMode(modeSwitchPin, INPUT_PULLUP); //defaults to joystick mode..

}

void loop() 
{ 
  if(digitalRead(modeSwitchPin) == HIGH)
  {
    inJoyStickMode = true;
    JoyStickMode();
  }
  else
  {
    if(inJoyStickMode)
    {
      inJoyStickMode = false;
      gotoNeutralPos();
    }
    SerialControlMode();
  }

}
