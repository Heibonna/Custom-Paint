#ifndef MORFOLOGY_H
#define MORFOLOGY_H

#include "structures.h"
#include <QImage>

class morfology
{
public:
    static void draw(mm tmp,kernel morfologyType,Color primaryColor,Color secondaryColor,QImage* img);

private:
    morfology();
};

#endif // MORFOLOGY_H
