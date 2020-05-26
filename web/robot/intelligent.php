<?php
session_start();
if (!isset($_SESSION['logged'])) {
    echo '<script>alert("请登录后访问页面！")</script>';
    header('Location: index.html');
    exit();
}

$map = isset($_POST['name']) ? $_POST['name'] : $_SESSION['map'];
?>

<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>智能模式</title>
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

        #info {
            width: 100%;
            padding: 10px 0 10px 30px;
            background-color: #2B2B2B;
        }

        h4 {
            color: #CB602D;
            margin: 0;
        }

        #decoration {
            height: 40px;
        }

        #deliver {
            margin: 20px 20px;
            background-color: #fff;
            border-radius: 5px;
            border: 1px solid #4C2B1C;
            cursor: pointer;
            transition: 0.1s linear;
        }

        #deliver:hover {
            color: orange;
            transform: scale(1.1);
            border: 2px solid orange;
        }

        #recover {
            margin: 15px 20px;
            background-color: #fff;
            border-radius: 5px;
            border: 1px solid #4C2B1C;
            cursor: pointer;
            transition: 0.1s linear;
        }

        #recover:hover {
            color: orange;
            transform: scale(1.1);
            border: 2px solid orange;
        }

        #respond {
            margin: 10px 20px 0;
            height: 40px;
            line-height: 40px;
            background-color: #fff;
            font-weight: bold;
            border-radius: 5px;
            color: #4C2B1C;
        }

        h3 {
            display: inline-block;
            margin: 20px 30px 10px 0;
            font-weight: bold;
        }

        p {
            padding-bottom: 10px;
        }

        .free {
            color: #5cb85c;
        }

        .occupied {
            color: orange;
        }

        #return {
            width: 100px;
            height: 60px;
            line-height: 50px;
            position: absolute;
            bottom: 70px;
            left: 20px;
            background-color: darkorange;
            color: #F2F2F2;
            font-weight: bold;
            font-size: 20px;
            border: none;
            border-radius: 10px;
        }

        #return:hover {
            transform: scale(1.12);
        }

        #stop {
            width: 100px;
            height: 60px;
            line-height: 50px;
            position: absolute;
            bottom: 70px;
            right: 20px;
            background-color: red;
            color: #F2F2F2;
            font-weight: bold;
            font-size: 20px;
            border: none;
            border-radius: 10px;
        }

        #stop:active {
            transform: scale(1.12);
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

    <style>
        /* 触发弹窗图片的样式 */
        #myImg {
            border-radius: 5px;
            cursor: pointer;
            transition: 0.3s;
        }

        #myImg:hover {
            opacity: 0.7;
        }

        /* 弹窗背景 */
        .modal {
            display: none; /* Hidden by default */
            position: fixed; /* Stay in place */
            z-index: 1; /* Sit on top */
            padding-top: 20px; /* Location of the box */
            left: 0;
            top: 0;
            width: 100%; /* Full width */
            height: 100%; /* Full height */
            overflow: auto; /* Enable scroll if needed */
            background-color: rgb(0, 0, 0); /* Fallback color */
            background-color: rgba(0, 0, 0, 0.9); /* Black w/ opacity */
        }

        /* 图片 */
        .modal-content {
            margin: auto;
            display: block;
            width: 80%;
            max-width: 600px;
        }

        #myModal {
            text-align: center;
        }

        /* 文本内容 */
        #caption {
            font-weight: bold;
            font-size: 20px;
            color: #ccc;
            display: block;
            margin: 10px 0 30px;
        }

        #location {
            border: none;
        }

        /* 添加动画 */
        .modal-content, #caption {
            -webkit-animation-name: zoom;
            -webkit-animation-duration: 0.6s;
            animation-name: zoom;
            animation-duration: 0.6s;
        }

        @-webkit-keyframes zoom {
            from {
                -webkit-transform: scale(0)
            }
            to {
                -webkit-transform: scale(1)
            }
        }

        @keyframes zoom {
            from {
                transform: scale(0)
            }
            to {
                transform: scale(1)
            }
        }

        /* 关闭按钮 */
        .close {
            position: absolute;
            top: 15px;
            right: 35px;
            color: white;
            font-size: 40px;
            font-weight: bold;
            transition: 0.3s;
        }

        .close:hover,
        .close:focus {
            color: #bbb;
            text-decoration: none;
            cursor: pointer;
        }

        /* 小屏幕中图片宽度为 100% */
        @media only screen and (max-width: 700px) {
            .modal-content {
                width: 100%;
            }
        }

        .mouse {
            position: fixed;
            background: red;
            width: 20px;
            height: 20px;
            border-radius: 10px;
            display: none;
        }

    </style>

