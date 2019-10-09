#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, float* x, float* y,int n1,int n2, lineSegment** segments, float a, float b)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->x = x;
    this->y = y;
    this->n1 = n1;
    this->n2 = n2;
    this->a = a;
    this->b = b;
    this->segments = segments;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen points;
    QPen text;

    text.setWidth(2);

    points.setCapStyle(Qt::RoundCap);
    points.setWidth(4);

    painter.drawText(QPoint(10,20),"number of intersections : " + QString::number(this->n2));
    painter.setPen(Qt::blue);
    painter.drawText(QPoint(10,40),"The fit line is of the form "+QString::number(this->a)+"x + "+QString::number(this->b));

    for (int i = 0; i < n1; i++) {
        lineSegment* seg = segments[i];
        QPointF p1(seg->left->x,seg->left->y);
        QPointF p2(seg->right->x,seg->right->y);
        painter.setPen(Qt::black);
        painter.drawLine(p1,p2);
        painter.setPen(points);
        painter.drawPoint(p1);
        painter.drawPoint(p2);
        painter.setPen(text);
        painter.drawText(p1,"("+QString::number(p1.rx())+","+QString::number(p1.ry())+")");
        painter.drawText(p2,"("+QString::number(p2.rx())+","+QString::number(p2.ry())+")");
    }

    points.setColor(Qt::red);
    text.setColor(Qt::red);
    for (int i = 0; i < n2; i++) {
        QPointF p(x[i],y[i]);
        painter.setPen(points);
        painter.drawPoint(p);
        painter.setPen(text);
        painter.drawText(p,"("+QString::number(p.rx())+","+QString::number(p.ry())+")");
    }

    float y1 = b;
    float y2 = a*1000 + b;
    painter.setPen(Qt::blue);
    painter.drawLine(QPointF(0,y1),QPointF(1000,y2));

}

