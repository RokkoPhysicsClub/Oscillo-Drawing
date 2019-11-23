<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>完了</title>
<div id="progress"></div>
<script type="text/javascript">

fetch("log.log").then(function(response) {
  return response.text();
}).then(function(text) {
  //text;
  var arr = text.split(/\r\n|\n/);
  document.getElementById('progress').innerHTML = arr[arr.length-2] ;
});
</script>
</head>
<body>
<p><?php

ini_set( 'display_errors', 1 );
$filename=$_GET["filename"];
$fps=$_GET["fps"];
$name = explode(".", $filename);
$file = "zahyou.txt";
echo $name[0];
shell_exec("rm -f gif/".$name[0].".gif");

shell_exec("rm -f gif/".$name[0]."_play.gif");
shell_exec("rm -f gif/".$name[0].".mp4");
//shell_exec("ffmpeg -f image2 -r ".$fps." -i images_done/%05d.png -r 30 -an -vcodec libx264 -pix_fmt yuv420p gif/".$name[0].".mp4");

shell_exec("cp images_done/00001.png gif/".$name[0]."_play.gif");
shell_exec("convert gif/".$name[0]."_play.gif button.png -composite gif/".$name[0]."_play.gif");

shell_exec("convert -delay 10 images_done/****1.png gif/".$name[0].".gif>end.log&");
//echo("sudo convert -layers optimize images_done/000*0.png ".$name[0].".gif");
//echo("convert images_done/* gif/".$name[0].".gif");
$file2="osd/".$name[0].".osd";
$size = floor((int)filesize($file2)/1048576);

echo "ファイルサイズ：" . $size."MB<br>プレビュー(1/10flame)<br>";

//echo("<img src= gif/".$name[0].".gif>");
?>
<a href="osd/<?php echo($name[0]); ?>.osd" download>ダウンロード</a><?php echo($name[0]);?>.osd<br>

</p>
</p><img src="gif/<?php echo($name[0]);?>_play.gif" onclick="this.setAttribute('src', this.getAttribute('src').replace(/_play.gif$/g, '.gif'));" style="cursor: pointer;"><br>
<a href= "movie.php?filename=<?php echo$filename."&fps=".$fps?> ">音付きmp4を作成する</a>
</body>
</html>
