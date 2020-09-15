#ifndef COLORPRESENTATION_H
#define COLORPRESENTATION_H
#include "tools.h"

class colorPresentation
{
private:
    mainWindow* w;
    int sliderNumber;
    int value;
    int WindowHeight;
    int WindowWidth;
public:
    colorPresentation(mainWindow* w, int height, int width);

    void present(int sliderNumber, int value);
    Color hsvToRGB(double h, double s, double v,int alpha);

};

#endif // COLORPRESENTATION_H
