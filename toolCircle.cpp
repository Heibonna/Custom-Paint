#include "toolCircle.h"

toolCircle::toolCircle(mainWindow* w)
            :tools(w)
{}

void toolCircle::draw(){
    int x, y;
    double r = sqrt(pow(*x1-*x0, 2.0) + pow(*y1-*y0, 2.0));

    for(x = 0; x < r; x++){
        y = int(sqrt(pow(r, 2.0) - pow(x, 2.0)));
        w->paintPixels(*x0 + x, *y0 + y);
        w->paintPixels(*x0 - x, *y0 + y);
        w->paintPixels(*x0 + x, *y0 - y);
        w->paintPixels(*x0 - x, *y0 - y);
        w->paintPixels(*x0 + y, *y0 + x);
        w->paintPixels(*x0 + y, *y0 - x);
        w->paintPixels(*x0 - y, *y0 + x);
        w->paintPixels(*x0 - y, *y0 - x);
   }
}
