<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>動画完了</title>
</head>
<body>

<p><?php

ini_set( 'display_errors', 1 );
$filename=$_GET["filename"];
$fps=$_GET["fps"];
$name = explode(".", $filename);
$file = "zahyou.txt";
echo $name[0];
shell_exec("rm -f gif/".$name[0].".mp4");
shell_exec("rm -f gif/".$name[0].".wav");
shell_exec("ffmpeg -i movies/".$filename." gif/".$name[0].".wav");
echo shell_exec("ffmpeg -f image2 -r ".$fps." -i images_done/%05d.png -i gif/".$name[0].".wav -r 30 -vcodec libx264 -pix_fmt yuv420p gif/".$name[0].".mp4");




//echo("<img src= gif/".$name[0].".gif>");
?></p>
<a href="osd/<?php echo($name[0]);?>.osd" download >osdダウンロード</a><?php echo($name[0].".osd");?><br>
</p><video controls>
  <source src="gif/<?php echo($name[0].".mp4");?>">
</video>

</body>
</html>
