//Don't make unknown changes
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{		
    ros::init(argc, argv, "chess_ui_fen");
    ros::NodeHandle nh;
    QApplication a(argc, argv);
    MainWindow w(nh);
    w.show();
    ros::Rate rate(10);
    while(ros::ok() && w.isVisible())
    {
        ros::spinOnce();
        rate.sleep();
        a.processEvents();
    }
    return 0;
}
