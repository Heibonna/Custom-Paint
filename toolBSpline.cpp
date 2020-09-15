#include "toolBSpline.h"

toolBSpline::toolBSpline(mainWindow* w)
                :tools(w)
{
    interface = false;
    current_adding = -1;
    currentMoving = {-1, -1};
    isMoving = false;
}


void toolBSpline::draw(){
    for(unsigned long i = 0; i < control_points.size(); i++)
            if(control_points[i].size() >0)
                draw(control_points[i]);
}


void toolBSpline::draw(std::vector<Point> curve){
    Point P0, P1;
    double t;
    if(curve.size() < 4)
        return;

    P0 = {0, 0};
    P1 = {0, 0};

    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        P1.swap(P0);
        if(P0.x != 0 && P0.y != 0){
            P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].x + (3*pow(t,3.0)-6*t*t+4)*curve[0].x + (1+3*t+3*t*t-3*t*t*t)*curve[0].x + t*t*t*curve[1].x)/6);
            P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].y + (3*pow(t,3.0)-6*t*t+4)*curve[0].y + (1+3*t+3*t*t-3*t*t*t)*curve[0].y + t*t*t*curve[1].y)/6);
            w->Line->draw(P0, P1);
        }
        else{
            P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].x + (3*pow(t,3.0)-6*t*t+4)*curve[0].x + (1+3*t+3*t*t-3*t*t*t)*curve[0].x + t*t*t*curve[1].x)/6);
            P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].y + (3*pow(t,3.0)-6*t*t+4)*curve[0].y + (1+3*t+3*t*t-3*t*t*t)*curve[0].y + t*t*t*curve[1].y)/6);
        }
    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        P1.swap(P0);
        P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].x + (3*pow(t,3.0)-6*t*t+4)*curve[0].x + (1+3*t+3*t*t-3*t*t*t)*curve[1].x + t*t*t*curve[2].x)/6);
        P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].y + (3*pow(t,3.0)-6*t*t+4)*curve[0].y + (1+3*t+3*t*t-3*t*t*t)*curve[1].y + t*t*t*curve[2].y)/6);
        w->Line->draw(P0, P1);

    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        P1.swap(P0);
        P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].x + (3*pow(t,3.0)-6*t*t+4)*curve[1].x + (1+3*t+3*t*t-3*t*t*t)*curve[2].x + t*t*t*curve[3].x)/6);
        P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[0].y + (3*pow(t,3.0)-6*t*t+4)*curve[1].y + (1+3*t+3*t*t-3*t*t*t)*curve[2].y + t*t*t*curve[3].y)/6);
        w->Line->draw(P0, P1);

    }
    for(unsigned long j = 4; j < curve.size(); j++){
        for(int i = 0;i <= 20; i++){
            t = i/20.0;
            P1.swap(P0);
            P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[j-3].x + (3*pow(t,3.0)-6*t*t+4)*curve[j-2].x + (1+3*t+3*t*t-3*t*t*t)*curve[j-1].x + t*t*t*curve[j].x)/6);
            P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[j-3].y + (3*pow(t,3.0)-6*t*t+4)*curve[j-2].y + (1+3*t+3*t*t-3*t*t*t)*curve[j-1].y + t*t*t*curve[j].y)/6);
            w->Line->draw(P0, P1);
        }
    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        P1.swap(P0);
        P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-3].x + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-2].x + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].x + t*t*t*curve[curve.size()-1].x)/6);
        P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-3].y + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-2].y + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].y + t*t*t*curve[curve.size()-1].y)/6);
        w->Line->draw(P0, P1);
    }
    for(int i = 0;i <= 20; i++){
        t = i/20.0;
        P1.swap(P0);
        P0.x = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-2].x + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-1].x + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].x + t*t*t*curve[curve.size()-1].x)/6);
        P0.y = round(((pow(-t,3.0)+3*t*t-3*t+1)*curve[curve.size()-2].y + (3*pow(t,3.0)-6*t*t+4)*curve[curve.size()-1].y + (1+3*t+3*t*t-3*t*t*t)*curve[curve.size()-1].y + t*t*t*curve[curve.size()-1].y)/6);
        w->Line->draw(P0, P1);
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

void toolBSpline::addControlPoint(Point P0, Point P1){
    Interface(false);
    if(control_points.size() != 0 && current_adding == -1){
        remove(control_points.size()-1);
        for(unsigned long  i=0; i < control_points.size(); i++){
            if(control_points[i].size() != 0){
                if(abs(control_points[i].back().x - P0.x) <= 5 && abs(control_points[i].back().y - P0.y) <= 5){
                    current_adding = i;
                    Interface(true);
                    return;
                }
            }
        }
    }
    else if(control_points.size() != 0){
        control_points[current_adding].push_back({P1.x, P1.y});
        remove(current_adding);
        draw(control_points[current_adding]);
        Interface(true);
        return;
    }

    control_points.back().push_back({P1.x, P1.y});
    draw(control_points.back());
    Interface(true);
}


void toolBSpline::modify(Point P0, Point P1, bool isPressed){
    Interface(false);
    if(control_points.size() == 0)
        return;
    if(isMoving){
        remove(currentMoving.x);
        control_points[currentMoving.x][currentMoving.y].x = P1.x;
        control_points[currentMoving.x][currentMoving.y].y = P1.y;

        draw();

        if(isPressed)
            isMoving = true;
        else{
            isMoving = false;
            currentMoving = {-1, -1};
        }
    }
    else{
        for(unsigned long  i=0; i < control_points.size(); i++){
            for(unsigned long  j=0; j < control_points[i].size(); j++){
                if(abs(control_points[i][j].x - P0.x) <= 5 && abs(control_points[i][j].y - P0.y) <= 5){
                    remove(i);
                    control_points[i][j].x = P1.x;
                    control_points[i][j].y = P1.y;

                    draw();
                    Interface(true);

                    if(isPressed){
                        isMoving = true;
                        currentMoving = {(int)i,(int)j};
                    }
                    else{
                        isMoving = false;
                        currentMoving = {-1, -1};
                    }
                    Interface(true);
                    return;
                }
            }
        }
    }
    Interface(true);
}

void toolBSpline::del(Point P1){
    Interface(false);
    for(unsigned long  i=0; i < control_points.size(); i++){
        if(control_points[i].size() == 0)
            continue;
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].x - P1.x) <= 5 && abs(control_points[i][j].y - P1.y) <= 5){
                remove(i);
                if(control_points[i].size() == 1){
                    control_points[i].clear();
                    Interface(true);
                    return;
                }
                else{
                    for(unsigned long  k=j; k < control_points[i].size()-1; k++)
                        control_points[i][k] = control_points[i][k+1];
                    control_points[i].pop_back();
                    draw(control_points[i]);
                    Interface(true);
                    return;
                }
            }
        }
    }
    Interface(true);
}

