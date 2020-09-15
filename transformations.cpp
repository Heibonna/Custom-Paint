#include "transformations.h"

transformations::transformations(std::string src, QImage* window)
    :img(window)
{
    this->picture = new QImage(window->width(), window->height(), QImage::Format_RGB32);
    this->srcPicture = new QImage(QString::fromStdString(src));
}

void transformations::reset(){
    *picture = srcPicture -> copy();

    loadImg();

    mainMi = *new Matrix();
    translationMi = *new Matrix();
    scallingMi = *new Matrix();
    shearingMi = *new Matrix();
    rotatingMi = *new Matrix();

    scallX = 500;
    scallY = 500;
    rotate = 0;
}

void transformations::loadImg(){
    int width = picture->width();
    int height = picture->height();

    for(int i=0; i < height;i++)
    for(int j=0; j < width; j++){
        img->bits()[img->width()*4*(i-1) + 4*j] = picture->bits()[picture->width()*4*i + 4*j];
        img->bits()[img->width()*4*(i-1) + 4*j + 1] = picture->bits()[picture->width()*4*i + 4*j + 1];
        img->bits()[img->width()*4*(i-1) + 4*j + 2] = picture->bits()[picture->width()*4*i + 4*j + 2];
        img->bits()[img->width()*4*(i-1) + 4*j + 3] = picture->bits()[picture->width()*4*i + 4*j + 3];

    }
}

void transformations::translocation(int dx, int dy){
    translationMi.fields[0][2] = -dx;
    translationMi.fields[1][2] = dy;

    draw();
}

void transformations::scalling(int dx, int dy){
    scallX = dx;
    scallY = dy;
    double Sx = 1.0*dx/500, Sy = 1.0*dy/500;
    double x0 = picture->width()/(1.0*2), y0 = picture->height()/(1.0*2);

    scallingMi.fields[0][0] = 1/Sx;
    scallingMi.fields[1][1] = 1/Sy;
    scallingMi.fields[2][2] = 1;
    scallingMi.fields[0][2] = x0 * (1 - 1/Sx);
    scallingMi.fields[1][2] = y0 * (1 - 1/Sy);

    draw();
}

void transformations::rotating(int alpha){
    rotate = alpha;
    int x0 = picture->width()/(1.0*2), y0 = picture->height()/(1.0*2) ;
    double radiany = alpha * M_PI/180;

    rotatingMi.fields[0][0] = cos(radiany);
    rotatingMi.fields[0][1] = -sin(radiany);
    rotatingMi.fields[1][0] = sin(radiany);
    rotatingMi.fields[1][1] = cos(radiany);
    rotatingMi.fields[2][2] = 1;
    rotatingMi.fields[0][2] = x0*(1 - cos(radiany)) + sin(radiany) * y0;
    rotatingMi.fields[1][2] = y0*(1 - cos(radiany)) - sin(radiany) * x0;

    draw();
}
void transformations::shearing(int dx, int dy){
    double sx = 1.0*dx/75;
    double sy = 1.0*dy/75;

    shearingMi.fields[0][1] = sy;
    shearingMi.fields[0][0] = 1+sx*sy;
    shearingMi.fields[1][1] = 1;
    shearingMi.fields[2][2] = 1;
    shearingMi.fields[1][0] = sx;
    shearingMi.fields[0][2] = -(img->width()/(1.0*2))*sx*sy - sy*(img->height()/(1.0*2));
    shearingMi.fields[1][2] = -(img->width()/(1.0*2))*sx;

    draw();
}

void transformations::draw(){
    double a,b;
    int x,y,xn,yn;
    unsigned char* ptr = img->bits();
    Matrix tmp;
    mainMi = rotatingMi * scallingMi * shearingMi * translationMi;

    for(int i=0; i < img->width();i++)
    for(int j=2; j < img->height()+2; j++){
        x = a = mainMi.fields[0][0] * i + mainMi.fields[0][1] * j + mainMi.fields[0][2];
        y = b = mainMi.fields[1][0] * i + mainMi.fields[1][1] * j + mainMi.fields[1][2];
        xn = x + 1;
        yn = y + 1;
        if(xn == img->height())
            xn--;
        if(yn == img->width())
            yn--;
        if(x >= 0 && y >= 0 && x <  img->height() && y < img->width()){
            a = a - x;
            b = b - y;
            ptr[img->width()*4*i + 4*j] = round(interpolation(interpolation(picture->bits()[img->width()*4*x + 4*y],
                                                              picture->bits()[img->width()*4*xn + 4*y],a),
                                                              interpolation(picture->bits()[img->width()*4*x + 4*yn],
                                                              picture->bits()[img->width()*4*xn + 4*yn],a),b));
            ptr[img->width()*4*i + 4*j + 1] = round(interpolation(interpolation(picture->bits()[img->width()*4*x + 4*y + 1],
                                                                  picture->bits()[img->width()*4*xn + 4*y + 1],a),
                                                                  interpolation(picture->bits()[img->width()*4*x + 4*yn + 1],
                                                                  picture->bits()[img->width()*4*xn + 4*yn + 1],a),b));
            ptr[img->width()*4*i + 4*j + 2] = round(interpolation(interpolation(picture->bits()[img->width()*4*x + 4*y + 2],
                                                                  picture->bits()[img->width()*4*xn + 4*y + 2],a),
                                                                  interpolation(picture->bits()[img->width()*4*x + 4*yn + 2],
                                                                  picture->bits()[img->width()*4*xn + 4*yn + 2],a),b));
            ptr[img->width()*4*i + 4*j + 3] = round(interpolation(interpolation(picture->bits()[img->width()*4*x + 4*y + 3],
                                                                  picture->bits()[img->width()*4*xn + 4*y + 3],a),
                                                                  interpolation(picture->bits()[img->width()*4*x + 4*yn + 3],
                                                                  picture->bits()[img->width()*4*xn + 4*yn + 3],a),b));
        }
    }
}
double transformations::interpolation(int x, int y, double dx){
    return (1-dx)*x+dx*y;
}
