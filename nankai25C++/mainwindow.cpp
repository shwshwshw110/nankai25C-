#include "stdafx.h"
#include "mainwindow.h"
#include<QPainter>
#include<Qpen>
#include<QBrush>
MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent), isDrawing(false)//初始化函数状态
{
	setWindowTitle("Mouse path Drawing");
	setGeometry(100, 100, 1200, 900);//窗口大小,以100，100为起点，宽1200，高900
}
MainWindow::~MainWindow() {}//清空之前对MainWindow的修改
void MainWindow::mousePressEvent(QMouseEvent* event) {//找到头文件中mousePressEvent进行重写定义，并通过*event与QMouseEvent建立联系，表明使用到了QMouseEvent；
	if (event->button() == Qt::LeftButton) {//表明在这函数中的event指的是button（指针用->,不是指针用.如QMouseEvent.button）（button在QMouseEvent中），并与Qt自身带的LeftButton建立联系，表明鼠标左键按下的时候事件开始。相当于如果按下左键。
		points.clear();//清空之前的路径
		points.append(event->pos());//pos()来源于QMouseEvent表示鼠标坐标，返回一个QPoint类型的坐标，append是指在末尾添加一个内容，由于与points连用，则表示在末尾添加一个点，points可以理解为点集来源于Qvector
		isDrawing = true;//表示开始进行绘制，将false的状态变成true
	}
}
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {//mouseReleaseEvent实际上是来源于QMainWindow，处理鼠标释放事件。意思是说我现在正在创建一个叫mouseReleaseEvent的函数，使得这个函数能够行使只要鼠标松开就停止绘制的功能。同时由此可见鼠标的点击和松开是两个不同的操作；
	if (event->button() == Qt::LeftButton) {
		points.append(event->pos());//将鼠标松开时的点加入点集
		isDrawing = false;//将正在绘画的状态取消
		update();//更新窗口
	}
}//以上两个函数确定了在点击鼠标和松开鼠标时的始末状态
void MainWindow::mouseMoveEvent(QMouseEvent* event) {//mouseMoveEvent用于处理鼠标移动事件，这个函数希望能在中间状态上加入鼠标移动的点
	if (isDrawing) {
		points.append(event->pos());
		update();//更新目前绘制的状态
	}
}
void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);//启用抗锯齿，setRenderHint是绘图渲染函数
	painter.setPen(QPen(Qt::black, 2));//设置画笔，两个像素点宽，黑色
	if (points.size() > 1) {//绘制路径，如果移动了（点的数量大于1）
		painter.drawPolyline(points);//用points被储存的顺序来绘制折线，drawPolyline是Qpainter类的函数，如想用曲线可用drawPath
	}
}