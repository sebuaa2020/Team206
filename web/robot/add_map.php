<?php
session_start();
if (!isset($_SESSION['logged'])) {
    echo '<script>alert("请登录后访问页面！")</script>';
    header('Location: index.html');
    exit();
}
include "connectDB.php";
$name = $_POST['name'];
$result = mysqli_query($conn, "INSERT INTO map(uid, name, src) VALUES ('".$_SESSION['uid']."', '$name', '#')");
$_SESSION['map'] = $name;
header('Location:intelligent.php');
