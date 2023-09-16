import os
import numpy
import cv2 as cv

data_path = "C:\\Users\\jangh\\Desktop\\Code\\Python\\YOLO"
image_file_path = os.path.join(data_path,"Image")
train_data = os.path.join(image_file_path,"Lenna.png")

img = cv.imread(train_data,cv.IMREAD_COLOR)

line_img = img.copy()
circle_img = img.copy()
rectangle_img = img.copy()
text_img = img.copy()

line_img = cv.line(line_img,(0,0),(img.shape[0], img.shape[1]),(255,255,0), 1, cv.LINE_AA) # Parameter | 1: 이미지파일 2: 시점 좌표(top-left) 3: 종점 좌표(botton-right) 4: (B,G,R) 5: 선 굵기 6: 안티 앨리어싱 활성화
circle_img = cv.circle(circle_img,(img.shape[1]//2,img.shape[0]//2),100,(0,255,0),5, cv.LINE_AA) # Parameter | 1: 이미지파일 2: 원점 좌표 3: 지름 크기  4: (B,G,R) 5: 선 굵기 6: 안티 앨리어싱 활성화
rectangle_img = cv.rectangle(rectangle_img,(100,100),(300,400),(0,0,255),5) # Parameter | 1: 이미지파일 2: 시점 좌표(top-left) 3: 종점 좌표(botton-right)  4: (B,G,R) 5: 선 굵기 6: 안티 앨리어싱 활성화
text_img = cv.putText(text_img,"This is Lenna",(100,100),cv.FONT_HERSHEY_SIMPLEX,3,(128,0,128),5, cv.LINE_AA) # Parameter | 1: 이미지파일 2: "TEXT" 3: 시점 좌표(bottom-left) 4: FONT 5: FONT SIZE 6: (B,G,R) 7: 선 굵기 8: 안티 앨리어싱 활성화

cv.imwrite(os.path.join(image_file_path,"Line_Drawed_Lenna.jpg"),line_img)
cv.imwrite(os.path.join(image_file_path,"Circle_Drawed_Lenna.jpg"),circle_img)
cv.imwrite(os.path.join(image_file_path,"Rectangle_Drawed_Lenna.jpg"),rectangle_img)
cv.imwrite(os.path.join(image_file_path,"Text_Inserted_Lenna.jpg"),text_img)