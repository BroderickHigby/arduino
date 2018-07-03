//example program to control a 6 axis servo based robotic arm 
//using 6 potentiomenters and an arduino uno. In my build the pots
//arm built into a 1:1 scale model of the arm, so the arm moves exactly
//as i move the model.
//
//Author:  David Zimmer <dzzie@yahoo.com> 
//Site:  http://sandsprite.com
//license: BSD

#include <Servo.h>

Servo s1;  //base rotation
Servo s2;  //lower arm joint
Servo s3;  //upper arm joint
Servo s4;  //upper arm rotation
Servo s5;  //wrist
Servo s6;  //hand rotation

int modeSwitchPin = 2; 

//servo pins
int sp1 = 3;
int sp2 = 5;
int sp3 = 6;
int sp4 = 9;
int sp5 = 10;
int sp6 = 11;

//pot pins
int pp1 = A0;
int pp2 = A1;
int pp3 = A2;
int pp4 = A3;
int pp5 = A4;
int pp6 = A5;

int lastPos[7] = {0, 0, 0, 0, 0, 0, 0};

//          x, 1,  2,   3,  4, 5, 6  you must set these to your system..
int calibration[7] = {0, 0, -20, -12, 0, 0, 0};
int neutralPos[7]  = {0,93,121,37,80,86,80};
bool moved = false;
bool debug = false;
bool inJoyStickMode = true;

void gotoNeutralPos(){
  for(int i=1; i<=6; i++) doMove(i, neutralPos[i],0);
}

void setup() {

  Serial.begin(115200);
  s1.attach(sp1);
  s2.attach(sp2);
  s3.attach(sp3);
  s4.attach(sp4);
  s5.attach(sp5);
  s6.attach(sp6);
  
  pinMode(pp1, INPUT);
  pinMode(pp2, INPUT);
  pinMode(pp3, INPUT);
  pinMode(pp4, INPUT);
  pinMode(pp5, INPUT);
  pinMode(pp6, INPUT);
  
  pinMode(modeSwitchPin, INPUT_PULLUP); //defaults to joystick mode..

}

void loop() {
  
  if(digitalRead(modeSwitchPin) == HIGH){
    inJoyStickMode = true;
    JoyStickMode();
  }
  else{
    if(inJoyStickMode){
      inJoyStickMode = false;
      gotoNeutralPos();
    }
    SerialControlMode();
  }

}


void JoyStickMode(){

  moved = false;
  int raw1 = analogRead(pp1);
  int raw2 = analogRead(pp2);
  int raw3 = analogRead(pp3);
  int raw4 = analogRead(pp4);
  int raw5 = analogRead(pp5);
  int raw6 = analogRead(pp6);
  
  int pos1 = map(raw1, 0, 1023, 0, 180);
  int pos2 = map(raw2, 0, 1023, 180, 0); //note i accidently swapped which side my +/- were on so I have to swap the mapping..(arm was acting in reverse of my motion)
  int pos3 = map(raw3, 0, 1023, 0, 180);
  int pos4 = map(raw4, 0, 1023, 0, 180); //not implemented in joystick yet
  int pos5 = map(raw5, 0, 1023, 0, 180);
  int pos6 = map(raw6, 0, 1023, 0, 180); //not implemented in joystick yet
  
  if(abs(pos1 - lastPos[1]) > 2) doMove(1, pos1, raw1);
  if(abs(pos2 - lastPos[2]) > 2) doMove(2, pos2, raw2);
  if(abs(pos3 - lastPos[3]) > 2) doMove(3, pos3, raw3);
  if(abs(pos4 - lastPos[4]) > 2) doMove(4, pos4, raw4);
  if(abs(pos5 - lastPos[5]) > 2) doMove(5, pos5, raw5);
  if(abs(pos6 - lastPos[6]) > 2) doMove(6, pos6, raw6);

  if(moved){
    if(debug)
      Serial.println();
    else{
      Serial.print(pos1);Serial.print(',');
      Serial.print(pos2);Serial.print(',');
      Serial.print(pos3);Serial.print(',');
      Serial.print(pos4);Serial.print(',');
      Serial.print(pos5);Serial.print(',');
      Serial.print(pos6);   
      Serial.println();
    }
  }

}



void SerialControlMode(){

  String n;
  Servo* s = 0;

  int i=1;
  int pos[7] = {0, 0, 0, 0, 0, 0, 0};
  char tmp[100];
  char *t = &tmp[0];

  //expected input 6 csv numbers for servo positions \n
  //0,0,0,0,0,0\n
  while(!Serial.available()){
    delay(1);
    if(digitalRead(modeSwitchPin) == HIGH) return; //they entered joystick mode..
  }
        
  n = Serial.readStringUntil('\n');
  
  if(n.length() >= 100){
    Serial.println("Invalid to long!");
    return;
  }

  strcpy(tmp,n.c_str());

  while(i < 7){
      pos[i] = atoi(t);
      i++;
    if(i!=7){
      while(*t != ','){
        if(*t == 0){i=7; break;}
        t++;
      }
    }
    t++;
  }

  if(i!=7){
    Serial.print("Invalid command string i=");
    Serial.println(i);
    Serial.println();
    return;
  }

  if(debug){
    Serial.print("Parsed input: ");
    for(i=1; i<=6; i++){
      Serial.print(pos[i]);
      Serial.print( (i==6 ? '\n' : ',' ) );
    }
  }

  bool isEmpty = true;
  for(i=1; i<=6; i++){
    if(pos[i] != 0){ isEmpty = false; break; }
  }

  if(!isEmpty){
    for(i=1; i<=6; i++){
      if( pos[i] != lastPos[i] ) doMove(i,pos[i],0);
    }
  }

  Serial.println("OK");

}

Servo* getServo(int index){

  switch(index){
    case 1: return &s1;
    case 2: return &s2;
    case 3: return &s3;
    case 4: return &s4;
    case 5: return &s5;
    case 6: return &s6;
  }

  return 0;
}

void doMove(int index, int pos, int raw){
  
  Servo* s = getServo(index);
  if(s==0) return;

  lastPos[index] = pos;
  if(debug) dbg(index,raw,pos);
  s->write(pos + calibration[index]);
  moved = true;

}


void dbg(int index, int raw, int pos){
  
  Serial.print(index);
  Serial.print(") ");
  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print(" Mapped: ");  
  Serial.println(pos); 
  
}
