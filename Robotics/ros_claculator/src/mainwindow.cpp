#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "std_msgs/Int32.h"
#include "myfirstros_node/Num.h"
#include <sstream>
#include <pthread.h>

int32_t ka=0,kb=0,val=0;char opr='!';//data modifiers
bool cnt=false;//counters

void *ROS_task(void *q)
	{
	ros::NodeHandle h;
	ros::Publisher pub;
    	pub = h.advertise<myfirstros_node::Num>("question", 1000);
    	ros::Rate loop_rate(5);
	while(ros::ok())
   	{
    	myfirstros_node::Num msg;
    	msg.num1 = ka;
	msg.num2 = kb;
	msg.ch=opr;
	
	if(cnt==true)
    	{
		pub.publish(msg);
		ka=kb=0;
    		opr='!';
		val=0;
		cnt=false;
	}
    	loop_rate.sleep();
    	ros::spinOnce();
   	}
	pthread_exit(NULL);
	}

MainWindow::MainWindow(ros::NodeHandle _nh, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), nh(_nh)
{
    	ui->setupUi(this);

	sub = nh.subscribe("answer", 1, &MainWindow::callback, this);
	
    	pthread_t thread;
	int rc;
	rc=pthread_create(&thread,NULL,ROS_task,(void *)val);
	if(rc)
	{
	ROS_INFO("Error %d",rc);
	exit(-1);
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_0_clicked()
{
    val=(val*10)+0;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_1_clicked()
{
    val=(val*10)+1;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_2_clicked()
{
    val=(val*10)+2;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_3_clicked()
{
    val=(val*10)+3;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_4_clicked()
{
    val=(val*10)+4;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_5_clicked()
{
    val=(val*10)+5;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_6_clicked()
{
    val=(val*10)+6;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_7_clicked()
{
    val=(val*10)+7;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_8_clicked()
{
    val=(val*10)+8;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_9_clicked()
{
    val=(val*10)+9;
    if(opr=='!')
	ka=val;
    else
	kb=val;
    ui->lcd1->display(val);
}

void MainWindow::on_pb_add_clicked()
{
    opr='+';val=0;
}

void MainWindow::on_pb_sub_clicked()
{
    opr='-';val=0;
}

void MainWindow::on_pb_mul_clicked()
{
    opr='*';val=0;
}

void MainWindow::on_pb_div_clicked()
{
    opr='/';val=0;
}

void MainWindow::on_pb_eql_clicked()
{
    cnt=true;  
}

void MainWindow::on_pb_clr_clicked()
{
    ka=kb=0;val=0;
    opr='!';
    ui->lcd1->display(val);
}

void MainWindow::callback(const std_msgs::Int32::ConstPtr& ans)
{
    ui->lcd1->display(ans->data);
}

