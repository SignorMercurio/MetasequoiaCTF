# UTF-8
题目给了一个`rfc3629`的链接，也就是UTF-8编码的RFC文件。

首先访问发现是空页面，扫一下可以发现`robots.txt`，指向一个奇怪的文件：
```
length q chdir lc and print chr ord q each le and print chr ord q lc eval and print chr ord q lt eval and print chr ord q sin s and print chr ord q xor x and print chr ord qw q not q and print chr oct oct ord q eq ge and print chr ord q msgctl m and print chr ord q local and print chr ord q dump and and print chr ord q or no and print chr ord q oct no and print chr ord q ge log
```

提示说`chmod +x secretscript`，说明这个文件是可以运行的，因此猜想这是脚本文件，查阅资料可知这是`ppencoding`，放入在线Perl运行工具运行一下，得到：
```
action=source
```

把这个当作GET参数，访问得到源码：
```php
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
```

过滤了很多字符，但是并不是没有报错注入的可能，利用`solve.py`可以注入出管理员密码。

但是直接用`admin`和密码登录是不行的，因为有如下判断：
```php
if ($username == 'admin') {
    die("No, I know you are not admin.");
}
```

这里的绕过技巧来自[这篇文章](https://www.leavesongs.com/PENETRATION/mysql-charset-trick.html)，细节还是比较多的，也是这题名称的由来。