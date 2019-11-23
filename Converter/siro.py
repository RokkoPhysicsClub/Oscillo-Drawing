from PIL import Image, ImageFilter
import numpy as np


for i in range(100000):
  img = Image.open('images/{0:05d}.png'.format(i+1))
  width, height = img.size
  im2=Image.new('RGB', (width, height))
  img_pixels = []
  for y in range(height):
    for x in range(width):
      r,g,b = img.getpixel((x,y))
      r=int(round((r+g+b)/3/64)*64)
      im2.putpixel((x,y),(r,r,r,0))
  im2.save('images_done/{0:05d}.png'.format(i+1))
  print (i)
