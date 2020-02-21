<?php

$conn->query("set names utf8");

$sql = "create table `user` (
         `id` int(10) unsigned NOT NULL PRIMARY KEY  AUTO_INCREMENT ,
         `username` varchar(30) NOT NULL,
         `passwd` varchar(32) NOT NULL,
         `role` varchar(30) NOT NULL
       )ENGINE=MyISAM AUTO_INCREMENT=1 DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci ";
if ($conn->query($sql)) {
  $sql  = "insert into `user`(`username`,`passwd`,`role`) values ('admin','".md5(randStr())."','admin')";
  $conn->query($sql);
}

function filter($str) {
     $filter = "/ |\*|,|;|union|is|like|regexp|and|or|for|file|#|--|\||&|`|".urldecode('%a0')."|".urldecode("%0a")."|".urldecode("%0b")."|".urldecode('%0c')."|".urldecode('%0d')."|".urldecode('%09')."/i";
     if(preg_match($filter,$str)) {
         die("?");
     }
     return $str;
}

function login($username,$passwd) {
    global $conn;

    $username = trim(strtolower($username));
    $passwd = trim(strtolower($passwd));
    if ($username == 'admin') {
        die("No, I know you are not admin.");
    }

    $sql = "select * from `user` where username='".$conn->escape_string($username)."' and passwd='".$conn->escape_string($passwd)."'";
    $res = $conn->query($sql);
    if ($res->num_rows > 0) {
        if($res->fetch_assoc()['role'] === 'admin') {
            exit($flag);
        }
    } else {
       echo "Username / Passwd Error!";
    }
}

$username = isset($_POST['username'])?filter($_POST['username']):"";
$passwd = isset($_POST['passwd'])?filter($_POST['passwd']):"";
$action = isset($_GET['action'])?filter($_GET['action']):"";

switch($action) {
   case "source": source(); break;
   case "login" : login($username,$passwd);break;
   case "show" : show($username);break;
}

echo 'R U sure U R familiar with UTF-8?';
