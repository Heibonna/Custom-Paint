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
        int x0, x1, y0, y1;

        for(unsigned long i = 0; i < control_points.size(); i++){
            for(unsigned long j = 0; j < control_points[i].size(); j++){
                if(w->secondaryColor != "red")
                    w->primaryColor = "red";
                else
                    w->primaryColor = "green";

                x0 = control_points[i][j].x;
                y0 = control_points[i][j].y;
                x1 = control_points[i][j].x+5;
                y1 = control_points[i][j].y+5;

                w->Circle->draw({x0, y0}, {x1, y1});

                if((j==0 || (j-1)%3 != 0) && j != control_points[i].size()-1){
                    x0 = control_points[i][j].x;
                    y0 = control_points[i][j].y;
                    x1 = control_points[i][j+1].x;
                    y1 = control_points[i][j+1].y;
                    w->Line->draw({x0,y0}, {x1, y1});
                }

                w->primaryColor = clr_tmp;

                x0 = control_points[i][j].x;
                y0 = control_points[i][j].y;
                x1 = control_points[i][j].x+3;
                y1 = control_points[i][j].y+3;
                w->Circle->draw({x0, y0}, {x1,y1});
            }
        }
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
        int x0, x1, y0, y1;

        for(unsigned long i = 0; i < control_points.size(); i++){
            for(unsigned long j = 0; j < control_points[i].size(); j++){
                if(w->secondaryColor != "green")
                    w->primaryColor = "green";
                else
                    w->primaryColor = "red";

                x0 = control_points[i][j].x;
                y0 = control_points[i][j].y;
                x1 = control_points[i][j].x+5;
                y1 = control_points[i][j].y+5;

                w->Circle->draw({x0, y0}, {x1, y1});

                if((j==0 || (j-1)%3 != 0) && j != control_points[i].size()-1){
                    x0 = control_points[i][j].x;
                    y0 = control_points[i][j].y;
                    x1 = control_points[i][j+1].x;
                    y1 = control_points[i][j+1].y;
                    w->Line->draw({x0,y0}, {x1, y1});
                }

                w->primaryColor = clr_tmp;

                x0 = control_points[i][j].x;
                y0 = control_points[i][j].y;
                x1 = control_points[i][j].x+3;
                y1 = control_points[i][j].y+3;
                w->Circle->draw({x0, y0}, {x1,y1});
            }
        }
    }
    else if(!visible && !imgEditor.isNull()){
        *(w->img) = imgEditor;
        imgEditor = *(new QImage());
    }
    w->update();

}
