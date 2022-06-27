#include "MPU9250.h"
#include <ros.h>
//#include <std_msgs/UInt16.h>
#include <std_msgs/Float64.h>
MPU9250 mpu;
ros::NodeHandle node_handle;

std_msgs::Float64 angle_msg;
ros::Publisher angle_publisher("angle", &angle_msg);

 void print_roll_pitch_yaw() {
    angle_msg.data=mpu.getYaw();
    angle_publisher.publish( &angle_msg );
    
}

void setup()
{
    
    Wire.begin();
    delay(2000);
   node_handle.initNode();
   node_handle.advertise(angle_publisher);
    if (!mpu.setup(0x68)) {  // change to your own address
        while (1)
        {
           
            delay(5000);
        }
    }
}

void loop() 
{
  if (mpu.update())
    {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25)
        {
           print_roll_pitch_yaw();
            prev_ms = millis();
        }
    }
    node_handle.spinOnce();
}
