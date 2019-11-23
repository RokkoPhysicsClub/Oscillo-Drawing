## coding: UTF-8
import cv2
import numpy as np
#from matplotlib import pyplot as plt
from PIL import Image, ImageFilter
import sys

args = sys.argv

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
    #org_img = cv2.imread('images/{0:05d}.png'.format(i+1), cv2.IMREAD_UNCHANGED)
    # 元の画像を読み込む
    img = cv2.imread('images/{0:05d}.png'.format(i+1))
    # グレースケール変換
    gray = cv2.cvtColor(img, cv2.COLOR_RGB2GRAY)   
    dst2 = cv2.adaptiveThreshold(gray,255,cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY,11,float(args[1]))

    
    # 結果を出力
    cv2.imwrite('images_done/{0:05d}.png'.format(i+1), dst2)

    # 終了処理
    print (i)
cv2.waitKey(1000)
cv2.destroyAllWindows()
