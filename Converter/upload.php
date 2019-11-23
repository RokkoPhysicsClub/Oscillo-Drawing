<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>ゆっくりしていってね</title>
</head>
<body>
<p><?php
ini_set( 'display_errors', 1 );
$filename=$_FILES["upfile"]["name"];
echo $_FILES['upfile']['error'];
if (is_uploaded_file($_FILES["upfile"]["tmp_name"])){
  if (move_uploaded_file($_FILES["upfile"]["tmp_name"], "movies/" . $_FILES["upfile"]["name"])) {
    //echo $_FILES["upfile"]["name"] . "をアップロードしました。";
  } else {
    echo "ファイルをアップロードできません。";
  }
} else {
  echo "ファイルが選択されていません。";
}
header('location: index.php?filename='.$filename);
exit();//←忘れずに！
?></p>
</body>
</html>
