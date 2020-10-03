# -*- coding: utf-8 -*-
"""
Created on Sun Sep 27 17:39:49 2020

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

print("1 ciclo")
ones = np.ones((2,2))
ones[0][1] = 0.5
ones[1][1] = 0.5
zeros = np.ones((2,2))
zeros[0][1] = 0.5
zeros[1][1]=0.5
zeros[0][0] = 0
zeros[1][0]=0
arr2 = np.zeros((512,512))
print(ones)
print(zeros)
print(arr[0][0]*ones)
print(arr[0][1]*zeros)
print(arr[0][0]*ones+arr[0][1]*zeros)
print(arr[0][2]*ones+arr[0][3]*zeros)
print(np.concatenate((arr[0][0]*ones+arr[0][1]*zeros,arr[0][1]*ones+arr[0][2]*zeros),axis=1))
print(arr2[0:2][:].shape)
for i in range(0,255):
    arrAux = np.empty((2,2))
    for j in range(0,255):
        arrAux=np.concatenate((arrAux,arr[i][j]*ones+arr[i][j+1]*zeros),axis=1)
        if j==254:
            arr2[2*i:2*(i+1)][:]=arrAux
            
        
img=Image.fromarray(arr2)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("sup-izqZoom0.png")
print("2 ciclo")
ones = np.ones((2,2))
arr2 = np.zeros((512,512))
print(np.concatenate((arr[0][0]*ones,arr[1][1]*ones)))
print(arr2[0:2][:].shape)
for i in range(256,511):
    arrAux = np.empty((2,2))
    for j in range(256,511):
        arrAux=np.concatenate((arrAux,arr[i][j]*ones),axis=1)
        if j==510:
            arr2[2*(i-256):2*(i-256+1)][:]=arrAux
        
img=Image.fromarray(arr2)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("inf-derZoom0.png")

print("3 ciclo")
ones = np.ones((2,2))
arr2 = np.zeros((512,512))
print(np.concatenate((arr[0][0]*ones,arr[1][1]*ones)))
print(arr2[0:2][:].shape)
for i in range(0,255):
    arrAux = np.empty((2,2))
    for j in range(256,511):
        arrAux=np.concatenate((arrAux,arr[i][j]*ones),axis=1)
        if j==510:
            arr2[2*i:2*(i+1)][:]=arrAux
        
img=Image.fromarray(arr2)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("sup-derZoom0.png")
print("4 ciclo")
ones = np.ones((2,2))
arr2 = np.zeros((512,512))
print(np.concatenate((arr[0][0]*ones,arr[1][1]*ones)))
print(arr2[0:2][:].shape)
for i in range(256,511):
    arrAux = np.empty((2,2))
    for j in range(0,255):
        arrAux=np.concatenate((arrAux,arr[i][j]*ones),axis=1)
        if j==254:
            arr2[2*(i-256):2*(i-256+1)][:]=arrAux
        
img=Image.fromarray(arr2)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("inf-izqZoom0.png")