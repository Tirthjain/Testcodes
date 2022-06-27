#include <ros.h>
#include <geometry_msgs/Twist.h>
ros::NodeHandle nh;
geometry_msgs::Twist msg;
//pwm 2 dir 2 left motor
//pwm1 dir 1 right motor
//pin 2, 3 right motor
//pin 4. 5 left motor
void roverCallBack(const geometry_msgs::Twist& cmd_vel)
{
  float vx = cmd_vel.linear.x ;
  float vy = cmd_vel.linear.y ;
  float vz = cmd_vel.linear.z ;
  float ax = cmd_vel.angular.x ;
  analogWrite(3, vx);
  analogWrite(5, vy);
  digitalWrite(2, vz);
  digitalWrite(4, ax);
}
ros::Subscriber <geometry_msgs::Twist> sub("/cmd_vel", roverCallBack);
void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  // put your main code here, to run repeatedly:
  nh.spinOnce();
  delay(1);
}
