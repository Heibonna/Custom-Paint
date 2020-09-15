
#include "toolPolygon.h"

toolPolygon::toolPolygon(mainWindow* w)
            :tools(w)
{}

void toolPolygon::draw(Point P0, Point P1){
    double x, y;
    std::pair<double, double> copy[2] = {{P0.x,P0.y}, {P1.x,P1.y}};
    int polygonVertices = w->polygonVertices;
    double alpha = 2 * M_PI/polygonVertices;
    double a, b;
    std::vector<std::pair<double,double>> points;


    a = double(P1.x>=P0.x ? P1.x-P0.x : P0.x-P1.x);
    b = double(P1.y>=P0.y ? P1.y-P0.y : P0.y-P1.y);

    for(double beta = alpha; beta <= 2*M_PI; beta += 2 * M_PI/polygonVertices){
        y = (b * sin(beta));
        x = (a * cos(beta));

        points.push_back({P0.x+x, P0.y+y});

    }
    for(int i = 0; i < polygonVertices-1; i++){
        P0.x = points[i].first;
        P0.y = points[i].second;
        P1.x = points[i+1].first;
        P1.y = points[i+1].second;

        w->Line->draw(P0, P1);
    }
    P0.x = points[polygonVertices-1].first;
    P0.y = points[polygonVertices-1].second;
    P1.x = points[0].first;
    P1.y = points[0].second;
    w->Line->draw(P0, P1);

    P0.x = copy[0].first;
    P0.y = copy[0].second;
    P1.x = copy[1].first;
    P1.y = copy[1].second;
}
