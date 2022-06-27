#include <ros.h>
#include <HCSR04.h>
#include "MPU9250.h"
#include <geometry_msgs/Twist.h>
#include <ArduinoHardware.h>
MPU9250 mpu;
UltraSonicDistanceSensor distanceSensor(7, 6);
float a,b,c = 0;
ros::NodeHandle  nh;
geometry_msgs::Twist msg;
ros::Publisher imu("/imu/ul", &msg);
void setup() {
  Serial.begin(115200);
  nh.initNode();
  nh.advertise(imu);
  Wire.begin();
  delay(2000);
  mpu.setup(0x68);
}

void loop() {
  if (mpu.update()) {
    static uint32_t prev_ms = millis();
    if (millis() > prev_ms + 25) {
      c = mpu.getYaw();
      a = mpu.getRoll();
      b = mpu.getPitch();
      prev_ms = millis();
    }
  }
  msg.linear.x = distanceSensor.measureDistanceCm();
  msg.angular.x = a;
  msg.angular.y = b;
  msg.angular.z = c;
  
  imu.publish(&msg);
  nh.spinOnce();
}
