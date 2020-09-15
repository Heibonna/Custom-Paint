#include "toolFulfill.h"
#include <stack>
#include <typeinfo>

toolFulfill::toolFulfill(mainWindow* w)
    :tools(w)
{
   oldColor = "white";
   img = new unsigned char(sizeof (w->img->bits()));
}

Color toolFulfill::getColor(int x, int y){
    Color pixelColor;

    pixelColor.blue = img[w->szer*4*y + 4*x];
    pixelColor.green = img[w->szer*4*y + 4*x + 1];
    pixelColor.red = img[w->szer*4*y + 4*x + 2];
    pixelColor.alpha = img[w->szer*4*y + 4*x + 3];

    return pixelColor;
}

void toolFulfill::draw(Point P1, unsigned char* bits){
    img = bits;
    int x = P1.x, y = P1.y;

    oldColor = getColor(x, y);

    floodFill(x, y);
}

void toolFulfill::floodFill(int x, int y){
    std::stack<std::pair<int,int>> stack;

    if(getColor(x,y) != oldColor || oldColor == w->primaryColor) return;

    stack.push({x,y});

    while(stack.size() > 0){
        x = stack.top().first;
        y = stack.top().second;
        stack.pop();

        if(getColor(x,y) != oldColor){
            continue;
        }

        int x1 = x, x2 = x;
        if(x1 > 0)
             while(getColor(x1-1, y) == oldColor && x1 > 0)
                 x1--;
        if(x2 < w->szer -1)
            while(getColor(x2+1,y) == oldColor && x2 < w->szer - 1)
                x2++;
         for(int i = x1; i <= x2; i++){
             w->paintPixels(i, y);

             if(y < w->wys -1)
                 if(getColor(i,y+1) == oldColor)
                     stack.push({i, y+1});
             if(y > 0)
                 if(getColor(i,y-1) == oldColor)
                     stack.push({i, y-1});
         }
    }
    return;
}
