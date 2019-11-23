<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>画像切り出し中</title>
</head>
<body>
<p><?php
ini_set( 'display_errors', 1 );
$fps=$_GET["fps"];
$filename=$_GET["filename"];
$option=$_GET["option"];
$sikiiti=$_GET["sikiiti"];
$name = explode(".", $filename);
echo($filename);
shell_exec("rm images/*");
echo(shell_exec("ffmpeg -i movies/".$filename." -s 256x256 -r ".$fps." images/%05d.png"));

//echo("ffmpeg -i movies/".$filename." -s 256x256 -r ".$fps." images/%05d.png");
header('location: totext.php?filename='.$filename.'&fps='.$fps.'&option='.$option.'&sikiiti='.$sikiiti);
exit();
?></p>
</body>
</html>
