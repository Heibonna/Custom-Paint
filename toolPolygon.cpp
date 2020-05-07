#include "toolPolygon.h"

toolPolygon::toolPolygon(mainWindow* w)
            :tools(w)
{}

void toolPolygon::draw(){
    double x, y;
    std::pair<double, double> copy[2] = {{*x0,*y0}, {*x1,*y1}};
    int polygonVertices = w->polygonVertices;
    double alpha = 2 * M_PI/polygonVertices;
    double a, b;
    std::vector<std::pair<double,double>> points;


    a = double(*x1>=*x0 ? *x1-*x0 : *x0-*x1);
    b = double(*y1>=*y0 ? *y1-*y0 : *y0-*y1);

    for(double beta = alpha; beta <= 2*M_PI; beta += 2 * M_PI/polygonVertices){
        y = (b * sin(beta));
        x = (a * cos(beta));

        points.push_back({*x0+x, *y0+y});

    }
    for(int i = 0; i < polygonVertices-1; i++){
        *x0 = points[i].first;
        *y0 = points[i].second;
        *x1 = points[i+1].first;
        *y1 = points[i+1].second;

        w->Line->draw();
    }
    *x0 = points[polygonVertices-1].first;
    *y0 = points[polygonVertices-1].second;
    *x1 = points[0].first;
    *y1 = points[0].second;
    w->Line->draw();

    //std::cout << "x0,x1,y0,y1,alhpa,a,b(" << x0 << "," << x1 << "," << y0 << "," << y1 << "," << alpha << "," << a << "," << b << ")"<< std::endl;

    *x0 = copy[0].first;
    *y0 = copy[0].second;
    *x1 = copy[1].first;
    *y1 = copy[1].second;
}
