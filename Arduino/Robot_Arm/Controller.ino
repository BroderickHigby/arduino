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
//Robot Arm code for loop method
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

//Driving code for loop method
 go_forward();
  calculate_forward();
  if (look_straight < 30) //If the angle of the sensor is less than 30 degrees, we will stop
  {
    Serial.println("/n first if statement");
    stop_movement();
    delay(50);

    for (angle = 90; angle >= 10; angle--)
    {
      servo.write(angle);
      delay(10);
    }
    go_backwards();      //Now we'll go backwards
    delay(150);
    //stop_movement();
    calculate_right();   //Let's figure out if we can even go right
    delay(50);
    for (angle = 10; angle <= 170; angle++)
    {
      servo.write(angle);
      delay(10);
    }
    calculate_left();
    delay(50);
    for (angle = 170; angle >= 90; angle--)
    {
      servo.write(angle);
      delay(10);
    }

    if (look_right > look_left)     //If right looks better than left, let's go right
    {

      go_right();
      delay(300);
      //stop_movement();
    }

    else                           //If left looks better than right, than let's go left
    {
      go_left();
      delay(300);
      //stop_movement();
    }

  }
  else                            //If all else fails, fuck it let's go forward
  {
    go_forward();
  }
}
