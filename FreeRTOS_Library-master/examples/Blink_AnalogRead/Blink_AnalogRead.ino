#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void TaskBlink( void *pvParameters );
void TaskAnalogRead( void *pvParameters );

//Constants defined for TEMP function
const int sensorPin = A0;
const int baselineTemp = 20.0;

// the setup function runs once when you press reset or power the board
void setup() 
{
    for(int pinNumber = 2; pinNumber < 5; pinNumber++)
      {
        pinMode(pinNumber, OUTPUT);
        digitalWrite(pinNumber, LOW);
      }
    
  // Now set up two tasks to run independently.
  xTaskCreate(
    TaskBlink
    ,  (const portCHAR *)"Blink"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 1 being the highest, and 4 being the lowest.
    ,  NULL );
  
  int sensorPin;
  xTaskCreate(
    TaskAnalogRead
    ,  (const portCHAR *) "AnalogRead"
    ,  128  // Stack size
    ,  NULL
    ,  1  // Priority
    ,  NULL );


  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlink(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}

void TaskAnalogRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
    // read the input on analog pin 0:
    int sensorVal = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorVal);
    vTaskDelay(1);  // one tick delay (30ms) in between reads for stability
 
    //CODE TO EXECUTE TEMP FUNCTION

    Serial.print("Temp sensor value: ");
    Serial.print(sensorVal);
    float voltage = ((sensorVal/1024.0) * 5.0);
    Serial.print(", Volts: ");
    Serial.print(voltage);
    Serial.print(", degrees C: ");
    //Convert volts to temp in degrees
    float temperature = (voltage - .5) * 100 + 34;
    Serial.println(temperature);
    if(temperature < baselineTemp)
    {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
    } 
    else if(temperature >= baselineTemp + 2 &&
              temperature <  baselineTemp + 4)
    {
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);           
    }
    else if(temperature >= baselineTemp + 4 &&
              temperature <  baselineTemp + 6)
      {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);     
      } 
    else if(temperature >= baselineTemp + 6)
      {
        digitalWrite(2, HIGH);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);     
      }
    delay(1);
  }
}
