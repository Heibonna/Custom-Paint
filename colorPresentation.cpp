#include "colorPresentation.h"

colorPresentation::colorPresentation(mainWindow* w, int height, int width)
    :w(w), sliderNumber(0), value(0), WindowHeight(height), WindowWidth(width)
{}

void colorPresentation::present(int sliderNumber, int value){
    this->sliderNumber = sliderNumber;
    this->value = value;
    double r,b,g,h,s,v;

    switch(sliderNumber){
    case 1:
        b = 255;
        r = value*1.0;
        for(int i=0; i<WindowHeight; i++){
            g = 0;
            for(int j=0; j<WindowWidth; j++){
                w->paintPixels(j, i, {(int)round(r),(int)round(g),(int)round(b),255});
                g += 1.0*255/WindowWidth;
            }
            b -= 1.0*255/WindowHeight;
        }
        break;
    case 2:
        g = value*1.0;
        b = 255;
        for(int i=0; i<WindowHeight; i++){
            r = 0;
            for(int j=0; j<WindowWidth; j++){
                w->paintPixels(j, i, {(int)round(r),(int)round(g),(int)round(b),255});
                r += 1.0*255/WindowWidth;
            }
            b -= 1.0*255/WindowHeight;
        }
        break;
    case 3:
        b = value*1.0;
        r = 255;
        for(int i=0; i<WindowHeight; i++){
            g = 0;
            for(int j=0; j<WindowWidth; j++){
                w->paintPixels(j, i, {(int)round(r),(int)round(g),(int)round(b),255});
                g += 1.0*255/WindowWidth;
            }
            r -= 1.0*255/WindowHeight;
        }
        break;
    case 4:
        h = value*1.0;
        s = 1;
        for(int i=0; i<WindowHeight; i++){
            v = 0;
            for(int j=0; j<WindowWidth; j++){
                w->paintPixels(j, i, hsvToRGB(h,s,v,255));
                v += 1.0*1/WindowWidth;
            }
            s -= 1.0*1/WindowHeight;
        }
        break;
    case 5:
        s = value*1.0/360;
        v = 1;
        for(int i=0; i<WindowHeight; i++){
            h = 360;
            for(int j=0; j<WindowWidth; j++){
                w->paintPixels(j, i, hsvToRGB(h,s,v,255));
                h -= 1.0*360/WindowWidth;
            }
            v -= 1.0*1/WindowHeight;
        }
        break;
    case 6:
        s = 1;
        v = value*1.0/360;
        for(int i=0; i<WindowHeight; i++){
            h = 360;
            for(int j=0; j<WindowWidth; j++){
                w->paintPixels(j, i, hsvToRGB(h,s,v,255));
                h -= 1.0*360/WindowWidth;
            }
            s -= 1.0*1/WindowHeight;
        }
        break;
    }
}

Color colorPresentation::hsvToRGB(double h, double s, double v,int alpha){
    Color rgb;
    double c = v*s;
    double m = v - c;
    double h2 = h/60;
    int x = (int)round(255*((c*(1 - abs(fmod(h2, 2) - 1)) +m)));

    if(h2 >= 0 && h2 <= 6){
        c = round(255*(c+m));
        m = round(255*m);
        if(h2 <= 1)
            rgb = Color((int)c,x,(int)m,alpha);
        else if(h2 <= 2)
            rgb = Color(x,(int)c,(int)m,alpha);
        else if(h2 <= 3)
            rgb = Color((int)m,(int)c,x,alpha);
        else if(h2 <= 4)
            rgb = Color((int)m,x,(int)c,alpha);
        else if(h2 <= 5)
            rgb = Color(x,(int)m,(int)c,alpha);
        else if(h2 <= 6)
            rgb = Color((int)c,(int)m,x,alpha);
    }
    else
        rgb = Color((int)m,(int)m,(int)m,alpha);

    return rgb;
}

