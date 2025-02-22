#include "stdafx.h"
#include "mainwindow.h"
#include<QPainter>
#include<Qpen>
#include<QBrush>
MainWindow::MainWindow(QWidget* parent)
	:QMainWindow(parent), isDrawing(false)//��ʼ������״̬
{
	setWindowTitle("Mouse path Drawing");
	setGeometry(100, 100, 1200, 900);//���ڴ�С,��100��100Ϊ��㣬��1200����900
}
MainWindow::~MainWindow() {}//���֮ǰ��MainWindow���޸�
void MainWindow::mousePressEvent(QMouseEvent* event) {//�ҵ�ͷ�ļ���mousePressEvent������д���壬��ͨ��*event��QMouseEvent������ϵ������ʹ�õ���QMouseEvent��
	if (event->button() == Qt::LeftButton) {//�������⺯���е�eventָ����button��ָ����->,����ָ����.��QMouseEvent.button����button��QMouseEvent�У�������Qt�������LeftButton������ϵ���������������µ�ʱ���¼���ʼ���൱��������������
		points.clear();//���֮ǰ��·��
		points.append(event->pos());//pos()��Դ��QMouseEvent��ʾ������꣬����һ��QPoint���͵����꣬append��ָ��ĩβ���һ�����ݣ�������points���ã����ʾ��ĩβ���һ���㣬points�������Ϊ�㼯��Դ��Qvector
		isDrawing = true;//��ʾ��ʼ���л��ƣ���false��״̬���true
	}
}
void MainWindow::mouseReleaseEvent(QMouseEvent* event) {//mouseReleaseEventʵ��������Դ��QMainWindow����������ͷ��¼�����˼��˵���������ڴ���һ����mouseReleaseEvent�ĺ�����ʹ����������ܹ���ʹֻҪ����ɿ���ֹͣ���ƵĹ��ܡ�ͬʱ�ɴ˿ɼ����ĵ�����ɿ���������ͬ�Ĳ�����
	if (event->button() == Qt::LeftButton) {
		points.append(event->pos());//������ɿ�ʱ�ĵ����㼯
		isDrawing = false;//�����ڻ滭��״̬ȡ��
		update();//���´���
	}
}//������������ȷ�����ڵ�������ɿ����ʱ��ʼĩ״̬
void MainWindow::mouseMoveEvent(QMouseEvent* event) {//mouseMoveEvent���ڴ�������ƶ��¼����������ϣ�������м�״̬�ϼ�������ƶ��ĵ�
	if (isDrawing) {
		points.append(event->pos());
		update();//����Ŀǰ���Ƶ�״̬
	}
}
void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);//���ÿ���ݣ�setRenderHint�ǻ�ͼ��Ⱦ����
	painter.setPen(QPen(Qt::black, 2));//���û��ʣ��������ص����ɫ
	if (points.size() > 1) {//����·��������ƶ��ˣ������������1��
		painter.drawPolyline(points);//��points�������˳�����������ߣ�drawPolyline��Qpainter��ĺ��������������߿���drawPath
	}
}