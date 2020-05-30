#include<ros/ros.h>
#include<geometry_msgs/Twist.h>
#include<fstream>
#define runningTime 100000
#define waitTime 100000
using namespace std;
int main(int argc, char** argv) {
    ros::init(argc, argv, "vel_ctrl");
    ros::NodeHandle n;
    ros::Publisher vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    int time = 0;
    ros::Rate loopRate(10);
	geometry_msgs::Twist vel_cmd;
	
	float x,y,z,d;
	ifstream infile;
	infile.open("test_baseMove_data.txt");
	
	while(infile >> d){
		x = d;
    	infile>>y;
    	infile>>z;
		
		time = runningTime;
		while(ros::ok() && time > 0) {		//测试样例进行测试
			geometry_msgs::Twist vel_cmd;

			vel_cmd.linear.x = x;		
			vel_cmd.linear.y = y;	
			vel_cmd.linear.z = 0;

			vel_cmd.angular.x = 0;
			vel_cmd.angular.y = 0;
			vel_cmd.angular.z = z;

			if(x > 0){
				ROS_INFO("The Robot should move forward");
			}else if(x < 0){
				ROS_INFO("The Robot should move back");
			}else if(y > 0){
				ROS_INFO("The Robot should move left");
			}else if(y < 0){
				ROS_INFO("The Robot should move right");	
			}else if(z > 0){
				ROS_INFO("The Robot should turn left");
			}else if(z < 0){
				ROS_INFO("The Robot should turn right");
			}
			time--;
			vel_pub.publish(vel_cmd);
			loopRate.sleep();
			ros::spinOnce();
		}

		time = waitTime;
		while(ros::ok() && time > 0) {		//不同测试用例间停顿时间
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
	}
	infile.close();
    return 0;
}
//vel_cmd.linear.x 是机器人前后平移运动速度，正值往前，负值往后，单位是“米/秒”；
//vel_cmd.linear.y 是机器人左右平移运动速度，正值往左，负值往右，单位是“米/秒”；
//vel_cmd.angular.z（注意 angular）是机器人自转速度，正值左转，负值右转，单位是 “弧度/秒”；
//ROS_INFO("Waiting for the move_base action server to come up");	这个是ros.h的基本参数
//结构体的其余参数为0即可
//测试数据取值范围在-0.1~0.1