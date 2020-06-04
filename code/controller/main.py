import socket
import threading
import os
import time
import subprocess

gazebo_str = "roslaunch wpr_simulation wpb_simple.launch"
vel_str = "rosrun my_vel_package "
map_name = ""
targets = []
nav_input = []


def attributeTask(mstr):
    global p_move, p_map, p_nav, start, save_now, load_now, deliver_now

    if deliver_now and mstr[0].isdigit():
        mes = float(mstr)
        nav_input.append(mes)
        if len(nav_input) == 4:
            half_x = nav_input[2] * 1.0 / 2
            half_y = nav_input[3] * 1.0 / 2
            x = (nav_input[0] - 300.0) * 1.0 / half_x * 25
            y = (300.0 - nav_input[1]) * 1.0 / half_y * 25
            targets.append([x, y])
            p_nav = subprocess.Popen("rosrun my_nav_package simple_goal " + str(x) + " " + str(y), shell=True)
            p_nav.wait()
            print("this nav is over!")
            nav_input.clear()


    if save_now:
        p_map = subprocess.Popen('rosrun map_server map_saver -f ' + mstr,shell=True)
        p_map.wait()
        p_map = subprocess.Popen('python edit_yaml.py ' + mstr + ".yaml", shell=True)
        p_map.wait()
        p_map = subprocess.Popen('cp ~/controller/' + mstr +  '.pgm ~/demo_ws/src/wpb_home/wpb_home_tutorials/maps/map.pgm', shell=True)
        p_map.wait()
        p_map = subprocess.Popen('cp ~/controller/' + mstr +  '.yaml ~/demo_ws/src/wpb_home/wpb_home_tutorials/maps/map.yaml', shell=True)
        p_map.wait()
        p_map = subprocess.Popen('python send.py ' + mstr + ".pgm", shell=True)
        p_map.wait()
        save_now = False
        return
    
    if load_now and mstr != "load_now" and mstr != "recover":
        p_map = subprocess.Popen('cp ~/controller/' + mstr +  '.pgm ~/demo_ws/src/wpb_home/wpb_home_tutorials/maps/map.pgm', shell=True)
        p_map.wait()
        p_map = subprocess.Popen('cp ~/controller/' + mstr +  '.yaml ~/demo_ws/src/wpb_home/wpb_home_tutorials/maps/map.yaml', shell=True)
        p_map.wait()
        load_now = False
        return

    if start:
        obstacle = subprocess.Popen("rosrun obstacle obstacle_detect", shell=True)
        start = False
        time.sleep(2)

    if mstr == "turn_left":
        if p_move is None:
            p_move = subprocess.Popen(vel_str + "turn_left", shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen(vel_str + "turn_left", shell=True) 
    if mstr == "turn_right":
        if p_move is None:
            p_move = subprocess.Popen(vel_str + "turn_right", shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen(vel_str + "turn_right", shell=True)
    if mstr == "forward":
        if p_move is None:
            p_move = subprocess.Popen(vel_str + "move_forward", shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen(vel_str + "move_forward", shell=True)
    if mstr == "back":
        if p_move is None:
            p_move = subprocess.Popen(vel_str + "move_backward", shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen(vel_str + "move_backward", shell=True)
    if mstr == "stop":
        if p_move is None:
            p_move = subprocess.Popen(vel_str + "stop", shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen(vel_str + "stop", shell=True)

    if mstr == "build_map":
        time.sleep(2)
        os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_tutorials hector_mapping.launch; exec bash\"'")
    if mstr == "save":
        if p_move is None:
            p_move = subprocess.Popen(vel_str + "stop", shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen(vel_str + "stop", shell=True)
        save_now = True

    if mstr == "load_map":
        load_now = True

    if mstr == "deliver":
        if not deliver_now:
            deliver_now = True
            os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_tutorials nav.launch\"'")
            time.sleep(2)

    if mstr == "recover":
        size = len(targets)
        for i in range(size - 1, -1, -1):
            x = str(targets[i][0])
            y = str(targets[i][1])
            p_nav = subprocess.Popen("rosrun my_nav_package simple_goal " + x + " " + y, shell=True)
            p_nav.wait()
        p_nav = subprocess.Popen("rosrun my_nav_package simple_goal 0.0 0.0", shell=True)
        p_nav.wait()
        targets.clear()


def setTcp():

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('localhost', 9999))
    server.listen(5)
    while True:
        print('wait for connection......')
        sock, addr = server.accept()
        print('client addr: ', addr)
        
        data = sock.recv(1024)
        rcvStr = data.decode('utf-8')
        print(rcvStr, end="\n\n")

        attributeTask(rcvStr)


p_move = None
p_map = None
p_nav = None
start = False
save_now = False
load_now = False
deliver_now = False

gazebo = subprocess.Popen(gazebo_str, shell=True)

setTcp()

