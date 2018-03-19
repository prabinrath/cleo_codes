#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ros/ros.h>
#include <drive/drivedata.h>
#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ros::NodeHandle _nh,QWidget *parent = 0);
    ~MainWindow();
    void callback1(const drive::drivedata::ConstPtr& msg);

private slots:
	void on_cnglbl_clicked();
	void on_opngdt_clicked();

private:
    Ui::MainWindow *ui;
    ros::NodeHandle nh;
    ros::Subscriber sub;
};

#endif // MAINWINDOW_H
