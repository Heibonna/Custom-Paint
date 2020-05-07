#ifndef TOOLLINE_H
#define TOOLLINE_H

#include "tools.h"

class toolLine:tools
{
friend class mainWindow;
public:
    toolLine(mainWindow*);

    void draw(std::pair<int,int>,std::pair<int,int>);
    void draw() override;
    void Interface(bool active) override;
};

#endif // TOOLLINE_H
