#include <HCSR04.h>
#include "Complex.h"
UltraSonicDistanceSensor right(13, 10);
UltraSonicDistanceSensor centre(12, 9);
UltraSonicDistanceSensor left(11, 8);
#define dir1 2
#define pwm1 3
#define dir2 4
#define pwm2 5
float r1, r2, r3 = 0;
void  motor(float p1, float p2, int d1, int d2) {
  digitalWrite(dir1, d1);
  digitalWrite(dir2, d2);
  analogWrite(pwm1, 80 - p1*1.5);
  analogWrite(pwm2, 80 + p2*1.5);
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  float r1 = left.measureDistanceCm();
  float r2 = centre.measureDistanceCm();
  float r3 = right.measureDistanceCm();
  float c2 = 1; //It will mememic r2 by having a very small
  //value so just to maximize the angle between resultant vectors
  Complex c1(r1 * 0.707, -r1 * 0.707);
  Complex c3(r3 * 0.707, r3 * 0.707);
  Complex c(0, 0);
  float k = abs(((r1 - r3) / (r1 + r3)) * 16.667 * 3.5); //k useful between range 0 and 0.58 only
  c = c1 + c3 + c2;
  //Serial.println("2");
  float ohm = 2 * (atan(c.imag() / c.real())); //285 for range between 0 to 180 degrees
  Serial.println(degrees(k));
  if (r2 < 10) {
    motor(0, 0, 1, 1);
    delay(1000);
    if (r1 > r3) {
      motor(0, 0, 0, 1);
      delay(1500);
    }
    else {
      motor(0, 0, 1, 0);
      delay(1500);
      //Serial.println("1");
    }
  }
  else if (ohm >= 0 && ohm < 60 ) motor(k * sin(ohm), k * sin(ohm), 0, 0);
  else if (ohm >= 60) motor(k * sin(ohm), k * sin(ohm), 0, 1);
  else if (ohm < 0 && ohm > -60 ) motor(k * sin(ohm), k * sin(ohm), 0, 0);
  else if (ohm <= -60) motor(k * sin(ohm), k * sin(ohm), 1, 0);
}
