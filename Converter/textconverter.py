# coding:utf-8
from PIL import Image, ImageFilter
import sys,time
#new_im=im.convert('1')
#new_im.save('bad2/00018.png')
maisuu=0;
start = time.time()
try:
  for i in range(16590):
    
    im = Image.open('images_done/{0:05d}.png'.format(i+1))
    maisuu+=1
    #new_im=im.convert('1')
      
except:
  print("")
  #print(maisuu)
  
end = time.time()
print("count  {:4.1f}ms".format((end - start) * 1000) )
f = open("zahyou.txt", "w")
f.write("{}\n".format(maisuu))
#f.write("Python!\n")
start = time.time()
for i in range(maisuu-1):
  im = Image.open('images_done/{0:05d}.png'.format(i+1))
  imgdata = im.getdata()
  width, height =im.size
  kokuten=0  
  LK= ""#kisuu
  LG= ""#guusuu
  for y in range(height):
    ycache = y * width
    flug=0
    for x in range(width):
      
      pixdata = imgdata[ycache + x]#int 0-255
      if(pixdata==255):
        kokuten+=1
        flug+=1
        if(flug==1):
          oldx=x
      else:
        if(flug!=0):
          if(y%2==0):
            LK=LK+("{} {} {}\n".format(oldx,x-1,y))
          else:
            LG=LG+("{} {} {}\n".format(oldx,x-1,y))
          flug=0
  #LG=LG[:-1]
  f.write("{}\n{}{}\n".format(kokuten,LK,LG))
  #new_im=im.convert('1')
  #sys.stdout.write("\r processing... : {} / {}" .format(i+1,maisuu))
  #sys.stdout.flush()
end = time.time()
print("")
print("time  {:4.1f}ms".format((end - start) * 1000) )
f.close()
print("done!")
