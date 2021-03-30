#include <DRV8835MotorShield.h>

#define LED_PIN 13

DRV8835MotorShield motors;
void setup() {
  // put your setup code here, to run once:
 pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(LED_PIN, HIGH);
 motors.setM1Speed(100);
  /*
  for (int speed = 0; speed <= 400; speed++)
  {
    
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  */
}
