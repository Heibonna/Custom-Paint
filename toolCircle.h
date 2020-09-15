#ifndef TOOLCIRCLE_H
#define TOOLCIRCLE_H

#include "tools.h"

class toolCircle:tools
{
friend class mainWindow;

private:
public:
    toolCircle(mainWindow*);

    void draw(Point P0, Point P1);
};

#endif // TOOLCIRCLE_H
