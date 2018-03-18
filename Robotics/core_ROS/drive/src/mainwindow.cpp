#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), nh(_nh)
{
    ui->setupUi(this);
    sub = nh.subscribe("check", 1, &MainWindow::callback1, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cnglbl_clicked()
{
	ui->label->setText("$_By Prabin Rath_$");
}

void MainWindow::on_opngdt_clicked()
{
	QDesktopServices::openUrl(QUrl("file:///home/prabin/Documents/Qt_temp"));	

	//QDesktopServices::openUrl(QUrl("http://www.pkrentertainment.webs.com"));

	/*QString program = "/usr/share/applications/gedit";
 
    	QStringList arguments;
 
    	QProcess *myProcess = new QProcess(this);
    	myProcess->start(program,(QStringList) arguments<<"/home/prabin/new.cpp");*/
}

void MainWindow::callback1(const drive::drivedata::ConstPtr& msg)
{
   	ui->label->setText((QString)msg->drive);
}

