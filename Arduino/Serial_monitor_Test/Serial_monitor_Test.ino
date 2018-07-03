const int ledPin = 13; 
const int BUTTON_PIN = 2;

int buttonState = 0;
unsigned long time;
void setup() 
{
    pinMode(ledPin, OUTPUT);
    pinMode(BUTTON_PIN, INPUT);
}

void loop() 
{
   int buttonState = digitalRead(BUTTON_PIN);
   if(buttonState == HIGH)
   {
    digitalWrite(ledPin, HIGH);
    Serial.println("Time: ");
    time = millis();
    Serial.print(time);
    delay(1000);
    
   }
   else
   {
    digitalWrite(ledPin, LOW);
   }

    
}
