#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <stdlib.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
    ros::init(argc, argv, "simple_goal");
    MoveBaseClient ac("move_base", true);
    
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("Waiting for the move_base action server to come up");
    }
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

    double target_x, target_y;

    target_x = strtod(argv[1], NULL);
    target_y = strtod(argv[2], NULL);

    ROS_INFO("destination is x: %f, y: %f", target_x, target_y);

    goal.target_pose.pose.position.x = target_x;
    goal.target_pose.pose.position.y = target_y;
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
    ac.waitForResult();
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("get to the destination successfully!");
    else
        ROS_INFO("The base failed to reach the destination");
    return 0;
}