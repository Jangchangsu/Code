import cv2
import os

data_path = "C:\\Users\\jangh\\Desktop\\Code\\Python\\YOLO"
image_data_path = os.path.join(data_path,'Image')
train_data0 = os.path.join(image_data_path,'Lenna.png')

 
color_img = cv2.imread(train_data0,cv2.IMREAD_COLOR)
gray_img = cv2.imread(train_data0,cv2.IMREAD_GRAYSCALE)
cvt2gray_img = cv2.cvtColor(color_img,cv2.COLOR_BGR2GRAY)
resized_img = cv2.resize(color_img,(1024,1024))
cropped_img = color_img[0:color_img.shape[0]//2,0:color_img.shape[1]//2]

if cv2.imwrite(os.path.join(image_data_path,"Gray_Lenna.jpg"),gray_img):
    print("Complete the Saving")
else:
    print("Fail the Saving")
if cv2.imwrite(os.path.join(image_data_path,"Convert2Gray_Lenna.jpg"),cvt2gray_img):
    print("Complete the Converting")
else: 
    print("Fail the Converting")
if cv2.imwrite(os.path.join(image_data_path,"Resizing_Lenna.jpg"),resized_img):
    print("Complete the resizing")
    print(resized_img.shape)
else:
    print("Fail the Resizing")
if cv2.imwrite(os.path.join(image_data_path,"Cropping_Lenna.jpg"),cropped_img):
    print("Complete the Cropping")
    print(cropped_img.shape)
else:
    print("Fail the Cropping")