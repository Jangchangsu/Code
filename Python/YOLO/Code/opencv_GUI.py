import cv2 as cv
import os
import time

def onMouse(event,x,y,flags,param):
    if event == cv.EVENT_LBUTTONDBLCLK:
        param[0] = cv.circle(param[0],(x,y),50,(255,0,0),5)


directory = "C:\\Users\\jangh\\Desktop\\Code\\Python\\YOLO"
Image_directory = os.path.join(directory,"Image")
file0 = os.path.join(Image_directory,"Lenna.png")

img = cv.imread(file0,cv.IMREAD_COLOR)
cvt_img = img.copy()
param = [cvt_img]

cv.namedWindow("My Image",cv.WINDOW_AUTOSIZE)
cv.setMouseCallback("My Image",onMouse,param)
roi = cv.selectROI("My Image", cvt_img) #범위 지정하고 enter 누르면 넘어감
print(roi)

while True: 
    key = cv.waitKey(1000)
    if key == ord("q"): 
        break 
    elif key == ord("g"):
       cvt_img = cv.cvtColor(cvt_img, cv.COLOR_BGR2GRAY)
    cv.imshow("My Image",cvt_img)

