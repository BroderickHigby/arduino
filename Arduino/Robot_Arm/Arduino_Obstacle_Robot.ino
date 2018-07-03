#define Trig 13
#define Echo 10
#include <Servo.h>
#include <AFMotor.h>


/*******************************
 * *Where we define variables **
 *******************************/
AF_DCMotor motor2(3);
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
  look_left = time / 58;
}

void calculate_forward() {
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  time = pulseIn(Echo, HIGH);
  look_straight = time / 58;
  Serial.println(look_straight); // Output to port
}

void calculate_right()
{
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  time = pulseIn(Echo, HIGH);
  look_right = time / 58;
}
