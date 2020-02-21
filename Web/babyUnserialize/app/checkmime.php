<?php
class tooYoung{
    protected $naive;
    public function tooSimple(){
        return $this->naive;
    }
}
class Main {
    public $file="/flag";
    public function __wakeup(){ $this-> file='/var/www/html/index.html'; }
    public function __destruct(){
        if(unserialize($_GET['reporter'])->tooSimple() === 'reporter'){
            if(!empty($this->file)) {
                show_source($this->file);
            }else{
                die('No such file');
            }
        }
    }
}

if(isset($_POST["submit"])) {
    $check = getimagesize($_POST['name']);
    if($check !== false) {
        echo "File is an image - " . $check["mime"] . "\n";
    } else {
        echo "File is not an image.";
    }
}
?>
