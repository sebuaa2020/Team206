<?php
session_start();
if (!isset($_SESSION['logged'])) {
    echo '<script>alert("请登录！")</script>';
    header('Location: index.html');
    exit();
}
$uid = $_SESSION['uid'];
?>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>加载地图</title>
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/animate.css">
    <style>
        header {
            width: 100%;
            height: 90px;
            background-color: #4C2B1C;
        }

        header h2 {
            text-align: center;
            color: white;
            margin: 0;
            padding: 20px 0 0 20px;
        }

        body {
            background-color: #F2F2F2;
        }

        h3 {
            display: inline-block;
            margin: 30px 30px 20px 0;
            font-weight: bold;
        }

        button {
            width: 60px;
            padding: 0;
            font-size: 20px;
            background-color: #A6CE39;
            color: white;
            border-radius: 5px;
            border: none;
        }

        button:hover {
            transform: scale(1.12);
        }

        #delete {
            background-color: red;
            margin-left: 10px;
        }

        #build {
            margin: 0 20px;
        }

        #load {
            margin: 0 20px;
        }

        label {
            list-style: none;
            display: block;
            cursor: pointer;
            line-height: 30px;
            height: 30px;
            font-size: 18px;
            background-color: #fff;
            padding-left: 10px;
            border-radius: 3px;
        }

        span {
            margin-left: 10px;
        }

        #exit {
            width: 100px;
            height: 60px;
            line-height: 50px;
            position: fixed;
            bottom: 70px;
            right: 20px;
            background-color: red;
            color: #F2F2F2;
            font-weight: bold;
            font-size: 20px;
            border: none;
            border-radius: 10px;
        }

        footer {
            width: 100%;
            height: 60px;
            background-color: #4C2B1C;
            position: fixed;
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
    <h2>设置地图</h2>
</header>
<div id="container">

    <div id="build" class="col-sm-6 col-sm-push-3">
        <h3>新建地图</h3>
        <button id="new">新建</button>
        <p>手动操控机器人，重新建立一张地图</p>
    </div>
    <div id="load" class="col-sm-6 col-sm-push-3">
        <h3>载入地图</h3>
        <button id="select">载入</button>
        <button id="delete">删除</button>
        <p>从已有的地图列表中选择一张地图</p>
        <div id="display">
            <form action="intelligent.php" id="chose" method="post">
                <?php
                include "connectDB.php";
                $result = mysqli_query($conn, "SELECT * FROM map WHERE uid = '$uid'");
                $cnt = 1;
                if ($result->num_rows > 0) {
                    while ($row = $result->fetch_assoc()) {
                        echo '<label for="c' . $cnt . '"><input type="radio" name="name" id="c' . $cnt . '" value="' . $row["name"] . '"><span>' . $row["name"] . '</span></label>';
                        $cnt++;
                    }
                }
                ?>
            </form>
        </div>
    </div>
</div>


<button id="exit" class="bounceIn">
    退出
</button>
<footer>
    <h5>咖啡Robot - BUAA Team 206</h5>
</footer>
</body>

<script src="js/jquery-1.10.2.js"></script>

<script>
    $('#exit').click(function () {
        window.location.href = 'welcome.php';
    });
    $('input:first').prop('checked', true);
    $("label:first").css("background", "#99CCFF").addClass('flag');


    $("label").click(
        function () {
            $(this).css("background", "#99CCFF").addClass('flag');
            $(this).siblings('label').css("background", "#ffffff").removeClass('flag');
        });

    $('#new').click(function () {
        window.location.href = 'build.php';
    });

    $('#select').click(function () {
        $('#chose').submit();
    });

    $('#delete').click(function () {
        var chosen = $('.flag');
        var name = chosen.children('input').val();
        if (confirm("确定要删除地图 " + name + " 吗？")) {
            $.post("delete_map.php", {name: name}, function () {
                chosen.remove();
            });
        }
    });

</script>

</html>
