#include <DRV8835MotorShield.h>

int solenoidPin = 4;
const int FLEX_PIN = A5;

int solenoidState = HIGH;

#define WINDOW_SIZE 1
int INDEX = 0;
int VALUE = 0;
int SUM = 0;
int READINGS[WINDOW_SIZE];
int AVERAGED = 0;

int error = 0;
int desiredPosition = 650;
float deltaError;
float integralError;
int oldError = 0;
int deltaT = 0;
unsigned long previousMillis = 0;
float kp = 3;
float ki = 0;//0.001;
float kd = -70;
float sumError = 0;
int motorCmd = 0;

DRV8835MotorShield motors;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(solenoidPin, OUTPUT);
  pinMode(FLEX_PIN, INPUT);
  solenoidState = HIGH;
  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();
  solenoidState = HIGH;
  deltaT = currentMillis - previousMillis;
  previousMillis = currentMillis;
  
  int flexReading = analogRead(FLEX_PIN);
  error = desiredPosition - flexReading;
  
  deltaError = (error - oldError)/ deltaT;
  integralError += error*deltaError;

  sumError = (kp*error)+(ki*integralError)+(kd*deltaError);

  if (sumError < 0 ){
    solenoidState = HIGH;
    sumError = sumError*-1;
    motorCmd = min(sumError,200);
    motors.setM2Speed(motorCmd);
    }

  else{
    //solenoidState = LOW;
    //Serial.println("Opening---------------");
    motors.setM2Speed(0);
  }
  digitalWrite(solenoidPin, solenoidState);

  SUM = SUM - READINGS[INDEX];       // Remove the oldest entry from the sum
  READINGS[INDEX] = flexReading;           // Add the newest reading to the window
  SUM = SUM + flexReading;                 // Add the newest reading to the sum
  INDEX = (INDEX+1) % WINDOW_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

  AVERAGED = SUM / WINDOW_SIZE;

  Serial.print("Reading:");
  Serial.print(flexReading);
  
  Serial.print(", ");
   Serial.print("Error:");
  Serial.print(error);
  Serial.print(", ");
  Serial.print("Desired:");
  Serial.println(desiredPosition);
  //Serial.print(", ");
  //Serial.println((kp*error)+(ki*integralError)+(kd*deltaError));
  

  
}
