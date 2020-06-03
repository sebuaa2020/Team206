#include<ros/ros.h>
#include<geometry_msgs/Twist.h>

#define runningTime 100000
#define stopTime 100000

int main(int argc, char** argv) {
    ros::init(argc, argv, "vel_ctrl");
    ros::NodeHandle n;
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    int time = 0;
    ros::Rate loopRate(10);

    time = runningTime;
    while(ros::ok() && time > 0) {
        geometry_msgs::Twist vel_cmd;

        vel_cmd.linear.x = 0;
        vel_cmd.linear.y = -0.1;
        vel_cmd.linear.z = 0;

        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 0;

        time--;
        vel_pub.publish(vel_cmd);
        loopRate.sleep();
        ros::spinOnce();
    }

    time = stopTime;
    while(ros::ok() && time > 0) {
        geometry_msgs::Twist vel_cmd;

        vel_cmd.linear.x = 0;
        vel_cmd.linear.y = 0;
        vel_cmd.linear.z = 0;

        vel_cmd.angular.x = 0;
        vel_cmd.angular.y = 0;
        vel_cmd.angular.z = 0;

        time--;
        vel_pub.publish(vel_cmd);
        loopRate.sleep();
        ros::spinOnce();
    }

    return 0;
}