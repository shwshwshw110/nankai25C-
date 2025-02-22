#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include<QMainWindow>
#include<QMouseEvent>
#include<QPainter>
#include<QVector>
#include<QPoint>
class MainWindow :public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
protected:
	void mousePressEvent(QMouseEvent* event)override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
private:
	QVector<QPoint>points;//动态储存鼠标路径所经过的点
	bool isDrawing;//判断是否正在进行绘制
};