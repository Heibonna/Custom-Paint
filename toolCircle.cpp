#include "toolCircle.h"

toolCircle::toolCircle(mainWindow* w)
            :tools(w)
{}

void toolCircle::draw(Point P0, Point P1){
    int x, y;
    double r = sqrt(pow(P1.x-P0.x, 2.0) + pow(P1.y-P0.y, 2.0));

    for(x = 0; x < r; x++){
        y = int(sqrt(pow(r, 2.0) - pow(x, 2.0)));
        w->paintPixels(P0.x + x, P0.y + y);
        w->paintPixels(P0.x - x, P0.y + y);
        w->paintPixels(P0.x + x, P0.y - y);
        w->paintPixels(P0.x - x, P0.y - y);
        w->paintPixels(P0.x + y, P0.y + x);
        w->paintPixels(P0.x + y, P0.y - x);
        w->paintPixels(P0.x - y, P0.y + x);
        w->paintPixels(P0.x - y, P0.y - x);
   }
}