</head>
<body>
<header>
    <h2>智能模式</h2>
</header>
<div id="container">
    <div id="info">
        <h4>当前地图：<?php echo $map; ?></h4>
    </div>

    <div id="decoration" class="col-xs-1 col-sm-12"></div>

    <div id="deliver" class="col-sm-6 col-sm-push-3 ">
        <h3>送咖啡</h3>
        <!-- 触发弹窗 - 图片改为你的图片地址 -->
        <img id="myImg" src="map/test.pgm" alt="选择目标地点" width="40" height="40">

        <p>在地图上选择目标地点，机器人自动导航到达</p>
    </div>
    <div id="recover" class="col-sm-6 col-sm-push-3 ">
        <h3>回收咖啡杯</h3>
        <p>一键回收地图场景内所有咖啡杯</p>
    </div>

    <div id="respond" class="col-sm-6 col-sm-push-3">
        <p>机器人状态：<span id="state">空闲</span></p>
    </div>

    <!-- 弹窗 -->
    <div id="myModal" class="modal">
        <!-- 关闭按钮 -->
        <span class="close" onclick="document.getElementById('myModal').style.display='none'">&times;</span>
        <span id="caption"></span>
        <!-- 弹窗内容 -->
        <img class="modal-content" id="location">
        <!-- 文本描述 -->
        <div id="mouse" class="mouse"></div>
    </div>
</div>


<button id="return" class="bounceIn">
    返回
</button>

<button id="stop" class="bounceIn">
    STOP
</button>

<footer>
    <h5>咖啡Robot - BUAA Team 206</h5>
</footer>
</body>

<script src="js/jquery-1.10.2.js"></script>

<script>
    $('#return').click(function () {
        window.location.href = 'load.php';
    });
    $('#stop').click(function () {
        console.log('STOP');
    });

    $('#state').addClass('free');
    $('#recover').click(function () {
        if (confirm('确定回收所有咖啡杯吗？')) {
            console.log('回收咖啡杯');
            $('#state').text('正在执行任务').removeClass('free').addClass('occupied');
        }
    });

</script>


<script>
    // 获取弹窗
    var modal = document.getElementById('myModal');

    // 获取图片插入到弹窗 - 使用 "alt" 属性作为文本部分的内容
    var img = document.getElementById('myImg');
    var modalImg = document.getElementById("location");
    var captionText = document.getElementById("caption");

    $('#deliver').click(function () {
        modal.style.display = "block";
        modalImg.src = img.src;
        captionText.innerText = img.alt;
    });

    // 获取 <span> 元素，设置关闭按钮
    var span = document.getElementsByClassName("close")[0];

    // 当点击 (x), 关闭弹窗
    span.onclick = function () {
        modal.style.display = "none";
    };

    var loc = $('#location');
    var mouse = document.getElementById('mouse');
    var x,y;

    loc.click(function () {
        //需求：鼠标在页面上单击时，获取单击时的位置，并显示一个小圆点
        mouse.style.display = 'block';
        // 获取事件对象的兼容处理
        var targetX = event.clientX - mouse.offsetWidth / 2;
        var targetY = event.clientY - mouse.offsetHeight / 2;
        // 在鼠标单击的位置显示<div>
        mouse.style.left = targetX + 'px';
        mouse.style.top = targetY + 'px';
        x = event.offsetX;
        y = event.offsetY;
        setTimeout(conf,600);
    });

    function conf() {
        if (confirm("确认选择此地点")) {
            console.log(x, y);
            console.log(loc.outerHeight(), loc.outerWidth());
            modal.style.display = "none";
            $('#state').text('正在执行任务').removeClass('free').addClass('occupied');
            console.log('送咖啡');
        }
    }

</script>


</html>
