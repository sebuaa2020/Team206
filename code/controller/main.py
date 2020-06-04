import socket
import threading
import os
import time
import subprocess

gazebo_str = "roslaunch wpr_simulation wpb_simple.launch"
vel_str = "rosrun my_vel_package "
map_name = ""
targets = []
x_in_img = 0.0
y_in_img = 0.0
x_img = 0.0
y_img = 0.0


def attributeTask(mstr):
    global p_move, p_map, p_nav, start, save_now, load_now, deliver_now

    if save_now:
        p_map = subprocess.Popen('rosrun map_server map_saver -f ' + mstr,shell=True)
        p_map.wait()
        p_map = subprocess.Popen('cp ~/controller/' + mstr +  '.pgm ~/demo_ws/src/wpb_home/wpb_home_tutorials/maps/map.pgm', shell=True)
        p_map.wait()
        p_map = subprocess.Popen('cp ~/controller/' + mstr +  '.yaml ~/demo_ws/src/wpb_home/wpb_home_tutorials/maps/map.yaml', shell=True)
        p_map.wait()
        p_map = subprocess.Popen('python send.py ' + mstr + ".pgm", shell=True)
        p_map.wait()
        save_now = False
        return
    
    if load_now:
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

        # attributeTask(rcvStr)


p_move = None
p_map = None
p_nav = None
start = False
save_now = False
load_now = False
deliver_now = False

# gazebo = subprocess.Popen(gazebo_str, shell=True)

setTcp()

