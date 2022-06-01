import cv2
import numpy as np
from dvr_class import *
dvr_link = 'http://169.254.108.159'
user_name = 'admin'
password = 'admin000'
cap = DvrCamera(dvr_link,user_name,password)
while cv2.waitKey(1) != ord("d"):
    _,frame = cap.read(1)
    gray = cv2.cvtColor(frame,COLOR_BGR2GRAY)
    thresh = cv2.adaptiveThreshold(gray)
    canny = cv2.Canny(thresh,50,150,apertureSize=3)
    
