# -*- coding: utf-8 -*-
"""
Created on Wed Sep 23 17:19:41 2020

@author: pablo
"""

from PIL import Image, ImageFilter,ImageDraw 
import numpy as np
from scipy.stats import bernoulli
from scipy.linalg import hilbert
import matplotlib.pyplot as plt

x = hilbert(9)
print(x)

plt.figure()
plt.plot(x)

"""
shape = [(40, 40), (512 - 10, 512 - 10)] 
x = np.array([40,502])
print(x.shape)
# creating new Image object 
img = Image.new("RGB", (512,512)) 
shape = np.array([[x[0],x[0]],[x[1],x[1]],[x[0]+50,x[0]+150],[x[1]+50,x[1]+150]])
shape= np.array([40,40,502,502])
print(shape.shape)
print(shape)
# create line image 
img1 = ImageDraw.Draw(img)   
img1.line(shape, fill ="red", width = 0)
#img1.line(shape, fill ="red", width = 0)

for i in range(0,len(shape)-1): 
    print(i)
    print(shape[i][0])
    print(shape[i][1])
    img1.line([(shape[i][0],shape[i][1]),(shape[i+1][0],shape[i+1][1])], fill ="red", width = 0)

img.show() 
"""
