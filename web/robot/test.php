<!DOCTYPE html>
<html>
<head>
    <title></title>
    <style>
        #mydiv{
            border:1px solid grey;
            width: 400px;
            height: 200px;
        }
    </style>
</head>
<body>
<div id="mydiv">
</div>
<script src="js/jquery-1.10.2.js"></script>
<script>
    $("#mydiv").mousedown(function(event){
        console.log(event.offsetX, event.offsetY);
    })


</script>
</body>
</html>
