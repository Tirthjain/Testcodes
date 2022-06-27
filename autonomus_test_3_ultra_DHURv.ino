#include <HCSR04.h>
UltraSonicDistanceSensor right_sensor(13, 10);
UltraSonicDistanceSensor centre_sensor(12,9);
UltraSonicDistanceSensor left_sensor(11,8);
#define dir_left 2
#define pwm_left 3
#define dir_right 4
#define pwm_right 5


void setup () {
  pinMode(dir_left, OUTPUT);
  pinMode(dir_right,OUTPUT);
  pinMode(pwm_left, OUTPUT);
  pinMode(pwm_right,OUTPUT);
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void left()
{
  digitalWrite(dir_left,HIGH);
  digitalWrite(dir_right,LOW);
  analogWrite(pwm_right,0);
  analogWrite(pwm_left,80);
  delay(5000);
}
void right()
{
  digitalWrite(dir_left,LOW);
  digitalWrite(dir_right,HIGH);
  analogWrite(pwm_right,80);
  analogWrite(pwm_left,0);
  delay(5000);
}
void forward()
{
  digitalWrite(dir_left,LOW);
  digitalWrite(dir_right,LOW);
  analogWrite(pwm_right,80);
  analogWrite(pwm_left,80);
  delay(5000);
}
void sharp_right(int speed)
{
    digitalWrite(dir_left,HIGH);
    digitalWrite(dir_right,LOW);
    analogWrite(pwm_left, speed);
    analogWrite(pwm_right,speed);
    delay(5000);
}
void sharp_left(int speed)
{
    digitalWrite(dir_left,LOW);
    digitalWrite(dir_right,HIGH);
    analogWrite(pwm_left, speed);
    analogWrite(pwm_right, speed);
    delay(5000);
}
void loop()
{
forward();
right();
left();
sharp_right(80);
sharp_left(80);
}
