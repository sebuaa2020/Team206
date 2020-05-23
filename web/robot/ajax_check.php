<?php
session_start();
include "connectDB.php";

$username = isset($_POST["username"])?$_POST["username"]:'';
$password = isset($_POST["password"])?$_POST["password"]:'';
$msg='';

$result = mysqli_query($conn, "SELECT * FROM user WHERE username = '$username'");
if ($result->num_rows > 0) {
    $row = mysqli_fetch_assoc($result);
    if ($row["password"] != $password) {
        $msg ="用户名或密码错误 X";
    } else{
        $_SESSION['logged'] = $username;
        $_SESSION['uid'] = $row['uid'];
        $msg = 'success';
        //header('Location: welcome.php');
    }
} else {
    $msg ="未注册用户 X";
}

echo json_encode($msg);


