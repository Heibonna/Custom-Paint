#include "toolBSpline.h"

toolBSpline::toolBSpline(mainWindow* w)
                :tools(w)
{
    interface = false;
    current_adding = -1;
}


void toolBSpline::draw(){
    for(unsigned long i = 0; i < control_points.size(); i++)
            if(control_points[i].size() >0)
                draw(control_points[i]);
}


void toolBSpline::draw(std::vector<std::pair<int,int>> curve){
    std::pair<int,int> p0, p1;
    double t;
    if(curve.size() < 4)
        return;

    p0 = {0, 0};
    p1 = {0, 0};

    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        p1.swap(p0);
        if(p0.first != 0 && p0.second != 0){
            p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].first + (3*pow(t,3.0)-6*t*t+4)*curve[0].first + (1+3*t+3*t*t-3*t*t*t)*curve[0].first + t*t*t*curve[1].first)/6);
            p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].second + (3*pow(t,3.0)-6*t*t+4)*curve[0].second + (1+3*t+3*t*t-3*t*t*t)*curve[0].second + t*t*t*curve[1].second)/6);
            w->Line->draw(p0, p1);
        }
        else{
            p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].first + (3*pow(t,3.0)-6*t*t+4)*curve[0].first + (1+3*t+3*t*t-3*t*t*t)*curve[0].first + t*t*t*curve[1].first)/6);
            p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].second + (3*pow(t,3.0)-6*t*t+4)*curve[0].second + (1+3*t+3*t*t-3*t*t*t)*curve[0].second + t*t*t*curve[1].second)/6);
        }
    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        p1.swap(p0);
        p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].first + (3*pow(t,3.0)-6*t*t+4)*curve[0].first + (1+3*t+3*t*t-3*t*t*t)*curve[1].first + t*t*t*curve[2].first)/6);
        p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].second + (3*pow(t,3.0)-6*t*t+4)*curve[0].second + (1+3*t+3*t*t-3*t*t*t)*curve[1].second + t*t*t*curve[2].second)/6);
        w->Line->draw(p0, p1);

    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        p1.swap(p0);
        p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].first + (3*pow(t,3.0)-6*t*t+4)*curve[1].first + (1+3*t+3*t*t-3*t*t*t)*curve[2].first + t*t*t*curve[3].first)/6);
        p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].second + (3*pow(t,3.0)-6*t*t+4)*curve[1].second + (1+3*t+3*t*t-3*t*t*t)*curve[2].second + t*t*t*curve[3].second)/6);
        w->Line->draw(p0, p1);

    }
    for(unsigned long j = 4; j < curve.size(); j++){
        for(int i = 0;i <= 20; i++){
            t = i/20.0;
            p1.swap(p0);
            p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[j-3].first + (3*pow(t,3.0)-6*t*t+4)*curve[j-2].first + (1+3*t+3*t*t-3*t*t*t)*curve[j-1].first + t*t*t*curve[j].first)/6);
            p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[j-3].second + (3*pow(t,3.0)-6*t*t+4)*curve[j-2].second + (1+3*t+3*t*t-3*t*t*t)*curve[j-1].second + t*t*t*curve[j].second)/6);
            w->Line->draw(p0, p1);
        }
    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        p1.swap(p0);
        p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-3].first + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-2].first + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].first + t*t*t*curve[curve.size()-1].first)/6);
        p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-3].second + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-2].second + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].second + t*t*t*curve[curve.size()-1].second)/6);
        w->Line->draw(p0, p1);
    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        p1.swap(p0);
        p0.first = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-2].first + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-1].first + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].first + t*t*t*curve[curve.size()-1].first)/6);
        p0.second = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-2].second + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-1].second + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].second + t*t*t*curve[curve.size()-1].second)/6);
        w->Line->draw(p0, p1);
    }
}

void toolBSpline::remove(unsigned long i){
    Color colortmp = w->primaryColor;
    w->primaryColor = w->secondaryColor;
    draw(control_points[i]);
    w->primaryColor = colortmp;

    if(w->isPressed){
        w->imgCopy = *(w->img);
    }
}

void toolBSpline::addControlPoint(){
    if(control_points.size() != 0 && current_adding == -1){
        remove(control_points.size()-1);
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
        remove(current_adding);
        draw(control_points[current_adding]);
        return;
    }

    control_points.back().push_back({*x1, *y1});
    draw(control_points.back());

}


void toolBSpline::modify(){
    if(control_points.size() == 0)
        return;

    Interface(false);

    for(unsigned long  i=0; i < control_points.size(); i++){
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].first - *x0) <= 5 && abs(control_points[i][j].second - *y0) <= 5){
                remove(i);
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

void toolBSpline::del(){
    for(unsigned long  i=0; i < control_points.size(); i++){
        if(control_points[i].size() == 0)
            continue;
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].first - *x0) <= 5 && abs(control_points[i][j].second - *y0) <= 5){
                remove(i);
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

