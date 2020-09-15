#ifndef TOOLFULFILL_H
#define TOOLFULFILL_H
#include "tools.h"

class toolFulfill :tools
{
private:
    Color oldColor;
    unsigned char* img;
public:
    toolFulfill(mainWindow *w);

    void draw(Point P1, unsigned char* bits);

    Color getColor(int x, int y);
    void floodFill(int x, int y);
};

#endif // TOOLFULFILL_H
