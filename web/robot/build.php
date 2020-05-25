<?php
session_start();
if (!isset($_SESSION['logged'])) {
    echo '<script>alert("请登录后访问页面！")</script>';
    header('Location: index.html');
    exit();
}
?>
<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>新建地图</title>
    <link rel="stylesheet" href="css/bootstrap.css">
    <link rel="stylesheet" href="css/animate.css">
    <style>

        body {
            background-color: #F2F2F2;
        }

        header {
            width: 100%;
            height: 90px;
            background-color: #4C2B1C;
            margin-bottom: 30px;
        }

        header h2 {
            text-align: center;
            color: white;
            margin: 0;
            padding: 20px 0 0 20px;
        }

        #decoration {
            height: 50px;
        }

        #tip {
            text-align: center;
            font-weight: bold;
            font-size: 20px;
        }

        #stage {
            width: 240px;
            margin: 30px auto 0;
            text-align: center;
            font-size: 24px;
            font-weight: bold;
            color: #CB602D;
        }

        #start {
            width: 240px;
        }

        #start:hover {
            cursor: pointer;
        }

        .area {
            height: 100px;
            display: none;
        }

        .area span {
            width: 150px;
            height: 80px;
            margin: 0 auto;
            line-height: 80px;
            font-size: 23px;
            font-weight: bold;
            border-radius: 10px;
            display: block;
            background-color: #A6CE39;
            color: white;
        }

        .area span:hover {
            color: orange;
            cursor: pointer;

        }

        .area span:active {
            transform: scale(1.2);
        }

        .arrow_1 {
            margin-right: 20px;
            height: 60px;
            width: 60px;
        }

        .arrow_2 {
            margin: 10px;
            height: 50px;
            width: 50px;
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

        #save {
            width: 100px;
            height: 60px;
            line-height: 50px;
            position: absolute;
            bottom: 70px;
            right: 20px;
            background-color: #5cb85c;
            color: #F2F2F2;
            font-weight: bold;
            font-size: 20px;
            border: none;
            border-radius: 10px;
        }

        button:hover {
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

</head>
<body>
<header>
    <h2>新建地图</h2>
</header>
<div id="container">

    <div id="decoration" class="col-xs-1 col-sm-12"></div>

    <div id="tip">
        请操控机器人在场景中充分移动！
    </div>

    <div id="stage">
        <img src="img/start_button.png" alt="" id="start">
        <span id="notice">Start !</span>
    </div>

    <div id="forward" class="col-xs-10 col-sm-12 area">
        <span id="forward" class="op"><img src="img/forward.png" alt="" class="arrow_1">前进</span>
    </div>

    <div id="turn_left" class="col-xs-6 col-sm-4 col-sm-push-2 area">
        <span id="turn_left" class="op"><img src="img/left.png" alt="" class="arrow_2">左转</span>
    </div>

    <div id="turn_right" class="col-xs-6 col-sm-4 col-sm-push-2 area">
        <span id="turn_right" class="op"><img src="img/right.png" alt="" class="arrow_2">右转</span>
    </div>

    <div id="back" class="col-xs-10 col-xs-push-1 col-sm-12 col-sm-push-0 area">
        <span id="back" class="op"><img src="img/back.png" alt="" class="arrow_1">后退</span>
    </div>


    <button id="return" class="bounceIn">
        返回
    </button>

    <button id="save" class="bounceIn">
        保存
    </button>
</div>

<footer>
    <h5>咖啡Robot - BUAA Team 206</h5>
</footer>
</body>

<script src="js/jquery-1.10.2.js"></script>

<script>
    $('#return').click(function () {
        history.back();
    });

    $('#save').click(function () {
        var name = prompt("请给新建地图命名！");
        if(name===null){
            return;
        }
        if (name === '') {
            alert("不能为空！");
        } else {
            var form = $("<form method='post' action='add_map.php'></form>");
            var input = "<input type='hidden' name='name' value='" + name + "'>";
            form.append(input);
            form.appendTo(document.body);
            form.submit();
        }
    })

</script>

<script>
    $('#start').click(function () {
        console.log('start');
        $('#stage').remove();
        clearInterval(InterVal);
        $('.area').addClass('bounceIn').show();
        $('#tip').hide();
    });

    $('.op').click(function () {
        console.log(this.id)
    })
</script>

<script>
    var rotateVal = 0;// 旋转角度
    var InterVal;// 定时器
    window.onload = function () {
        // 网页加载完成后即运行rotate函数
        rotate(1);
        // 鼠标悬浮在图片上时，停止旋转，即清除定时器
        document.getElementById('start').onmousemove = function () {
            clearInterval(InterVal);
            rotate(60)
        };
        // 鼠标离开图片时，继续旋转，即继续运行定时器
        document.getElementById('start').onmouseleave = function () {
            rotate(1)
        }
    };

    // 设置定时器
    function rotate(vel) {
        InterVal = setInterval(function () {
            var img = document.getElementById('start');
            if (img) {
                rotateVal += vel;
                // 设置旋转属性(顺时针)
                img.style.transform = 'rotate(' + rotateVal + 'deg)';
                // 设置旋转属性(逆时针)
                //img.style.transform = 'rotate(-' + rotateVal + 'deg)'
                // 设置旋转时的动画  匀速0.1s
                img.style.transition = '0.1s linear';
            } else {
                clearInterval(InterVal);
            }
        }, 100)
    }
</script>

<script>
    $(function () {
        function add_animate() {
            if (notice.css('display') === 'none')
                notice.show();
            else
                notice.hide(50, 'linear');
            setTimeout(add_animate, 600);
        }

        var notice = $('#notice');
        notice.addClass('bounceIn bounceOut');
        setTimeout(add_animate, 600);
    })

</script>

</html>
