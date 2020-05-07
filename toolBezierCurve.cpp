#include "toolBezierCurve.h"


toolBezierCurve::toolBezierCurve(mainWindow* w)
                :tools(w)
{
    interface = false;
    current_adding = -1;
}


void toolBezierCurve::draw(){
    for(unsigned long i = 0; i < control_points.size(); i++)
            if(control_points[i].size() >0)
                draw(control_points[i]);
}


void toolBezierCurve::draw(std::vector<std::pair<int,int>> curve){
    std::pair<int,int> p0, p1;
    double t;
    while(curve.size()%3-1 != 0)
        curve.pop_back();

    if(curve.size()-1 == 0)
        return;

    p0 = {0, 0};
    p1 = {0, 0};


    for(unsigned long j = 0; j+3 < curve.size(); j += 3){
        for(int i = 0;i <= 60; i++){
            t = i/60.0;

            if(p0.first != 0 && p0.second != 0){
                p1.swap(p0);
                p0.first = round(pow(1.0-t,3.0)*curve[j].first + 3*pow(1.0-t,2.0)*curve[j+1].first*t + 3*(1.0-t)*curve[j+2].first*t*t + curve[j+3].first*t*t*t);
                p0.second = round(pow(1.0-t,3.0)*curve[j].second + 3*pow(1.0-t,2.0)*curve[j+1].second*t + 3*(1.0-t)*curve[j+2].second*t*t + curve[j+3].second*t*t*t);
                w->Line->draw(p0, p1);
            }
            else{
                p0.first = round(pow(1.0-t,3.0)*curve[j].first + 3*pow(1.0-t,2.0)*curve[j+1].first*t + 3*(1.0-t)*curve[j+2].first*t*t + curve[j+3].first*t*t*t);
                p0.second = round(pow(1.0-t,3.0)*curve[j].second + 3*pow(1.0-t,2.0)*curve[j+1].second*t + 3*(1.0-t)*curve[j+2].second*t*t + curve[j+3].second*t*t*t);
            }
        }
    }
}

void toolBezierCurve::removeBezier(unsigned long i){
    Color colortmp = w->primaryColor;
    w->primaryColor = w->secondaryColor;
    draw(control_points[i]);
    w->primaryColor = colortmp;

    if(w->isPressed){
        w->imgCopy = *(w->img);
    }
}

void toolBezierCurve::addControlPoint(){
    if(control_points.size() != 0 && current_adding == -1){
        for(unsigned long  i=0; i < control_points.size(); i++){
            if(control_points[i].size() != 0){
                if(abs(control_points[i].back().first - *x0) <= 5 && abs(control_points[i].back().second - *y0) <= 5){
                    current_adding = i;
                    return;
                }
            }
        }
    }
    else if(control_points.size() != 0){
        control_points[current_adding].push_back({*x1, *y1});
        draw(control_points[current_adding]);
        return;
    }

    control_points.back().push_back({*x1, *y1});
    draw(control_points.back());

}


void toolBezierCurve::modifyBezier(){
    if(control_points.size() == 0)
        return;

    Interface(false);

    for(unsigned long  i=0; i < control_points.size(); i++){
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].first - *x0) <= 5 && abs(control_points[i][j].second - *y0) <= 5){
                removeBezier(i);
                control_points[i][j].first = *x1;
                control_points[i][j].second = *y1;

                draw();
                Interface(true);

                *x0 = control_points[i][j].first;
                *y0 = control_points[i][j].second;

                return;
            }
        }
    }
    Interface(true);
}

void toolBezierCurve::deleteBezier(){
    for(unsigned long  i=0; i < control_points.size(); i++){
        if(control_points[i].size() == 0)
            continue;
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].first - *x0) <= 5 && abs(control_points[i][j].second - *y0) <= 5){
                removeBezier(i);
                if(control_points[i].size() == 1){
                    control_points[i].clear();
                    return;
                }
                else{
                    for(unsigned long  k=j; k < control_points[i].size()-1; k++)
                        control_points[i][k] = control_points[i][k+1];
                    control_points[i].pop_back();
                    draw(control_points[i]);
                    return;
                }
            }
        }
    }
}
