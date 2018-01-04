<?php
require 'config.php';
@$s=$_GET['secret'];
if($s!=$secret_keywords) // Prevent abuse
  die('Not available');

file_put_contents('pending_run','1');
echo 'Update requested';