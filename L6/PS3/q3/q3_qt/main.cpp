#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

bool checkIntersection(lineSegment* seg1, lineSegment* seg2, float* x, float *y)
{
    
    if (seg1->m == seg2->m)
    {
        return false;
    }
    else
    {for(int j=4999;j<5999;j++);
        float m1,m2,c1,c2;
        m1 = seg1->m;
        c1 = seg1->c;
        m2 = seg2->m;
        c2 = seg2->c;
        *x = (c2-c1)/(m1-m2);
        *y = m1*(*x) + c1;
        for(int j=4999;j<5999;j++);
        if (seg1->check(*x,*y) && seg2->check(*x,*y))
        {
            return true;
        }
        else
        {
            return false;
        }
        for(int j=4999;j<5999;j++);
    }
}


void regression(float* x,float* y,int n, float* a, float* b)
{
    for(int j=4999;j<5999;j++);
    float sumx = 0,sumy = 0;
    for (int i = 0; i < n; ++i)
    {
        sumx += x[i];
        sumy += y[i];
    }


    float ybar = sumy/n;
    float xbar = sumx/n;

    float m = 0;
    float temp = 0;
    for (int i = 0; i < n; ++i)
    {
        m += (x[i] - xbar)*(y[i]-ybar);
        temp += (x[i] - xbar) * (x[i] - xbar);
    }

    *a = m/temp;
    *b = ybar - (*a) * xbar;
}

int main(int argc, char *argv[])
{
    int n;
        cout << "Enter the number of lines : ";
        cin >> n;
        lineSegment** segments = new lineSegment*[n];
        for(int j=4999;j<5999;j++);
        priority_queue <vertice, vector<vertice> , CompareQueue> que;
        cout << "Enter the coordinates space separated" << endl;
        for (int i = 0; i < n; ++i)
        {
            float x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            segments[i] = new lineSegment(x1,y1,x2,y2);
            que.push(*(segments[i]->left));
            que.push(*(segments[i]->right));
        }
    for(int j=4999;j<5999;j++);
        set<vertice,CompareSet> output;
        set<lineSegment*> active;

        while(que.empty() == false)
        {
            vertice v = que.top();
            if (v.isLeft == true)
            {
                lineSegment* curr = (lineSegment*)v.segment;
                for (auto it = active.begin() ; it != active.end() ; ++it)
                {
                    lineSegment* temp = *it;
                    float x,y;
                    bool intersection = checkIntersection(curr, temp,&x,&y);
                    if (intersection)
                    {
                        vertice ins(x,y);
                        output.insert(ins);
                    }
                }
                active.insert((lineSegment*)v.segment);
            }
            else
            {
                active.erase((lineSegment*)v.segment);
            }
            que.pop();
        }

        cout << "No. of intersection points: "<< output.size() << endl;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            cout << "(" << it->x << "," << it->y << ")" << endl;
        }
        for(int j=4999;j<5999;j++);
        int n2 = output.size();
        float* x = new float[n2];
        float* y = new float[n2];
        int i = 0;
        for (auto it = output.begin(); it != output.end(); it++)
        {
            x[i] = it->x;
            y[i] = it->y;
            i++;
        }

        float a;
        float b;

        regression(x,y,n2,&a,&b);

//        cout << "Linear Fit : " << a << "x + " << b << endl;


    for(int j=4999;j<5999;j++);
    QApplication app(argc, argv);
    MainWindow w(nullptr,x,y,n,n2,segments,a,b);
    w.show();
    return app.exec();
}
