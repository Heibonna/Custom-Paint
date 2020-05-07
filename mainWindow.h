#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QSpinBox>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifndef Color
struct Color
{
    int red = 0;
    int green = 0;
    int blue = 0;
    int alpha = 255;

    Color& operator=(const std::string& rhs){
            if(rhs == "red"){
                red = 255;
                green = 0;
                blue = 0;
            }
            else if(rhs == "green"){
                red = 0;
                green = 255;
                blue = 0;
            }
            else if(rhs == "blue"){
                red = 0;
                green = 0;
                blue = 255;
            }
            else if(rhs == "black"){
                red = 0;
                green = 0;
                blue = 0;
            }
            else if(rhs == "white"){
                red = 255;
                green = 255;
                blue = 255;
            }
            return *this;
    }

    bool operator==(const Color& rhs){
        return (this->red == rhs.red && this->green == rhs.green &&
                this->blue == rhs.blue && this->alpha == rhs.alpha);
    }
    bool operator==(const std::string& rhs){
        if(rhs == "red"){
            return (this->red == 255 && this->green == 0 &&
                this->blue == 0 && this->alpha == 255);
        }
        else if(rhs == "green"){
            return (this->red == 0 && this->green == 255 &&
                this->blue == 0 && this->alpha == 255);
        }
        else if(rhs == "blue"){
            return (this->red == 0 && this->green == 0 &&
                this->blue == 255 && this->alpha == 255);
        }
        else if(rhs == "black"){
            return (this->red == 0 && this->green == 0 &&
                this->blue == 0 && this->alpha == 255);
        }
        else if(rhs == "white"){
            return (this->red == 255 && this->green == 255 &&
                this->blue == 255 && this->alpha == 255);
        }
        else
            return false;
    }
    bool operator!=(const Color& rhs){
        return !(*this == rhs);
    }
    bool operator!=(const std::string& rhs){
        return !(*this == rhs);
    }

};
#endif

class tools;
class toolLine;
class toolCircle;
class toolPolygon;
class toolBezierCurve;
class toolBSpline;
class toolsInterfaces;
class toolFulfill;

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

    //window properties
    int szer;
    int wys;
    int poczX;
    int poczY;

    //parameters
    int isPressed;
    Color primaryColor;
    Color secondaryColor;
    int mode;       //0-pen, 1-line, 2-circle, 3-polygon, 4-addBezier, 5-modifyBezier, 6-removeBezier

    void paintPixels(int x, int y);
    void paintPixels(int x, int y, Color color);
    void cpyImg(QImage* src, QImage* cpy);

    //specialised
    int x0, y0, x1, y1;
    int polygonVertices;

    //methods
    void czysc();

    //controlers
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

    bool clickedIntoWindow(std::pair<int, int>);
    bool clickedIntoWindow();

private slots:
    void on_cleanButton_clicked();
    void on_penButton_clicked();
    void on_lineButton_clicked();
    void on_exitButton_clicked();
    void on_blackButton_clicked();
    void on_whiteButton_clicked();
    void on_redButton_clicked();
    void on_greenButton_clicked();
    void on_blueButton_clicked();
    void on_circleButton_clicked();
    void on_polygonButton_clicked();
    void on_spinBox_valueChanged(int);
    void on_addBezier_clicked();
    void on_modifyBezier_clicked();
    void on_deleteBezier_clicked();
    void on_addSpline_clicked();
    void on_modifySpline_clicked();
    void on_deleteSpline_clicked();
    void on_scanLine_clicked();
    void on_floodFill_clicked();
};

#endif // MAINWINDOW_H
