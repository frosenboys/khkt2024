<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Quản lí lò sấy</title>
    <link rel="icon" href="/logo.png">
    <!-- JQuery 3.6.0 JS -->
    <script src="https://code.jquery.com/jquery-3.6.0.js" integrity="sha256-H+K7U5CnXl1h5ywQfKtSj8PCmoN9aaq30gDh27Xc0jk=" crossorigin="anonymous"></script>
    <!-- SweetAlert -->
    <script src="https://cdn.jsdelivr.net/npm/sweetalert2@11"></script>
    <!-- FontAwesome -->
    <script src="https://kit.fontawesome.com/f64ae307e0.js" crossorigin="anonymous"></script>
    <!-- Boostrap -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhGWiC2Al4u+LWgxfKTRIcfu0JTxR+EQDz/bgldoEyl4H0zUF0QKbrJ0EcQF" crossorigin="anonymous"></script>
    <!-- Font -->
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=JetBrains+Mono:wght@100&family=Noto+Sans&display=swap" rel="stylesheet">
</head>
<body id="reload" class="w-100">
    
</body>

<style>
    /* width */
    ::-webkit-scrollbar {
    width: 10px;
    }

    /* Track */
    ::-webkit-scrollbar-track {
    background: #f1f1f1;
    }

    /* Handle */
    ::-webkit-scrollbar-thumb {
    background: #888;
    }

    /* Handle on hover */
    ::-webkit-scrollbar-thumb:hover {
    background: #555;
    }

    *{
        font-family: Noto Sans;
    }
    
</style>
<script>
    $("#reload").load("/body.php");
    document.onkeydown = function(e) {
        if(e.ctrlKey && e.shiftKey && e.keyCode == 'I'.charCodeAt(0)) return false;
        if(e.ctrlKey && e.shiftKey && e.keyCode == 'J'.charCodeAt(0)) return false;
        if(e.ctrlKey && e.keyCode == 'U'.charCodeAt(0)) return false;
    }

    function change(mode){
        var formData = {
            change: true,
            mode: mode,
        };
        $.ajax({
            type: "POST",
            url: "changemode.php",
            data: formData,
            dataType: "json",
            encode: true,
        }).done(function (data) {
            if (data.error !== undefined){
            Swal.fire({
                icon: "error",
                title: "Oops...",
                text: data.error,
            });
            }
            else{
            Swal.fire({
                icon: "success",
                title: "Successfully",
                text: data.success,
            });
            setTimeout(function() {
                window.location.href = "/";
            }, 2000);
            }
        }).fail(function (data) {
            console.log(data);
        });
    }
    $(function() {
        // Reload div mỗi 5s
        setInterval(function() {
            $("#reload").load("/body.php");
        }, 5000);
    });
</script>

</html>