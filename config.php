<?php
    $server = "localhost";
    $username = "root";
    $password = "";
    $db = "esp32";

    $conn = mysqli_connect($server, $username, $password, $db);
        mysqli_set_charset($conn,'utf8mb4');
    if(!$conn)
    {
        echo "Error";
    }
    date_default_timezone_set('Asia/Ho_Chi_Minh');
?>