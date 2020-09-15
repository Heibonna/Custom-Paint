#include "toolFulfilledPolygon.h"
#include "toolLine.h"

toolFulfilledPolygon::toolFulfilledPolygon(mainWindow* w)
                        :tools(w)
{
}

void toolFulfilledPolygon::draw(Point P){
    points.push_back(P);

    if(points.size() < 2)
        w->paintPixels(P.x, P.y);
    else{
        if(points.back().inRange(points.front())){
            points.pop_back();
            w->Line->draw(points.front(), points.back());
            scanLine();
            points.clear();
        }
        else
            w->Line->draw(points[points.size()-2], P);
    }
}

void toolFulfilledPolygon::scanLine(){
    std::vector<ET> edgeTable;
    std::vector<int> xTable;
    for(unsigned long i = 0; i < points.size()-1; i++)
        if(points[i].y != points[i+1].y)
            edgeTable.push_back(ET(points[i], points[i+1]));

    if(points[0].y != points.back().y){
        edgeTable.push_back(ET(points[points.size()-1], points[0]));
    }

    if(edgeTable.size() == 0)
        return;

    int y = edgeTable[0].Ymin;
    for(unsigned long i = 1; i < edgeTable.size(); i++)
        if(y > edgeTable[i].Ymin)
            y = edgeTable[i].Ymin;

    do{
        for(unsigned long i = 0; i < edgeTable.size(); i++) {
            if(edgeTable[i].Ymin <= y && edgeTable[i].Ymax > y)
                xTable.push_back(int(round(1.0*edgeTable[i].P0.x + (y - 1.0*edgeTable[i].P0.y) * edgeTable[i].m)));
            if(edgeTable[i].Ymax <= y){
                edgeTable.erase(edgeTable.begin() + i);
                if(i != edgeTable.size()-1)
                    i--;
            }
        }
        std::sort(xTable.begin(), xTable.end());
        for(unsigned long i = 0; i < xTable.size(); i += 2)
            if(i < xTable.size()-1)
                w->Line->draw({xTable[i],y}, {xTable[i+1], y});

        xTable.clear();
        y++;
    }
    while(edgeTable.size() > 0);
}
