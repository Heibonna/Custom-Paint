#include "toolBezierCurve.h"
#include "toolBSpline.h"
#include "toolLine.h"
#include "toolCircle.h"
#include "toolPolygon.h"

void toolBezierCurve::Interface(bool visible){
    interface = visible;

    if(visible){
        if((imgEditor).isNull())
            imgEditor = *(w->img);

        Color clr_tmp = w->primaryColor;
        unsigned long a = *x0, b = *x1, c = *y0, d = *y1;

        for(unsigned long i = 0; i < control_points.size(); i++){
            for(unsigned long j = 0; j < control_points[i].size(); j++){
                if(w->secondaryColor != "red")
                    w->primaryColor = "red";
                else
                    w->primaryColor = "green";

                *x0 = control_points[i][j].first;
                *y0 = control_points[i][j].second;
                *x1 = control_points[i][j].first+5;
                *y1 = control_points[i][j].second+5;
                w->Circle->draw();

                if((j==0 || (j-1)%3 != 0) && j != control_points[i].size()-1)
                        w->Line->draw({control_points[i][j].first,control_points[i][j].second}, {control_points[i][j+1].first, control_points[i][j+1].second});

                w->primaryColor = clr_tmp;
                *x0 = control_points[i][j].first;
                *y0 = control_points[i][j].second;
                *x1 = control_points[i][j].first+3;
                *y1 = control_points[i][j].second+3;
                w->Circle->draw();
            }
        }
        *x0 = a;
        *x1 = b;
        *y0 = c;
        *y1 = d;
    }
    else if(!visible && !imgEditor.isNull()){
        *(w->img) = imgEditor;
        imgEditor = *(new QImage());
    }
    w->update();

}


void toolBSpline::Interface(bool visible){
    interface = visible;

    if(visible){
        if((imgEditor).isNull())
            imgEditor = *(w->img);

        Color clr_tmp = w->primaryColor;
        unsigned long a = *x0, b = *x1, c = *y0, d = *y1;

        for(unsigned long i = 0; i < control_points.size(); i++){
            for(unsigned long j = 0; j < control_points[i].size(); j++){
                if(w->secondaryColor != "green")
                    w->primaryColor = "green";
                else
                    w->primaryColor = "red";

                *x0 = control_points[i][j].first;
                *y0 = control_points[i][j].second;
                *x1 = control_points[i][j].first+5;
                *y1 = control_points[i][j].second+5;
                w->Circle->draw();

                if((j==0 || (j-1)%3 != 0) && j != control_points[i].size()-1)
                        w->Line->draw({control_points[i][j].first,control_points[i][j].second}, {control_points[i][j+1].first, control_points[i][j+1].second});

                w->primaryColor = clr_tmp;
                *x0 = control_points[i][j].first;
                *y0 = control_points[i][j].second;
                *x1 = control_points[i][j].first+3;
                *y1 = control_points[i][j].second+3;
                w->Circle->draw();
            }
        }
        *x0 = a;
        *x1 = b;
        *y0 = c;
        *y1 = d;
    }
    else if(!visible && !imgEditor.isNull()){
        *(w->img) = imgEditor;
        imgEditor = *(new QImage());
    }
    w->update();

}


void toolLine::Interface(bool){}
void toolCircle::Interface(bool){}
void toolPolygon::Interface(bool){}
