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

    void draw() override;
    void draw(int x,int y,int mode, unsigned char* bits);
    void Interface(bool active) override;

    Color getColor(int x, int y);
    void floodFill(int x, int y);
    void scanLine(int x, int y);
};

#endif // TOOLFULFILL_H
