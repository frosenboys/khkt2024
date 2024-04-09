<?php
    include "config.php";
    if (isset($_POST['change'])){
        $data = [];
        $mode = $_POST['mode'];
        $sql = "UPDATE status SET mode = '$mode' WHERE id = 1";
        $result = mysqli_query($conn, $sql);
        if($result == 1)
        {
            $data["sucess"] = "Cập nhật chế độ thành công !";
        }
        else $data["error"] = "Đã có lỗi xảy ra !";
        echo json_encode($data);
    }
    else header("location: /");
?>