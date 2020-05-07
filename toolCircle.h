#ifndef TOOLCIRCLE_H
#define TOOLCIRCLE_H

#include "tools.h"

class toolCircle:tools
{
friend class mainWindow;

private:
public:
    toolCircle(mainWindow*);

    void draw() override;
    void Interface(bool active) override;
};

#endif // TOOLCIRCLE_H
