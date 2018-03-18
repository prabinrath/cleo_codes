#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <drive/defaultConfig.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <drive/drivedata.h>
#include <cstring>

using namespace cv;
using namespace std;

int shp=3;

int iLowH = 0;int iHighH = 179;
int iLowS = 0;int iHighS = 255;
int iLowV = 0;int iHighV = 255;

void callback(drive::defaultConfig &config, uint32_t level) 
{
  if(config.set_HSV==1){iLowH = 90;iHighH = 148;iLowS = 32;iHighS = 255;iLowV = 0;iHighV = 197;}
  else if(config.set_HSV==2){iLowH = 145;iHighH = 179;iLowS = 131;iHighS = 208;iLowV = 97;iHighV = 255;}
  else if(config.set_HSV==3){iLowH = 60;iHighH = 92;iLowS = 53;iHighS = 255;iLowV = 42;iHighV = 157;}
  else if(config.set_HSV==4){iLowH = 0;iHighH = 179;iLowS = 0;iHighS = 255;iLowV = 0;iHighV = 99;}
  else if(config.set_HSV==5){iLowH = 60;iHighH = 92;iLowS = 53;iHighS = 255;iLowV = 42;iHighV = 157;}
  else {iLowH = 0;iHighH = 179;iLowS = 0;iHighS = 255;iLowV = 0;iHighV = 255;}

  if(config.set_shape=="triangle")shp=3;
  else if(config.set_shape=="square")shp=4;
  else if(config.set_shape=="pentagon")shp=5;
  else if(config.set_shape=="hexagon")shp=6;
  else if(config.set_shape=="circle")shp=8;
  else shp=5;
}

int main(int argc, char** argv)
{
	  ros::init(argc, argv, "drive_pub");
	  ros::NodeHandle nh;

	  dynamic_reconfigure::Server<drive::defaultConfig> server;
  	  dynamic_reconfigure::Server<drive::defaultConfig>::CallbackType f;
  	  f = boost::bind(&callback, _1, _2);
  	  server.setCallback(f);

	  ros::Publisher pub = nh.advertise<drive::drivedata>("drive_pub", 1000);
	  
	  //VideoCapture cap("http://10.175.169.202:8080/videofeed?dummy=param.mjpg");
	  VideoCapture cap(2);
	  if ( !cap.isOpened() )
	    {
		 std::cout << "Cannot open the video file" << std::endl;
		 return -1;
	    }

  	  namedWindow("Raw Feed", CV_WINDOW_NORMAL);
	  namedWindow("Threshold feed", CV_WINDOW_NORMAL);
	  namedWindow("Tracking", CV_WINDOW_NORMAL);
	  namedWindow("Control", CV_WINDOW_NORMAL);

	  cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	  cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	  cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	  cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	  cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	  cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	  int cx,cy;float ar;
	  char drv='k';

	  ros::Rate loop_rate(30);
	  while (nh.ok())
		{
		Mat frame;
        	bool bSuccess = cap.read(frame);
		if (!bSuccess)
        	{
             	std::cout << "Cannot read a frame from video stream" << std::endl;
             	break;
        	}
		
		Mat hsv,thresh;
		cvtColor(frame, hsv, CV_BGR2HSV);

		inRange(hsv, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), thresh);

		Rect bounding_rect;
		vector<vector<Point> > contours;
    		vector<Vec4i> hierarchy;
    		findContours( thresh, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
		vector<Point> approx;

		for (int i = 0; i < contours.size(); i++)
		{
			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
			if (fabs(contourArea(contours[i])) < 100 || !isContourConvex(approx))
			continue;
			if (approx.size() == shp)
			{
				Moments mom = moments(contours[i]);
				cy=mom.m01/mom.m00,cx=mom.m10/mom.m00;ar=mom.m00;
				//cout<<"contour X "<<cx<<" contour Y "<<cy<<"contour area "<<mom.m00<<endl;
				bounding_rect=boundingRect(contours[i]);
			}
		}

		Mat dst=frame.clone();
		rectangle(dst, bounding_rect,  Scalar(255,0,0),2, 8,0);
		imshow( "Raw Feed", frame );
		imshow( "Threshold feed", thresh );
		imshow( "Tracking", dst );
		if (waitKey(30) == 27)
       		{
            		std::cout << "esc key is pressed by user" << std::endl;
            		break;
       		}

		if(cx>(0.75*frame.cols))
		drv='d';
		else if(cx<(0.25*frame.cols))
		drv='a';
		else if(ar>5000)
		drv='s';
		else if(ar<3000)
		drv='w';
		else
		drv='l';

		drive::drivedata msg;
		msg.num1=cx;msg.num2=cy;msg.drive=drv;
		pub.publish(msg);

	    	ros::spinOnce();
	    	loop_rate.sleep();
	  	}
}
