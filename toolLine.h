#ifndef TOOLLINE_H
#define TOOLLINE_H

#include "tools.h"

class toolLine:tools
{
friend class mainWindow;
public:
    toolLine(mainWindow*);

    void draw(Point P0, Point P1);
};

#endif // TOOLLINE_H
