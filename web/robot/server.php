<?php

$server = socket_create(AF_INET, SOCK_STREAM, SOL_TCP); //创建socket/参数解释同客服端
socket_bind($server, "0.0.0.0", 9999); //绑定端口和IP/0.0.0.0表示允许任意地址发起连接/9999表示允许9999端口号进行连接
socket_listen($server); //进入监听

$connection = socket_accept($server);//接受请求并建立连接
$data = socket_read($connection, 1024); //接受数据
echo $data; //打印数据

socket_close($server);//关闭socket
