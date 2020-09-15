#ifndef toolBezierCurve_H
#define toolBezierCurve_H

#include "tools.h"
#include "toolLine.h"

class toolBezierCurve:tools
{
friend class mainWindow;
private:
    QImage imgEditor;
    std::vector<std::vector<Point>> control_points;

    bool interface;
    bool isMoving;
    int copy_x0, copy_y0;
    Point currentMoving;
    long current_adding;

public:
    toolBezierCurve(mainWindow*);

    void addControlPoint(Point P0, Point P1);
    void draw();
    void draw(std::vector<Point> curve);
    void removeBezier(unsigned long);
    void Interface(bool);
    void modifyBezier(Point P0, Point P1, bool isMoving);
    void deleteBezier(Point P1);
    void reset();
};

#endif // toolBezierCurve_H
