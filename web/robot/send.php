<?php

$PORT = 9999;
$client = socket_create(AF_INET, SOCK_STREAM, SOL_TCP); //创建socket/参数1:代表IPV4/参数2：流传输/参数3：TCP/
$result = socket_connect($client, "192.168.3.2", $PORT); //向指定地址/端口发出连接请求，连接结果返回到result
if ($result == false) {  //这里我们简单的对连接结果进行响应/为了Debug方便
    echo "ERROR CONNECT\n";
    die();
} else {
    echo "CONNECTED\n";
}

//已建立连接，准备发送数据
$data = $_POST['instruction'];
socket_write($client, $data);
socket_close($client); //关闭socket

