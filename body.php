    <?php 
        require 'config.php'; 
        $sql = "SELECT * FROM status WHERE id = 1";
        $result = mysqli_query($conn, $sql);
        $rows = mysqli_fetch_array($result);

        function humiCheck($humi){
            if ($humi < 10) echo 'Ổn định';
            else if ($humi <= 50) echo 'Hơi ẩm';
            else if ($humi > 50) echo 'Độ ẩm cao';
        }
    ?>
    <center>
        <div class="card w-50 shadow container mt-2">
            <div class="card-title mt-2">
                <h4 class="mt-2 fw-bold">Trạng thái</h4>
            </div>
            <hr style="margin:0;">
            <div class="card-body d-flex justify-content-around">
                <div class="card shadow-lg p-4 text-success fw-bold m-2 ele" id="temp">
                    <i class="fa-solid fa-temperature-full" style="font-size: 50px"></i><br>
                    <p>Nhiệt độ</p>
                    <p id="temp-value" style="font-size: 40px"><?=$rows['temp'];?>°C</p>
                    <p>Ổn định</p>
                </div>
                <div class="card shadow-lg p-4 text-danger fw-bold m-2 ele" id="temp">
                    <i class="fa-solid fa-droplet" style="font-size: 50px"></i><br>
                    <p>Độ ẩm</p>
                    <p id="temp-value" style="font-size: 40px"><?=$rows['humi'];?>%</p>
                    <p><?=humiCheck($rows['humi']);?></p>
                </div>
            </div>
        </div>

        <div class="card w-50 shadow container mt-4 mb-5">
            <div class="card-title mt-2">
                <h4 class="mt-2 fw-bold">Chế độ</h4>
            </div>
            <hr style="margin:0;">
            <div class="card-body">
                <p>Chế độ hiện tại: 
                    <span class="fw-bold text-primary">
                        <?php
                            if($rows['mode'] == 1){
                                echo 'Sấy khô';
                            }
                            else if($rows['mode'] == 2){
                                echo 'Sấy dẻo';
                            }
                            else if($rows['mode'] == 3){
                                echo 'Sấy giòn';
                            }
                        ?>
                    </span>
                </p>
                <p>Thay đổi chế độ:</p>
                <div class="list">
                    <a class="btn btn-primary m-2 shadow" onclick="change('1');">Sấy khô (60-80°C)</a>
                    <a class="btn btn-primary m-2 shadow" onclick="change('2');">Sấy dẻo (40-70°C)</a>
                    <a class="btn btn-primary m-2 shadow" onclick="change('3');">Sấy giòn (70-90°C)</a>
                </div>
            </div>
        </div>
    </center>


<style>
    @media only screen and (max-width: 900px){
        .card-body{
            flex-wrap: wrap;
        }
        .ele{
            width: 100%;
        }
    }
    .ele{
        width: 50%;
        min-width: 150px;
    }
    .container{
        min-width: 250px;
    }
    body{
        /* background-color: #8dfcab; */
        background: linear-gradient(to right, #bff5c3, #ace3fa);
    }
</style>

<footer class="w-100 text-center p-3 shadow" style="padding: 10px;text-align: center;width: 100%;">
	<div class="text-dark" style="font-weight: bold;">Copyright @ 2024 by <a style="color: #f28a5a;" href="https://www.facebook.com/xuan.datbing/">Xuân Đạt Bing</a></div>
</footer>