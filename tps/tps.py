# -*- coding: utf-8 -*-
"""
Created on Mon Sep 21 21:01:12 2020

@author: pablo
"""

from PIL import Image
img = Image.open('lenna.bmp').convert('L')
img.show()
img.save('lennagris.bmp','bmp')

print(img)