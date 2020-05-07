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
    std::vector<std::vector<std::pair<int,int>>> control_points;

    bool interface;
    int copy_x0, copy_y0;
    long current_adding;

public:
    toolBSpline(mainWindow*);

    void addControlPoint();
    void draw() override;
    void draw(std::vector<std::pair<int,int>> curve);
    void remove(unsigned long);
    void Interface(bool) override;
    void modify();
    void del();
    void reset();
};

#endif // TOOOLBSPLINE_H
