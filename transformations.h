#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include "tools.h"
#include "structures.h"
#include <string>

class transformations
{
private:
    QImage* srcPicture;
    QImage* picture;
    QImage* img;

    Matrix mainMi;
    Matrix translationMi;
    Matrix scallingMi;
    Matrix rotatingMi;
    Matrix shearingMi;

    int rotate, scallX, scallY;

    void draw();
    void paintPoint(QImage* img, Matrix toPaint, QImage* colors, Point from);
public:
    transformations(std::string src, QImage* img);
    void reset();
    void loadImg();
    void translocation(int dx, int dy);
    void scalling(int dx, int dy);
    void rotating(int alpha);
    void shearing(int sx, int sy);
    double interpolation(int x, int y, double dx);
};

#endif // TRANSFORMATIONS_H
