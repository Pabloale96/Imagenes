# -*- coding: utf-8 -*-
"""
Created on Mon Sep 28 12:08:00 2020

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

def upsampling(img,N):
    
    ones = np.ones((N,N))
    w = img.shape[0]*N
    h = img.shape[1]*N
    img2 = np.zeros((w,h))
    for i in range(0,img.shape[0]):
        arrAux = np.empty((N,N))
        for j in range(0,img.shape[1]-1):
            arrAux=np.concatenate((arrAux,img[i][j]*ones),axis=1)
            if j==img.shape[1]-2:
                img2[N*(i):N*(i+1),:]=arrAux
    
    return img2


img = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)

imgPil=Image.fromarray(img)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("original.png")

#%%
kernel = np.ones((5,5),np.float32)/25

imgKernel = cv2.filter2D(img,-1,kernel) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgKernel)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("kernel.png")

hist = cv2.calcHist([imgKernel], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histKernel.png', bbox_inches='tight')

#%%
blur = np.ones((3,3))
blur[0,0] = blur[0,2] = blur[2,0] = blur[2,2] = 0.0625
blur[0,1] = blur[2,1] = blur[1,0] = blur[1,2] = 0.125
blur[1,1] = 0.25


imgBlur = cv2.filter2D(img,-1,blur) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgBlur)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("blur.png")
hist = cv2.calcHist([imgBlur], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histBlur.png', bbox_inches='tight')

#%%
bottomSobel = np.zeros((3,3))
bottomSobel[0,0] = bottomSobel[0,2] = -1
bottomSobel [0,1] = -2
bottomSobel[2,0] = bottomSobel[2,2] = 1
bottomSobel [2,1] = 2

imgBottom = cv2.filter2D(img,-1,bottomSobel) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgBottom)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("bottomSobel.png")

hist = cv2.calcHist([imgBottom], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('bottomSobelhist.png', bbox_inches='tight')

#%%
emboss = np.ones((3,3))
emboss [0,0] = -2
emboss [0,1] = emboss [1,0] = -1
emboss [2,2] = 2

imgEmboss = cv2.filter2D(img,-1,emboss) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgEmboss)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("emboss.png")

hist = cv2.calcHist([imgEmboss], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histemboss.png', bbox_inches='tight')

#%%
leftSobel = np.zeros((3,3))
leftSobel[0,0] = leftSobel[2,0]= 1
leftSobel[0,2] = leftSobel[2,2]= -1
leftSobel[1,0] = 2
leftSobel[1,2] = -2

imgleftSobel = cv2.filter2D(img,-1,leftSobel) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgleftSobel)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("leftSobel.png")

hist = cv2.calcHist([imgleftSobel], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histleftSobel.png', bbox_inches='tight')

#%%
outline = np.ones((3,3))*-1
outline[1,1] = 8

imgOutline = cv2.filter2D(img,-1,outline) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgOutline)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("outline.png")

hist = cv2.calcHist([imgOutline], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histoutlinel.png', bbox_inches='tight')

#%%
laplace= np.ones((3,3))*-1
laplace[0,0] = laplace[0,2] = laplace[2,0] =laplace[2,2]=0
laplace[1,1] = 4

print(laplace)

imglaplace = cv2.filter2D(img,-1,laplace) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imglaplace)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("laplace.png")

hist = cv2.calcHist([imglaplace], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histlaplace.png', bbox_inches='tight')


#%%
rightSobel = np.zeros((3,3))
rightSobel[0,0] = rightSobel[2,0] = -1
rightSobel[0,2] = rightSobel[2,2] = 1
rightSobel[1,0] = -2
rightSobel[1,2] = 2

imgrightSobel= cv2.filter2D(img,-1,rightSobel) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgrightSobel)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("rightSobel.png")

hist = cv2.calcHist([imgrightSobel], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histrightSobel.png', bbox_inches='tight')

#%%
sharpen= np.zeros((3,3))
sharpen[0,1] = sharpen[1,0] = sharpen[2,1] = sharpen[1,2] = -1
sharpen[1,1] = 5
 
print(sharpen)

imgsharpen= cv2.filter2D(img,-1,sharpen) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgsharpen)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("sharpen.png")

hist = cv2.calcHist([imgsharpen], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histsharpen.png', bbox_inches='tight')


#%%
topSobel= np.zeros((3,3))

topSobel[0,0] = topSobel[0,2] = 1 
topSobel[2,0] = topSobel[2,2] = -1 
topSobel[0,1] = 2
topSobel[2,1] = -2

imgtopSobel= cv2.filter2D(img,-1,topSobel) #aplica el filtro kernel a la imagen.
imgPil=Image.fromarray(imgtopSobel)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("topSobel.png")

hist = cv2.calcHist([imgtopSobel], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('histtopSobel.png', bbox_inches='tight')

#%%

imgBf1 = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)

imgBf1[0:256,0:256] = imgOutline[0:256,0:256]
imgBf1[0:256,256:512] = imgsharpen[0:256,256:512]
imgBf1[256:512,0:256] = imgKernel[256:512,0:256]
imgBf1[256:512,256:512] = imgrightSobel[256:512,256:512]

imgPil=Image.fromarray(imgBf1)
if imgPil.mode != 'RGB':
    imgPil = imgPil.convert('RGB')
imgPil.show()
imgPil.save("imgBf1.png")

hist = cv2.calcHist([imgBf1], [0], None, [256], [0, 256])
plt.figure()
plt.plot(hist)
plt.savefig('imgBf1hist.png', bbox_inches='tight')
