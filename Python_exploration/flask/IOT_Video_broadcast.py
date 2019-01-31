#!/usr/bin/env python
from flask import Flask, render_template, Response
import cv2

app = Flask(__name__)

def gen(camera):
    while True:
        _, img = camera.read()
        frame=cv2.imencode('.jpg', img)[1].tobytes()
        yield (b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + str(frame) + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(gen(cv2.VideoCapture(2)), mimetype='multipart/x-mixed-replace; boundary=frame')

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True, threaded=True)
