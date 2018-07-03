#define Trig 13
#define Echo 10
#include <Servo.h>
#include <AFMotor.h>


/******************************
 **Where we define variables **
 ******************************/
AF_DCMotor motor2(2);
AF_DCMotor motor4(4);

Servo servo;

int angle = 90;
int look_left;
int look_right;
int look_straight;

int time;

/*********************
 ** Methods defined **
 *********************/
 
void setup() //Every Arduino method has a setup method
{ 
  //servo connects to pina 9 - a servo for the rangefinder
  servo.attach(9); 
  Serial.begin(9600); 
} 


void go_forward()
{       
  motor2.run(FORWARD);
  motor4.run(FORWARD);
  motor2.setSpeed(255); 
  motor4.setSpeed(255);  
}

void go_backwards()
{       
  motor2.run(BACKWARD);
  motor4.run(BACKWARD);
  motor2.setSpeed(255); 
  motor4.setSpeed(255); 
}

void go_right()
{
  motor2.run(FORWARD);
 // motor4.run(FORWARD);
  motor2.setSpeed(255); 
 // motor4.setSpeed(255); 
}

void go_left()
{
  // motor3.run(FORWARD);
  motor4.run(FORWARD);
  // motor3.setSpeed(255); 
  motor4.setSpeed(255); 
}

void stop_movement()  // Stop movement
{              
  motor2.run(RELEASE);
  motor4.run(RELEASE);
  Serial.begin(9600);   // set up Serial library at 9600 bps
  Serial.println("Motor");       
}

void calculate_left() // Calculates angles by  
{               
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  time = pulseIn(Echo, HIGH);
  look_left = time/58;
}

void calculate_forward(){        
   digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  time = pulseIn(Echo, HIGH);
  look_straight = time/58;
    Serial.println(look_straight); // Output to port 
}

void calculate_right()
{           
   digitalWrite(Trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(Trig, LOW);
   time = pulseIn(Echo, HIGH);
   look_right = time/58;
}


/**********************************************************************************
 **All Arduino projects also have a loop method, in addition to the setup method**
 **********************************************************************************/
void loop() 
{
  go_forward();
  calculate_forward();
    if(look_straight<30)    //If the angle of the sensor is less than 30 degrees, we will stop
    {
       stop_movement();
       delay(50);
       
       for(angle=90;angle>=10;angle--)    
       {
           servo.write(angle);
           delay(10);
       }
       go_backwards();      //Now we'll go backwards 
       delay(150);
       stop_movement(); 
       calculate_right();   //Let's figure out if we can even go right
       delay(50);
       for(angle=10;angle<=170;angle++)
       {
           servo.write(angle);
           delay(10);
       }
      calculate_left();
      delay(50);
      for(angle=170;angle>=90;angle--)
      {
         servo.write(angle);
         delay(10);
      }
  
      if(look_right > look_left)      //If right looks better than left, let's go right 
      {
 
         go_right();
         delay(300);
         //stop_movement(); //commented out for testing
      }
  
      else                           //If left looks better than right, then let's go left
      {

         go_left();
         delay(300);
         //stop_movement(); //commented out for testing
      }
       
    }  
    else                            //If all else fails, fuck it let's go forward
    {
        go_forward();
    }
}
