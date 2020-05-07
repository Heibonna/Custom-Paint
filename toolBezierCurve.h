#ifndef toolBezierCurve_H
#define toolBezierCurve_H

#include "tools.h"
#include "toolLine.h"

class toolBezierCurve:tools
{
friend class mainWindow;
private:
    QImage imgEditor;
    std::vector<std::vector<std::pair<int,int>>> control_points;

    bool interface;
    int copy_x0, copy_y0;
    long current_adding;

public:
    toolBezierCurve(mainWindow*);

    void addControlPoint();
    void draw() override;
    void draw(std::vector<std::pair<int,int>> curve);
    void removeBezier(unsigned long);
    void Interface(bool) override;
    void modifyBezier();
    void deleteBezier();
    void reset();
};

#endif // toolBezierCurve_H
