#include "toolLine.h"

toolLine::toolLine(mainWindow* w)
         :tools(w)
{}

void toolLine::draw(std::pair<int,int> p1, std::pair<int,int> p2){
    float a, b;
    if(p1.first == p2.first){
        for(int y = p1.second; y != p2.second; y += (p1.second < p2.second ? 1 : -1))
            w->paintPixels(p1.first, y);
    }
    else{
        a = float(p1.second - p2.second)/(p1.first - p2.first);
        b = p1.second - a * p1.first;

        if(a <= 1 && a >= -1){
            for(int x = p1.first; x != p2.first; x += (p1.first < p2.first ? 1 : -1)){
                int y = a*x+b;
                w->paintPixels(x, y);
            }
        }
        else{
            for(int y = p1.second; y != p2.second; y += (p1.second < p2.second ? 1 : -1)){
                int x = (y-b)/a;
                w->paintPixels(x, y);
            }
        }
    }
}


void toolLine::draw(){
    draw({*x0,*y0},{*x1,*y1});
}
