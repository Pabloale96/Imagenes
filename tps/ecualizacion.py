# -*- coding: utf-8 -*-
"""
Created on Sun Sep 27 15:55:00 2020

@author: pablo
"""
import cv2
import numpy as np
import matplotlib.pyplot as plt
 
img = cv2.imread('lenna.bmp', cv2.IMREAD_GRAYSCALE)
#img_to_yuv = cv2.cvtColor(img,cv2.COLOR_BGR2YUV)
img2 = cv2.equalizeHist(img)
#hist_equalization_result = cv2.cvtColor(img_to_yuv, cv2.COLOR_YUV2BGR)
 
cv2.imwrite('ecualidazorHistograma.png',img2)
 
# Create zeros array to store the stretched image
minmax_img = np.zeros((img2.shape[0],img2.shape[1]),dtype = 'uint8')
 
# Loop over the image and apply Min-Max formulae
for i in range(img2.shape[0]):
    for j in range(img2.shape[1]):
        minmax_img[i,j] = 255*(img2[i,j]-np.min(img2))/(np.max(img2)-np.min(img2))
 
# Displat the stretched image
cv2.imwrite('stretching.png',minmax_img)
#cv2.waitKey(0)





hist = cv2.calcHist([img], [0], None, [256], [0, 256])
hist2 = cv2.calcHist([img2], [0], None, [256], [0, 256])

plt.figure()
plt.plot(hist)
plt.savefig('histOriginal.png', bbox_inches='tight')
plt.figure()
plt.plot(hist2)
plt.savefig('histEcualizado.png', bbox_inches='tight')
plt.show()