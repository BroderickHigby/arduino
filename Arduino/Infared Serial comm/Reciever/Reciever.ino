#include <SoftwareSerial.h>
                                    `
#define rxPin 2
#define txPin 3

SoftwareSerial XSERIAL = SoftwareSerial(rxPin, txPin, false);


void setup() {
  // put your setup code here, to run once:
  XSERIAL.begin(9600);
  Serial.begin(9600);
  Serial.println("Start Listening...");
}

void loop() {
  // put your main code here, to run repeatedly:
    if(XSERIAL.available())
    {
      Serial.print((char)XSERIAL.read());
    }
}
