<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>白黒化＆テキスト化</title>
</head>
<body>
<p><?php
ini_set( 'display_errors', 1 );
$fps=$_GET["fps"];
$filename=$_GET["filename"];
$name = explode(".", $filename);
$option=$_GET["option"];
$sikiiti=$_GET["sikiiti"];
if($sikiiti=="")$sikiiti="0";
echo($filename);
//shell_exec("nohup ffmpeg -r ".$fps." -i images_done/%05d.png -vcodec libx264 -pix_fmt yuv420p -r 30  ".$filename."_done.mp4");
shell_exec("rm images_done/*");
shell_exec("rm zahyou.txt");
if($option=="tubutubu"){
shell_exec("python videoconverter.py");
}
if($option=="autogray"){
shell_exec("python sirokai.py ".$sikiiti);
}
//shell_exec("python videoconverter.py");

shell_exec("chmod 777 log.log");
shell_exec("python textconverter2.py ".$name[0].">log.log");//textconverter ->2ninatta
chmod("zahyou.txt", 0777);  // 8 進数; 正しいモードの値
//echo("ffmpeg -i movies/".$filename." -s 256x256 -r ".$fps." images/%05d.png");
header('location: end.php?filename='.$filename.'&fps='.$fps.'&option='.$option.'&sikiiti='.$sikiiti);

?></p>
</body>
</html>
