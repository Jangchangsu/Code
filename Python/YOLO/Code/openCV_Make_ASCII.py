import numpy as np
import cv2 as cv
import os

def print_ascii_img(ascii_img):
    for i in range(ascii_img.shape[0]):
        for j in range(ascii_img.shape[1]):
            print(ascii_img[i,j].decode("utf-8"), end="")
        print()

def img2ascii(img, L, ascii_string):
    ascii_img = np.chararray(img.shape)
    qunit = 256//L
    for i  in range (img.shape[0]):
        for j  in range (img.shape[1]):
            index = img[i,j] // qunit
            ascii_img[i,j] = ascii_string[index]
    return ascii_img

data_path = "C:\\Users\\jangh\\Desktop\\Code\\Python\\YOLO"
image_file_path = os.path.join(data_path,"Image")
train_data = os.path.join(image_file_path,"Lenna.png")

train_img = cv.imread(train_data,cv.IMREAD_COLOR)
cv2gray_img = cv.cvtColor(train_img,cv.COLOR_BGR2GRAY)

ascii_string = "@#BPDQOUo=+*~-`."
ascii_img = img2ascii(cv2gray_img, 16, ascii_string)
print_ascii_img(ascii_img)
