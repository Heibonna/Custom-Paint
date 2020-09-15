#ifndef TOOLPOLYGON_H
#define TOOLPOLYGON_H

#include "tools.h"
#include "toolLine.h"

class toolPolygon:tools
{
friend class mainWindow;
public:
    toolPolygon(mainWindow*);

    void draw(Point P0,Point P1);
};

#endif // TOOLPOLYGON_H
