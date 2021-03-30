#include <DRV8835MotorShield.h>
// constants won't change. Used here to set a pin number:
int solenoidPin = 4;
const int FLEX_PIN = A5; // Pin connected to voltage divider output
#define WINDOW_SIZE 50
int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;
// Variables will change:
int solenoidState = LOW; // ledState used to set the LED
int count = 0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)
DRV8835MotorShield motors;
void setup() {
  // set the digital pin as output:
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  pinMode(FLEX_PIN, INPUT);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  unsigned long currentMillis = millis();
    
  int flexADC = analogRead(FLEX_PIN);
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (solenoidState == LOW) {
      //Serial.println("On");
      solenoidState = HIGH;
       motors.setM2Speed(100);
    } else {
      solenoidState = LOW;
       motors.setM2Speed(00);
    }
  }
  
  if(solenoidState == HIGH){
    flexADC -= 50;//42;
    count =0;
    digitalWrite(solenoidPin, solenoidState);
    //Serial.println("Closing1");
     
    }

   else{
    if (count%6 == 0){
      digitalWrite(solenoidPin, solenoidState);
     // Serial.println("Closing2");
      }
     else{
     digitalWrite(solenoidPin, HIGH);
     //Serial.println("Opening");
     }
    }
   

 
    
   SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  READINGS[INDEX] = flexADC;           // Add the newest reading to the window
  SUM = SUM + flexADC;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;      // Divide the sum of the window by the window size for the result
  Serial.println(AVERAGED);
    // set the LED with the ledState of the variable:
  
    
  count++;
  delay(10);
}
