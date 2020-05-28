#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

static const float limitDistance = 0.5;
static float now = 0.0;
static int step = 0;
static int flag = 0;
static ros::Publisher vel_pub;

void subCallback(const sensor_msgs::LaserScan::ConstPtr& scan) {
    float now_min = 100;
    for (int i = 0; i < 360; i++) {
        if (scan->ranges[i] < now_min) {
            now_min = scan->ranges[i];
        }
    }
    ROS_INFO("%f", now_min);
    if (now_min < limitDistance && step == 0) {
        now = now_min;
        step++;
    }
    if (now_min < now) {
        now = now_min;
        step++;
    }
    if (step > 3 && flag == 0) {

        system("rosrun my_vel_package stop");
        ROS_INFO("find obstacle_detect, stop!");
        flag = 1;
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "obstacle_detect");
    ROS_INFO("start detect obstacle");

    ros::NodeHandle nh;
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::Subscriber sub = nh.subscribe("/scan", 10, subCallback);
    ros::spin();
    
    return 0;
}