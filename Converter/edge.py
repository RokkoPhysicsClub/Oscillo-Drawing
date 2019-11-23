## coding: UTF-8
import cv2
from PIL import Image, ImageFilter
# 定数定義
maisuu=0
filedir="images"
print("#####################################")
try:
  for i in range(100000):

    im = Image.open(filedir+'/{0:05d}.png'.format(i+1))
    maisuu+=1
    print("Count	{}" .format(maisuu))


except:
  print("")
  

print("")

#ORG_FILE_NAME = "images/00101.png"
#CANNY_FILE_NAME = "canny.png"
for i in range(maisuu):
    # 元の画像を読み込む
    #org_img = cv2.imread('images/{0:05d}.png'.format(i+1), cv2.IMREAD_UNCHANGED)
    # グレースケールに変換
    gray_img = cv2.imread('images/{0:05d}.png'.format(i+1), cv2.IMREAD_GRAYSCALE)
    # エッジ抽出
    canny_img = cv2.Canny(gray_img, 50, 110)


    # ファイルに保存

    cv2.imwrite('images_done/{0:05d}.png'.format(i+1), canny_img)

    # 終了処理
    print (i)
cv2.waitKey(1000)
cv2.destroyAllWindows()