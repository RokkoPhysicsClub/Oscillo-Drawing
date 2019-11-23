from PIL import Image, ImageFilter

#new_im=im.convert('1')
#new_im.save('bad2/00018.png')
for i in range(16590):
  im = Image.open('images/{0:05d}.png'.format(i+1))
  new_im=im.convert('1')
  new_im.save('images_done/{0:05d}.png'.format(i+1))
  print (i)
