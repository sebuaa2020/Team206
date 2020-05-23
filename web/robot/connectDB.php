<?php
$host = "localhost:3306";
$user = "root";
$password = "";
$dbname = "robot";

$conn = new mysqli($host, $user, $password, $dbname);
if ($conn->connect_error) {
    die("数据库连接失败: " . $conn->connect_error);
}