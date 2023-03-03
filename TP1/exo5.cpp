#include "tp1.h"
#include <QApplication>
#include <time.h>

// #include <iostream>
// using namespace std;

int isMandelbrot(Point z, int n, Point point){
    // recursiv Mandelbrot

    // check n
    if (n == 0) {
        return 0;
    }
    else if (sqrt(z.x*z.x + z.y*z.y) > 2) {
        return 1;
    }
    else {
        Point zn;
        zn.x = z.x*z.x + z.y*z.y + point.x;
        zn.y = 2*z.x*z.y + point.y;
        return isMandelbrot(zn,n-1,point);
    }

    // check length of z
    // if Mandelbrot, return 1 or n (check the difference)
    // otherwise, process the square of z and recall
    // isMandebrot

    // (x + iy)^2 = (x^2 - y^2) + 2ixy
    return 0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MandelbrotWindow(isMandelbrot);
    w->show();

    a.exec();


}



