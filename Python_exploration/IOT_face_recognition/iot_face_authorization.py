'''
A python code to implement face Authorization using KAIROS face recognition API for IOT solutions. The code uses Pyserial for establising Serial communication with the Arduino that lights up a green LED for successful authorization and red for unsuccessful authorization.
'''
import cv2
import requests,base64,json
import serial
import time

ser=serial.Serial('/dev/ttyACM0',9600)

face_cascade = cv2.CascadeClassifier('data/haarcascades/haarcascade_frontalface_default.xml')

cap = cv2.VideoCapture(0)

imr=0
imr_counter=0

while(True):
    	# Capture frame-by-frame
	if imr==1:
	    break
    	ret, frame = cap.read()
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
	faces = face_cascade.detectMultiScale(gray, 1.3, 5)
	for (x,y,w,h) in faces:
	    cv2.rectangle(frame,(x,y),(x+w,y+h),(255,0,0),2)
	    img_name="pkr.jpg".format(imr_counter)
	    cv2.imwrite(img_name,frame)
	    print("{} written!".format(img_name))
	    imr_counter+=1
	    imr=1
	    break
	cv2.imshow('face detected',frame)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break

cap.release()
cv2.destroyAllWindows()

with open("pkr.jpg","rb") as image_file:
    encoded_string=base64.b64encode(image_file.read())

headers = {
    'content-type':'application.json',
    "app_id": "Your app id",
    "app_key": "Your app key"
}

payload_dict = {"image":encoded_string,"gallery_name":"MyGallery"}
payload=json.dumps(payload_dict)

url = "http://api.kairos.com/recognize"

r = requests.post(url,data=payload,headers=headers)

print r.content

if '"status":"success"' in r.content:
	print('Found')
	ser.write("g")
	time.sleep(5)
elif '"status":"failure"' in r.content:
	print('Not Found')
	ser.write("r")
	time.sleep(5)

ser.write("s")
