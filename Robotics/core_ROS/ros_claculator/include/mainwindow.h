#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ros::NodeHandle _nh,QWidget *parent = 0);
    ~MainWindow();
    void callback(const std_msgs::Int32::ConstPtr& msg);

private slots:
    	void on_pb_0_clicked();
	void on_pb_1_clicked();
	void on_pb_2_clicked();
	void on_pb_3_clicked();
	void on_pb_4_clicked();
	void on_pb_5_clicked();
	void on_pb_6_clicked();
	void on_pb_7_clicked();
	void on_pb_8_clicked();
	void on_pb_9_clicked();
	void on_pb_add_clicked();
	void on_pb_sub_clicked();
	void on_pb_mul_clicked();
	void on_pb_div_clicked();
	void on_pb_eql_clicked();
	void on_pb_clr_clicked();
	
private:
    Ui::MainWindow *ui;
    ros::NodeHandle nh;
    ros::Subscriber sub;
};

#endif // MAINWINDOW_H
