#include "layer.h"

layer::layer(QString path)
{
    image = QImage(path);
    alpha = 0;
    mode = normal;

}

layer::layer(){}

void layer::getImage(int number, layer* tab, QImage* img){
    Color tmp;
    unsigned char* ptr = img->bits();
    int width = img->width(), height = img->height(), result;
    double alpha;

    for(int i = number-1; i >= 0; i--){
        alpha = tab[i].alpha;
        for(int j = 0; j < width * height * 4; j++){
            if(tab[i].mode == normal)
                result = tab[i].image.bits()[j];
            else if(tab[i].mode == multiple)
                result = tab[i].image.bits()[j] * ptr[j] >> 8;
            else if(tab[i].mode == darken)
                result = std::min(tab[i].image.bits()[j], ptr[j]);
            else if(tab[i].mode == lighten)
                result = std::max(tab[i].image.bits()[j], ptr[j]);
            else if(tab[i].mode == difference)
                result = std::abs(tab[i].image.bits()[j] - ptr[j]);
            else if(tab[i].mode == additive)
                result = std::min(tab[i].image.bits()[j] + ptr[j], 255);
            else if(tab[i].mode == substractive)
                result = std::max(tab[i].image.bits()[j] + ptr[j], 0);

            ptr[j] = (int)round(alpha * result + (1-alpha) * ptr[j]);
        }
    }
}

void layer::updateLayer(int alpha, blending mode){
    this -> alpha = 1.0*alpha/100;
    this -> mode = mode;
}
