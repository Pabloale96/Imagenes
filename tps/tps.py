# -*- coding: utf-8 -*-
"""
Created on Mon Sep 21 21:01:12 2020

@author: pablo
"""

from PIL import Image, ImageFilter, ImageDraw 
import numpy as np
from scipy.stats import bernoulli
from scipy.fftpack import dct, idct
import cv2
import matplotlib.pyplot as plt
import math as mt

# implement 2D DCT
def dct2(a):
    return dct(dct(a.T, norm='ortho').T, norm='ortho')

# implement 2D IDCT
def idct2(a):
    return idct(idct(a.T, norm='ortho').T, norm='ortho')   
"""
def hilbert_curve(order):
    A = np.zeros((0,2))
    B = np.zeros((0,2))
    C = np.zeros((0,2))
    D = np.zeros((0,2))
    north = np.array([[ 0 ,1]])
    east  = np.array([[ 1 ,0]])
    south = np.array([[0 ,-1]])
    west  = np.array([[ -1 ,0]])

    for i in range(0,order):
        AA = np.concatenate([B,north,A,east,A,south,C])
        BB = np.concatenate([A,east,B,north,B,west,D])
        CC = np.concatenate([B,west,C,south,C,east,A])
        DD = np.concatenate([C,south,D,west,D,north,B])

        A = AA;
        B = BB;
        C = CC;
        D = DD;
        
        
    subs = np.concatenate((np.array([[0,0]]),np.cumsum(A,axis=0)))
    x=np.array((len(subs),1))
    y=np.array((len(subs),1))
    x = subs[:,0];
    y = subs[:,1];
    return x,y,AA
"""
#%%
img = Image.open('lenna.bmp').convert('L')
#img.show()
arr = np.asarray(img)

arr1 = arr + 150*np.ones((1,1))
img=Image.fromarray(arr1)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("ruidoCte.png")


mean = 100
std = 50 
num_samples = arr.shape
noise = np.random.normal(mean, std, size=num_samples)
arr2 = arr + noise
img=Image.fromarray(arr2)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("ruidoAleatorioNormal.png")

ber = bernoulli.rvs(0.5, size=arr.shape)*100
arr3 = arr + ber
img=Image.fromarray(arr3)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.show()
img.save("ruidoAleatorioBernuli.png")


#%%
dif = np.zeros((512*512,1))
k=0
arr4 = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)
for i in range(0,512):
    for j in range(0,511):
        dif[k] = (arr[i][j]-arr[i][j+1])
        k=k+1
        if(np.abs(arr[i][j+1]-arr[i][j])>0.5):
            if (arr[i][j+1]>arr[i][j]):
                arr4[i][j] = 0


hist = cv2.calcHist([arr4], [0], None, [256], [0, 256])
#print(hist.shape)
plt.figure()
plt.plot(hist)
plt.savefig("recorridoHorizontal-Histograma.png", bbox_inches='tight')
#plt.ylim([0,60])
            
img=Image.fromarray(arr4)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.save("recorridoHorizontal.png")
img.show()

dif = np.zeros((512*512,1))
k=0
img = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)
for i in range(0,512):
    for j in range(0,511):
        dif[k] = (arr[j][i]-arr[j+1][i])
        k=k+1
        if(np.abs((arr[j][i]-arr[j+1][i]))>0.5):
            if (arr[j+1][i]>arr[j][i]):
                arr5[j][i] = 0


hist = cv2.calcHist([arr5], [0], None, [256], [0, 256])
#print(hist.shape)
plt.figure()
plt.plot(hist)
plt.savefig("recorridoVertical-Histograma.png", bbox_inches='tight')
#plt.ylim([0,60])
plt.show()
img=Image.fromarray(arr5)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.save("recoridoVertical.png")
img.show()

arr6= arr5+arr4
img=Image.fromarray(arr6)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.save("sumaRecorido.png")
img.show()

"""
order = 9
x,y,AA = hilbert_curve(order)
plt.figure()
plt.plot(x,y)
plt.show()

x=np.dstack((x,np.zeros_like(x))).reshape(x.shape[0],-1)
y=np.dstack((y,np.zeros_like(y))).reshape(y.shape[0],-1)
for i in range(0,len(x)):
    x[i][1]=y[i][0]
img = Image.open('lenna.bmp').convert('L')
img1=ImageDraw.Draw(img)
for i in np.arange(0,131072*2-1):

    img1.point([(x[i][0],x[i][1])],fill='red')

img.show()
"""
#%%
arr = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)
imF = dct2(arr)


plt.figure()
plt.hist(arr,255,[0,200],facecolor='g')
plt.hist(imF,255,[0,200],facecolor='r')
plt.savefig("transformadaCoseno.png", bbox_inches='tight')
plt.show()

img=Image.fromarray(imF)
if img.mode != 'RGB':
    img = img.convert('RGB')
img.save("transformadaCoseno.png")


arr7 = idct2(imF)
img=Image.fromarray(np.log(np.abs(arr7)))
if img.mode != 'RGB':
    img = img.convert('RGB')
#img.save("recoridoVertical.png")
img.show()






