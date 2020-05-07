#ifndef TOOLPOLYGON_H
#define TOOLPOLYGON_H

#include "tools.h"
#include "toolLine.h"

class toolPolygon:tools
{
friend class mainWindow;
public:
    toolPolygon(mainWindow*);

    void draw() override;
    void Interface(bool active) override;
};

#endif // TOOLPOLYGON_H
