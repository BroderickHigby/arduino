#include <SoftwareSerial.h>

#define rxPin 3
#define txPin 4

SoftwareSerial XSERIAL = SoftwareSerial(rxPin,txPin);


void setup() {
  // put your setup code here, to run once:
    XSERIAL.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
    XSERIAL.println("Hello Brody!!!");
    delay(1000);

}
