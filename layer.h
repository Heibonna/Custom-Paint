#ifndef LAYER_H
#define LAYER_H
#include <QImage>
#include <QString>
#include "tools.h"

class layer
{
public:
    QImage image;
    double alpha;
    blending mode;
public:
    layer(QString path);
    layer();

    void updateLayer(int alpha, blending blendingMode);
    void getImage(int number, layer* tab, QImage* img);
};
#endif // LAYER_H
