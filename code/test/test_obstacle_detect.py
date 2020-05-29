import subprocess

def test_obstacle_forward():
	test = subprocess.Popen("rosrun my_vel_package move_forward");
	test2 = subprocess.Popen("rosrun obstacle my_obstacle_detect > test_result_forward.txt");

def test_obstacle_backward():
	test = subprocess.Popen("rosrun my_vel_package move_backward");
	test2 = subprocess.Popen("rosrun obstacle my_obstacle_detect > test_result_backward.txt");

def test_obstacle_right():
	


def test_obstacle_left():


