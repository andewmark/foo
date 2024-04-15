<?php

$username = $_POST['username'];
$email = $_POST['$email'];
$password = $_POST['password'];

if (!empty($username) && !empty($email) && !empty($password)) {
    $host = '';
    $dbUsername='';
    $dbPassword= '';
    $dbname='';

    $conn = new mysqli($host, $dbUsername, $dbPassword, $dbname); #connecting our db

    if(mysqli_connect_error()){
        echo "Failed";
        die('Connect Error('. mysqli_connect_errno() .')'. mysqli_connect_error());
    }else{
        echo "connected successfully";
  
        $SELECT = "SELECT email from registerdb Where email = ? Limit 1"; # because emails are unique
        $INSERT = "INSERT Into registerdb (username, email, password) values(?,?,?)";

        // prepare statement 
        $stmt = $conn->prepare($SELECT);
        $stmt->bind_param("s", $email);
        $stmt->execute();
        $stmt->bind_result($email);
        $stmt->store_result();
        $rnum = $stmt->num_rows;
        if($rnum > 0){
            $stmt->close();

            $stmt = $conn->prepare($INSERT);
            $stmt->bind_param("sss", $username, $email, $password);
            $stmt->execute();
            echo"new user registered successfully";
        }else{
            echo "something went wrong";

        }
        if (($_SERVER['REQUEST_METHOD'] == 'POST') && isset($_POST['action']) && (!empty($_POST['action']))){

        }
        header('Location: profile.html');
       

        $stmt->close();
        $conn->close();


    }


}

