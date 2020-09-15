#ifndef TOOLS_H
#define TOOLS_H

#include <QImage>
#include <QMouseEvent>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include "mainWindow.h"

class tools{
friend class mainWindow;
protected:
    mainWindow* w;
    int *mode;
public:
    tools(mainWindow* w);
};

#endif // TOOLS_H
