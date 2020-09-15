#include "toolLine.h"

toolLine::toolLine(mainWindow* w)
         :tools(w)
{}

void toolLine::draw(Point P0, Point P1){
    float a, b;
    int x, y;

    if(P0.x == P1.x){
        for(int y = P0.y; y != P1.y; y += (P0.y < P1.y ? 1 : -1))
            w->paintPixels(P0.x, y);
    }
    else{
        a = float(P0.y - P1.y)/(P0.x - P1.x);
        b = P0.y - a * P0.x;

        if(a <= 1 && a >= -1){
            for(int x = P0.x; x != P1.x; x += (P0.x < P1.x ? 1 : -1)){
                y = a*x+b;
                w->paintPixels(x, y);
            }
            x = P1.x;
            y = a*x+b;
            w->paintPixels(x, y);
        }
        else{
            for(int y = P0.y; y != P1.y; y += (P0.y < P1.y ? 1 : -1)){
                x = (y-b)/a;
                w->paintPixels(x, y);
            }
            y = P1.y;
            x = (y-b)/a;
            w->paintPixels(x, y);
        }
    }
}
