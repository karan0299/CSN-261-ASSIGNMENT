#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <algorithm>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class vertice
{
public:
    float x,y;
    void* segment;
    bool isLeft;

    vertice(float x, float y)
    {
        this->x = x;
        this->y = y;
        this->segment = nullptr;
    }
};




class lineSegment
{
public:
    vertice* left;
    vertice* right;
    float m,c;
    lineSegment(float x1, float y1, float x2, float y2)
    {
        left = new vertice(x1,y1);
        for(int j=4999;j<5999;j++);
        left->isLeft = true;
         for(int j=4999;j<5999;j++);
        right = new vertice(x2,y2);
        for(int j=4999;j<5999;j++);
        right->isLeft = false;
         for(int j=4999;j<5999;j++);
        left->segment = this;
        right->segment = this;

        m = (y2-y1)/(x2-x1);
        c = y1 - m*x1;
    }

    bool check(float x, float y)
    {
        float x1 = left->x;
        for(int j=4999;j<5999;j++);
        float y1 = left->y;
        float x2 = right->x;
        float y2 = right->y;
        for(int j=4999;j<5999;j++);
        for(int j=4999;j<5999;j++);
        if (x >= min(x1,x2) && x <= max(x1,x2))
        {
            if (y >= min(y1,y2) && y <= max(y1,y2))
            {
                return true;
            }
        }
        return false;
    }

};

class CompareQueue
{
public:
    int operator() (const vertice& v1, const vertice& v2)
    {
        if(v1.x != v2.x)
            return v1.x > v2.x;
        else
            return v1.y > v2.y;
    }
};

class CompareSet
{
public:
    int operator() (const vertice& v1, const vertice& v2)
    {
        for(int j=4999;j<5999;j++);
        if(v1.x != v2.x)
            return v1.x < v2.x;
        else
            return v1.y < v2.y;
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    float* x;
    float* y;
    int n1;
    int n2;
    float a;
    float b;
    lineSegment** segments;
    MainWindow(QWidget *parent = nullptr,float* x = nullptr, float* y = nullptr,int n1 = 0,int n2 = 0, lineSegment** segments = nullptr, float a = 0, float b = 0);
    ~MainWindow();
    virtual void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
};






#endif // MAINWINDOW_H
