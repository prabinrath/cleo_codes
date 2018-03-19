#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{		
    ros::init(argc, argv, "listener");
    ros::NodeHandle nh;
    QApplication a(argc, argv);
    MainWindow w(nh);
    w.show();
    ros::Rate rate(5);
    while(ros::ok())
    {
        ros::spinOnce();
        rate.sleep();
        a.processEvents();
    }
    return a.exec();
}
