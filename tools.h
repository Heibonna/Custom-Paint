#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QMouseEvent>
#include <iostream>
#include <vector>
#include <cmath>
#include "mainWindow.h"

class tools{
friend class mainWindow;
protected:
    mainWindow* w;
    int *x0, *y0, *x1, *y1;
    int *mode;
public:
    tools(mainWindow* w);

    virtual void draw() = 0;
    virtual void Interface(bool active) = 0;
};

#endif // TOOLS_H
