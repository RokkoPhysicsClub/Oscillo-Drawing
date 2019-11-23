from PIL import Image, ImageFilter
import sys,time
###file select
import sys

args = sys.argv

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
f = open("osd/"+args[1]+".osd", "w")
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
    ycache = y * width
    oldx=7
    x=0
    flug=0
    for x in range(width):

      pixdata = imgdata[ycache + x - 1]#int 0-255
      if(pixdata==0 and x!=width):
        flug+=1
        if(flug==1):
          oldx=x
      else:
        if(flug!=0):
          kokuten+=1
          if(y%2==0):
            LK=LK+("{} {} {}\n".format(oldx,x-1,y))#kiauuretu
          else:
            LG=LG+("{} {} {}\n".format(oldx,x-1,y))#guusuuretu
          flug=0
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
