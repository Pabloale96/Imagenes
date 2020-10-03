# -*- coding: utf-8 -*-
"""
Created on Sat Sep 26 19:30:59 2020

@author: pablo
"""


from PIL import Image, ImageFilter, ImageDraw 
import numpy as np
from scipy.stats import bernoulli
from scipy.fftpack import dct, idct
from scipy.ndimage import zoom
import cv2
import matplotlib.pyplot as plt
import math as mt

arr = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)
img = Image.open('lenna.bmp').convert('L')
arr = np.asarray(img)

arr = arr.reshape((-1,1))
arr = np.float32(arr)
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.2)
k = np.array([5,10,20,40,80,100,255])
for i in range(0,len(k)):
    _,labels, (centers) = cv2.kmeans(arr, k[i], None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
    centers = np.uint8(centers)
    labels = labels.flatten()

    arr3 = np.zeros((512*512,1))
    for j in range(0,512*512):
        arr3[j] = centers[labels[j]] 


    arr3 = arr3.reshape(512,512)

    img=Image.fromarray(arr3)
    if img.mode != 'RGB':
        img = img.convert('RGB')
    asd = np.array2string(k[i])
    img.save('kmeans-k-'+asd+'.png')
    img.show()


#img.save("recoridoVertical.bmp")
