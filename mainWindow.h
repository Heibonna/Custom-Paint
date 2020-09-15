#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#include "structures.h"
#include "morfology.h"

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QWidget>
#include <QMouseEvent>
#include <QSpinBox>

class tools;
class toolLine;
class toolCircle;
class toolPolygon;
class toolBezierCurve;
class toolBSpline;
class toolsInterfaces;
class toolFulfill;
class toolFulfilledPolygon;
class colorPresentation;
class layer;
class transformations;

namespace Ui {
    class mainWindow;
}

class mainWindow : public QMainWindow {
    Q_OBJECT
    friend class tools;
    friend class toolLine;
    friend class toolCircle;
    friend class toolPolygon;
    friend class toolBezierCurve;
    friend class toolBSpline;
    friend class toolsInterfaces;
    friend class toolFulfill;
    friend class toolFulfilledPolygon;
    friend class colorPresentation;
    friend class layer;
    friend class transformations;
public:
    explicit mainWindow(QWidget *parent = 0);

    ~mainWindow();

protected:
    Ui::mainWindow *ui;
    QImage *img;
    QImage imgCopy;

    toolLine *Line;
    toolCircle *Circle;
    toolPolygon *Polygon;
    toolBezierCurve *Bezier;
    toolBSpline *Spline;
    toolFulfill *Fulfill;
    toolFulfilledPolygon *FullPolygon;
    colorPresentation *ColorPresentation;
    transformations *transform;

    //window properties
    int szer;
    int wys;
    int poczX;
    int poczY;

    //parameters
    int isPressed;
    Color primaryColor;
    Color secondaryColor;
    int mode;                       //0-pen, 1-line, 2-circle, 3-polygon, 4-6-bezier, 7-9-Splice, 10-floodFill, 11-scanLine

    //blending
    const int layerNumber = 3;
    layer* layers;

public:
    void cleanWindow();
    void paintPixels(int x, int y);
    void paintPixels(int x, int y, Color color);

    //specialised
    Point P0, P1;
    int polygonVertices;
    int selectedLayer = 0;
    kernel kernelType;

    //methods
    void czysc();
    void updateInterfaces(bool Bezier, bool B_Spline);
    void updateInterfaces();
    void bezierInterface();
    void splineInterface();
    void setMode(int mode);
    void imageProcessing(mm morfologyType);

    //controlers
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    bool clickedIntoWindow(Point);
    bool clickedIntoWindow();
    void cpyImg(QImage* cpy, QImage* src);
    void chooseTransformation(int i, int value);

private slots:
    void on_cleanButton_clicked();
    void on_penButton_clicked();
    void on_lineButton_clicked();
    void on_blackButton_clicked();
    void on_whiteButton_clicked();
    void on_redButton_clicked();
    void on_greenButton_clicked();
    void on_blueButton_clicked();
    void on_blackBackgroundButton_clicked();
    void on_whiteBackgroundButton_clicked();
    void on_redBackgroundButton_clicked();
    void on_greenBackgroundButton_clicked();
    void on_blueBackgroundButton_clicked();
    void on_circleButton_clicked();
    void on_polygonButton_clicked();
    void on_spinBox_valueChanged(int);
    void on_addBezier_clicked();
    void on_modifyBezier_clicked();
    void on_deleteBezier_clicked();
    void on_addSpline_clicked();
    void on_modifySpline_clicked();
    void on_deleteSpline_clicked();
    void on_scanLineButton_clicked();
    void on_floodFillButton_clicked();
    void on_slider1_sliderMoved(int);
    void on_slider2_sliderMoved(int);
    void on_slider3_sliderMoved(int);
    void on_slider4_sliderMoved(int);
    void on_slider5_sliderMoved(int);
    void on_slider6_sliderMoved(int);
    void on_alphaValue_sliderMoved(int);
    void on_blendingMode_currentIndexChanged(int);
    void on_listWidget_currentRowChanged(int);
    void on_crossBox_clicked();
    void on_cubeBox_clicked();
    void on_erosionButton_clicked();
    void on_dilationButton_clicked();
    void on_openingButton_clicked();
    void on_closingButton_clicked();
    void on_translationSlider_sliderMoved(int);
    void on_translationSlider2_sliderMoved(int);
    void on_rotationSlider_sliderMoved(int);
    void on_scalingSlider_sliderMoved(int);
    void on_scalingSlider2_sliderMoved(int);
    void on_shearingSlider_sliderMoved(int);
    void on_shearingSlider2_sliderMoved(int);
    void on_resetButton_clicked();
};

#endif // MAINWINDOW_H
