<?php
session_start();
if (!isset($_SESSION['logged'])) {
    echo '<script>alert("请登录后访问页面！")</script>';
    header('Location: index.html');
    exit();
}
$username = $_SESSION['logged'];
?>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <title>首页</title>
    <link rel="stylesheet" href="css/bootstrap.css">
    <style>
        * {
            margin: 0;
            padding: 0;
            list-style: none;
            text-decoration: none;
        }

        header {
            width: 100%;
            height: 90px;
            background-color: #4C2B1C;
        }

        #name {
            float: left;
            margin-right: 10px;
        }

        #logout {
            margin-right: 5px;
            padding: 5px 5px;
            width: 50px;
            background-color: #CB602D;
            border: none;
            border-radius: 5px;
            font-size: 16px;
            float: left;
        }

        h4 {
            color: #CB602D;
            margin: 0;
        }

        header h2 {
            color: white;
            margin: 0;
            padding: 20px 0 0 20px;
        }

        #times {
            float: right;
            font-size: 16px;
            margin: 10px 60px 0 0;
        }

        body {
            background-color: #F2F2F2;
        }

        #mode {
            height: 75px;
            line-height: 75px;
            text-align: center;
            background-color: #2B2B2B;
            color: white;
            font-size: 20px;
            font-weight: bold;
        }

        #manual {
            height: 75px;
            line-height: 75px;
            text-align: center;
            background-color: #2B2B2B;
            color: white;
            font-size: 30px;
            font-weight: bold;
        }

        #manual:hover {
            color: #CB602D !important;
            cursor: pointer;
        }

        #intelligent {
            height: 75px;
            line-height: 75px;
            text-align: center;
            background-color: #F2F2F2;
            color: black;
            font-size: 30px;
            font-weight: bold;
        }

        #intelligent:hover {
            color: #CB602D !important;
            cursor: pointer;
        }

        #decoration {
            height: 60px;
        }

        #manual_dis {
            text-align: center;
            margin: 20px 0;
            font-size: 20px;
            font-weight: bold;
        }

        #intelligent_dis {
            text-align: center;
            margin: 20px 0;
            font-size: 20px;
            font-weight: bold;
        }

        p {
            margin: 20px 0 30px;
        }


        #robot_info {
            width: 100%;
            padding: 10px 0 10px 30px;
            background-color: #2B2B2B;
            position: absolute;
            bottom: 60px;
        }

        footer {
            width: 100%;
            height: 60px;
            background-color: #4C2B1C;
            position: absolute;
            bottom: 0;
            text-align: center;
        }

        footer h5 {
            margin-top: 20px;
            color: #9d9d9d;
        }
    </style>

</head>

<body>

<header>
    <h2>
        <span id="name">已登录用户 ：<?php echo $username ?></span>
        <button id="logout">退出</button>
        <span id="times"> </span>
    </h2>
</header>


<div id="container">
    <div id="mode" class="col-xs-12 col-sm-2">Mode</div>
    <div id="intelligent" class="col-xs-6 col-sm-5">智能模式</div>
    <div id="manual" class="col-xs-6 col-sm-5">手动模式</div>


    <div id="decoration" class="col-xs-1 col-sm-12"></div>
    <div id="manual_dis" class="col-xs-10  col-sm-6 col-sm-push-3" style="display: none">
        <p>手动模式下<br>可以遥控机器人移动<br>进行 前进/后退/左转/右转</p>
        <a href="manual.php">点击进入手动模式</a>
    </div>
    <div id="intelligent_dis" class="col-xs-10  col-sm-6 col-sm-push-3">
        <p>智能模式下<br>需要 新建 / 载入地图<br>通过功能按钮智能操控机器人</p>
        <a href="load.php">点击进入智能模式</a>
    </div>

</div>

<div id="operation">

</div>

<div id="robot_info">
    <h4>当前机器人状态：未连接</h4>
</div>
<footer>
    <h5>咖啡Robot - BUAA Team 206</h5>
</footer>
</body>

<script src="js/jquery-1.10.2.js"></script>
<script>
    var time = $('#times');
    time.html('Date: ' + new Date().toLocaleString('chinese', {hour12: false}));

    function getDate() {
        time.html('Date: ' + new Date().toLocaleString('chinese', {hour12: false}));
    }

    setInterval('getDate()', 1000)
</script>

<script>
    $('#manual').click(function () {
        $('#manual_dis').show();
        $('#intelligent_dis').hide();
        $('#intelligent').css({'backgroundColor': '#2B2B2B', 'color': 'white'});
        $('#manual').css({'backgroundColor': '#F2F2F2', 'color': 'black'});
    });

    $('#intelligent').click(function () {
        $('#intelligent_dis').show();
        $('#manual_dis').hide();
        $('#manual').css({'backgroundColor': '#2B2B2B', 'color': 'white'});
        $('#intelligent').css({'backgroundColor': '#F2F2F2', 'color': 'black'});
    });
</script>

<script>
    $('#logout').click(function () {
        window.location.href = 'logout.php';
    });

</script>

</html>

