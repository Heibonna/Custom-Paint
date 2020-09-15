#ifndef TOOLBSPLINE_H
#define TOOLBSPLINE_H

#include "tools.h"
#include "toolLine.h"

class toolBSpline:tools
{
public:
friend class mainWindow;
private:
    QImage imgEditor;
    std::vector<std::vector<Point>> control_points;

    bool interface;
    int copy_x0, copy_y0;
    long current_adding;
    bool isMoving;
    Point currentMoving;

public:
    toolBSpline(mainWindow*);

    void addControlPoint(Point P0, Point P1);
    void draw();
    void draw(std::vector<Point> curve);
    void remove(unsigned long);
    void Interface(bool) ;
    void modify(Point P0, Point P1, bool isPressed);
    void del(Point P1);
    void reset();
};

#endif // TOOOLBSPLINE_H
