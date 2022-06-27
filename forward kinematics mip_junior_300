#!/usr/bin/env python3
from __future__ import print_function
import rospy
import numpy as np
import math
from sensor_msgs.msg import JointState
import sys, select, termios, tty
d2=0
t2_2=0
t1_1=0

def getKey(key_timeout):
    settings = termios.tcgetattr(sys.stdin)
    tty.setraw(sys.stdin.fileno())
    rlist, _, _ = select.select([sys.stdin], [], [], key_timeout)
    if rlist:
        key = sys.stdin.read(1)
    else:
        key = ''
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN,settings)
    return key

def fk(d,t1,t2,t3):
    pt =[[0,0,0,0.16935+d],[t1,0,0.3008,-0.055],[t2,0,0.3,-0.04510],[t3,0,0,0]]
    for i in range(4):
        h =[[np.cos(pt[i][0]),-np.sin(pt[i][0])*np.cos(pt[i][1]),np.sin(pt[i][0])*np.sin(pt[i][1]),pt[i][2]*np.cos(pt[i][0])],
        [np.sin(pt[i][0]),np.cos(pt[i][0])*np.cos(pt[i][1]),-np.cos(pt[i][0])*np.sin(pt[i][1]),pt[i][2]*np.sin(pt[i][0])],
        [0,np.sin(pt[i][1]),np.cos(pt[i][1]),pt[i][3]],
        [0,0,0,1]]
        if i == 0:
            h01=h
        elif i==1:
            h12=h
        elif i==2:
            h23=h
        elif i==3:  
            h34=h

    h02 = np.dot(h01,h12)
    h03 = np.dot(h02,h23)
    A12 = np.dot(h12,h23)
    print(np.array(A12))
    h04 = np.dot(h03,h34)
    #rospy.loginfo("x = %f, y = %f, z = %f\n",h04[0][3],h04[1][3],h04[2][3])
def main():
    rospy.init_node('try', anonymous=True)
    pub = rospy.Publisher("/joint_states",JointState,queue_size = 500)
    joint = JointState()
    joint.header.stamp = rospy.Time.now()
    joint.name = ["prismatic1","revolute1","revolute2","revolute3","EE_right","EE_left"]
    joint.velocity = []
    joint.position = [0,0,0,0,0,0]
    joint.effort = []
    pub.publish(joint)
     
    while not rospy.is_shutdown():
        x = float(input('Enter the y coordinates:'))
        y = float(input('Enter the x coordinates:'))
        z = float(input('Enter the z coordinates:'))
        temp1 = (x*x + y*y - 0.18)/0.18
        t2 = min(-math.acos(temp1),2.06)
        temp2 = 0.3*math.sin(t2)/(0.3+0.3*math.cos(t2))
        t1 = min(math.atan2(x,y) - math.atan(temp2),2.06)
        d = z  - 0.06925
        global d2
        d2 = d/100
        global t2_2
        t2_2 = t2/100
        global t1_1
        t1_1 = t1/100
        temp4 = d2
        temp5 = t2_2
        temp3 = t1_1
    while (d2 < d) and (t2_2 < t2) and (t1_1 <t1):
        joint.velocity = []
        joint.position = [d2,t1_1,t2_2,0,0,0]
        joint.effort = []
        pub.publish(joint)
        print('hello')
        rospy.Rate(10)
        d2 = d2 + temp4
        t2_2 = t2_2 + temp5
        t3_3 = t3_3 + temp3
main()
