<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>ゆっくりしていってね</title>
</head>
<body>
<?php
ini_set( 'display_errors', 1 );
echo($_GET["filename"]);
$filename=$_GET["filename"]
?><br>上にファイル名が表示されてない場合はアップロード失敗<br>
<form action="ffmpeg.php" method="get" enctype="multipart/form-data">
  fps：<br />
  <input type="text" name="fps" size="30"value=20 /><br />
  <br />
	<select name='option'>
		<option value='tubutubu'>つぶつぶ</option>
		<option value='autogray'>アニメ調</option>
		<option value='hand'>手動しきい値+つぶつぶ処理</option>
	</select><br>
	手動しきい値を選んだ場合のしきい値
	<input type="text" name="sikiiti" size="30"value=120 /><br />
  <input type="hidden" name="filename" value=<?php echo($filename) ?>>
  <input type="submit" value="変換" />
</form>
</body>
</html>
