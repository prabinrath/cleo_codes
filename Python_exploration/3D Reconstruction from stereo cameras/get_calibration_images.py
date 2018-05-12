import numpy as np
import cv2

ROWS=9;COLS=6;count=50;
train_path='/home/prabin/python/openCV_samples/stereovision/final/calibration_pictures/'
capl = cv2.VideoCapture(2)
capr = cv2.VideoCapture(3)
i=0
while i<count:
	retl,img_l=capl.read()
	retr,img_r=capr.read()
	if not(retl) or not(retr):
		print('Camera feed unavailable')
		break
	gray_l = cv2.cvtColor(img_l, cv2.COLOR_BGR2GRAY)
	gray_r = cv2.cvtColor(img_r, cv2.COLOR_BGR2GRAY)
	retl, corners_l = cv2.findChessboardCorners(gray_l, (ROWS,COLS), flags=cv2.CALIB_CB_FAST_CHECK)
	retr, corners_r = cv2.findChessboardCorners(gray_r, (ROWS,COLS), flags=cv2.CALIB_CB_FAST_CHECK)
	
	if retl and retr:
		print('Board Detected in both feeds')
		if i<9:
			name_l='left_0'+str(i+1)+'.jpg'
			name_r='right_0'+str(i+1)+'.jpg'
		else:
			name_l='left_'+str(i+1)+'.jpg'
			name_r='right_'+str(i+1)+'.jpg'
		cv2.imwrite(train_path+name_l, img_l)
		cv2.imwrite(train_path+name_r, img_r)
		retl = cv2.drawChessboardCorners(img_l, (ROWS,COLS),corners_l, retl)
		retr = cv2.drawChessboardCorners(img_r, (ROWS,COLS),corners_r, retr)
		cv2.imshow('Image_aquired L', img_l)
		cv2.imshow('Image_aquired R', img_r)
		i+=1
		cv2.waitKey(2000)
	else:
		print('Couldnt Find ChessBoard in both feeds')
cv2.destroyAllWindows()
		
		
		

