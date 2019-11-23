from PIL import Image, ImageFilter
import sys,time
###file select

maisuu=0;
filedir="images_done";
start = time.time()
print("#####################################")
try:
  for i in range(100000):

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
f = open("zahyou.txt", "w")
f.write("{}\n".format(maisuu))
#f.write("Python!\n")
start = time.time()
for i in range(maisuu):
  im = Image.open(filedir+'/{0:05d}.png'.format(i+1))
  imgdata = im.getdata()
  #width, height =im.size
  kokuten=0
  LK= ""#kisuu
  LG= ""#guusuu
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
      if(kosa!=kosa_old or x==width):
        if(flug!=0 ):
          kosa_old=kosa
          if(kosa_old>0 ):
            kokuten+=1
            if(y%2==0):
              LK=LK+("{} {} {} {}\n".format(oldx,x-1,y,kosa_old))#kiauuretu
            else:
              LG=LG+("{} {} {} {}\n".format(oldx,x-1,y,kosa_old))#guusuuretu
          flug=0
        else:
          flug+=1
          if(flug==1):
            oldx=x
            kosa_old=kosa
  #LG=LG[:-1]
  f.write("{}\n{}{}".format(kokuten,LK,LG))#yousosuu,kisuu,guusuu
  #xstart ,xend , y
  #new_im=im.convert('1')
  print("processing... : {} / {}" .format(i+1,maisuu))
  
end = time.time()
print("")
print("time  {:4.1f}ms".format((end - start) * 1000) )
f.close()
print("done!")

