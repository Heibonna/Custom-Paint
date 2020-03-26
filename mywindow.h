#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <iostream>
#include <cmath>
#include <vector>

#include <QMainWindow>
// Klasa QMainWindow posiada swoj wlasny layout.
// latwo mozna do niej dodac pasek menu, widzety dokujace,
// pasek narzedzi i pasek statusu. Na srodku okna
// wyswietlanego przez QMainWindow znajduje sie obszar,
// ktory mozna wypelnic roznymi widgetami.

#include <QPainter>
// niskopoziomowe rysowanie na elementach GUI

#include <QImage>
// QImage to klasa pozwalajaca na niezalezna od sprzetu reprezentacje obrazu.
// Pozwala na bezposredni dostep do poszczegolnych pikseli,

#include <QMouseEvent>
// klikniecia, ruch myszka itp.

#include <QSpinBox>

namespace Ui {
    class MyWindow;
}


class MyWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MyWindow(QWidget *parent = 0);

    ~MyWindow();

private:
    Ui::MyWindow *ui;

    QImage *img;
    QImage imgCopy;

    int szer;
    int wys;
    int poczX;
    int poczY;
    int isPressed;
    char color;     //black,white,red,green,blue
    int mode;       //0-pen, 1-line, 2-circle, 3-polygon
    int polygonVertices;

    int x0, y0, x1, y1;

    void czysc();
    void rysuj1();
    void rysuj2();

    void paintPixels(int, int);
    bool clickedIntoWindow(std::pair<int, int>);
    bool clickedIntoWindow();
    bool clickedIntoRange(double);
    void drawLine();
    void drawCircle();
    void drawPolygon();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);

private slots:
    void on_draw2Button_clicked();
    void on_draw1Button_clicked();
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


};

#endif // MYWINDOW_H
