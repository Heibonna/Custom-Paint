#include "toolBezierCurve.h"


toolBezierCurve::toolBezierCurve(mainWindow* w)
                :tools(w)
{
    interface = false;
    current_adding = -1;
    currentMoving = {-1, -1};
    isMoving = false;
}


void toolBezierCurve::draw(){
    for(unsigned long i = 0; i < control_points.size(); i++)
            if(control_points[i].size() >0)
                draw(control_points[i]);
}


void toolBezierCurve::draw(std::vector<Point> curve){
    Point p0, p1;
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

            if(p0.x != 0 && p0.y != 0){
                p1.swap(p0);
                p0.x = round(pow(1.0-t,3.0)*curve[j].x + 3*pow(1.0-t,2.0)*curve[j+1].x*t + 3*(1.0-t)*curve[j+2].x*t*t + curve[j+3].x*t*t*t);
                p0.y = round(pow(1.0-t,3.0)*curve[j].y + 3*pow(1.0-t,2.0)*curve[j+1].y*t + 3*(1.0-t)*curve[j+2].y*t*t + curve[j+3].y*t*t*t);
                w->Line->draw(p0, p1);
            }
            else{
                p0.x = round(pow(1.0-t,3.0)*curve[j].x + 3*pow(1.0-t,2.0)*curve[j+1].x*t + 3*(1.0-t)*curve[j+2].x*t*t + curve[j+3].x*t*t*t);
                p0.y = round(pow(1.0-t,3.0)*curve[j].y + 3*pow(1.0-t,2.0)*curve[j+1].y*t + 3*(1.0-t)*curve[j+2].y*t*t + curve[j+3].y*t*t*t);
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

void toolBezierCurve::addControlPoint(Point P0, Point P1){
    Interface(false);

    if(control_points.size() != 0 && current_adding == -1){
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
        control_points[current_adding].push_back(P1);
        draw(control_points[current_adding]);
        Interface(true);
        return;
    }

    control_points.back().push_back(P1);
    draw(control_points.back());
    Interface(true);
}


void toolBezierCurve::modifyBezier(Point P0, Point P1, bool isPressed){
    if(control_points.size() == 0)
        return;

    Interface(false);

    if(isMoving){
        removeBezier(currentMoving.x);
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
        isMoving = false;
        currentMoving = {-1, -1};
        for(unsigned long  i=0; i < control_points.size(); i++){
            for(unsigned long  j=0; j < control_points[i].size(); j++){
                if((abs(control_points[i][j].x - P0.x) <= 5 && abs(control_points[i][j].y - P0.y) <= 5)){
                    removeBezier(i);
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

                    return;
                }
            }
        }
    }
    Interface(true);
}

void toolBezierCurve::deleteBezier(Point P0){
    Interface(false);
    for(unsigned long  i=0; i < control_points.size(); i++){
        if(control_points[i].size() == 0)
            continue;
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].x - P0.x) <= 5 && abs(control_points[i][j].y - P0.y) <= 5){
                removeBezier(i);
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
}
