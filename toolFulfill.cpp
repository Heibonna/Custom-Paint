#include "toolFulfill.h"
#include <stack>

toolFulfill::toolFulfill(mainWindow* w)
    :tools(w)
{
   oldColor = "white";
   img = new unsigned char(sizeof (w->img->bits()));
}

void toolFulfill::Interface(bool){};

Color toolFulfill::getColor(int x, int y){
    Color pixelColor;

    pixelColor.blue = img[w->szer*4*y + 4*x];
    pixelColor.green = img[w->szer*4*y + 4*x + 1];
    pixelColor.red = img[w->szer*4*y + 4*x + 2];
    pixelColor.alpha = img[w->szer*4*y + 4*x + 3];

    return pixelColor;
}

void toolFulfill::draw(){
    draw(w->x1, w->y1, w->mode, w->img->bits());
}

void toolFulfill::draw(int x, int y, int mode, unsigned char* bits){
    img = bits;
    oldColor = getColor(x, y);

    if(mode == 10)
        floodFill(x, y);
    else if(mode == 11)
        scanLine(x, y);
}

void toolFulfill::floodFill(int x, int y){
    std::stack<std::pair<int,int>> stack;

    if(getColor(x,y) != oldColor) return;

    stack.push({x,y});

    while(stack.size() > 0){
        x = stack.top().first;
        y = stack.top().second;
        stack.pop();

        if(getColor(x,y) == oldColor){
            int x1 = x, x2 = x;
            while(getColor(x1, y) == oldColor && x1 > 0){
                x1--;
            }
            while(getColor(x2,y) == oldColor && x2 < w->szer){
                x2++;
            }
            for(int i = x1; i < x2; i++){
                std::cout << i << std::endl;
                w->paintPixels(i, y);
            }
            for(int i = x1; i < x2; i++){
                if(getColor(i,y+1) == oldColor && y <= w->wys)
                    stack.push({i, y+1});
                if(getColor(i,y-1) == oldColor && y >= 0)
                    stack.push({i, y-1});
            }
        }
    }
    return;
}

void toolFulfill::scanLine(int, int){

}
