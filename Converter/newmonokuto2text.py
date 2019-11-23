from PIL import Image, ImageFilter
import sys,time
###file select

maisuu=0;
filedir="images_done";
start = time.time()
print("#####################################")
try:
  for i in range(3):

    im = Image.open(filedir+'/{0:05d}.png'.format(i+1))
    maisuu+=1
    print("Count	{}" .format(maisuu))


except:
  print("")
  

end = time.time()
print("")
print("Count Time	{:4.1f}ms".format((end - start) * 1000) )
im = Image.open(filedir+'/{0:05d}.png'.format(1))
width, height =im.size
print("Size	{}x{}".format(width,height))
print("#####################################")
f = open("zahyou.bin", "wb")
maisuu_b=maisuu
f.write(maisuu_b.to_bytes(2,byteorder='big'))
#f.write("Python!\n")
start = time.time()
for i in range(maisuu):
  im = Image.open(filedir+'/{0:05d}.png'.format(i+1))
  imgdata = im.getdata()
  #width, height =im.size
  kokuten=0
  LK=b'00'
  LG=b'00'
  for y in range(height):
    kosa_old=0
    kosa=0
    ycache = y * width
    oldx=0
    x=0
    flug=0
    for x in range(width):
      
      pixdata = imgdata[ycache + x - 1]#int 0-255
      kosa = pixdata[0]
      if(kosa!=kosa_old):
        if(flug!=0):
          kokuten+=1
          kosa_old=kosa
          if(kosa_old>0):
            if(y%2==0):
              #LK=LK+("{}{}{}{}".format(oldx,x-1,y,kosa_old))#kiauuretu
              LK=LK+oldx.to_bytes(2,byteorder='big')
            else:
              #LG=LG+("{}{}{}{}".format(oldx,x-1,y,kosa_old))#guusuuretu
              LG=LG+oldx.to_bytes(2,byteorder='big')
            flug=0
        else:
          flug+=1
          if(flug==1):
            oldx=x
            kosa_old=kosa
  #LG=LG[:-1]
  #f.write("{}{}{}".format(kokuten,LK,LG))#yousosuu,kisuu,guusuu
  f.write(kokuten.to_bytes(2,byteorder='big'))
  f.write(LK)
  f.write(LG)
  #xstart ,xend , y
  #new_im=im.convert('1')
  print("processing... : {} / {}" .format(i+1,maisuu))
  
end = time.time()
print("")
print("time  {:4.1f}ms".format((end - start) * 1000) )
f.close()
print("done!")

