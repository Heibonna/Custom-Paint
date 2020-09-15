#ifndef TOOLFULFILLEDPOLYGON_H
#define TOOLFULFILLEDPOLYGON_H

#include "tools.h"

class toolFulfilledPolygon :tools
{
public:
    toolFulfilledPolygon(mainWindow*);

    std::vector<Point> points;

    void draw(Point P);
    void scanLine();
    void sortByYmin(std::vector<std::pair<Point,Point>>);
};

#endif // TOOLFULFILLEDPOLYGON_H
