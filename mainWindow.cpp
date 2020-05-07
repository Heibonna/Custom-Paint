#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "tools.h"
#include "toolLine.h"
#include "toolCircle.h"
#include "toolPolygon.h"
#include "toolBezierCurve.h"
#include "toolBSpline.h"
#include "toolFulfill.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow){

    ui->setupUi(this);

    setMouseTracking(true);

    szer = ui->Frame->width();
    wys = ui->Frame->height();
    poczX = ui->Frame->x();
    poczY = ui->Frame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    Line = new toolLine(this);
    Circle = new toolCircle(this);
    Polygon = new toolPolygon(this);
    Bezier = new toolBezierCurve(this);
    Spline = new toolBSpline(this);
    Fulfill = new toolFulfill(this);
    imgCopy = QImage(szer,wys,QImage::Format_RGB32);

    isPressed = 0;
    mode = 0;
    x0 = -1;
    y0 = -1;
    x1 = -1;
    y1 = -1;

    primaryColor = "white";
    on_cleanButton_clicked();
    primaryColor = "black";

    secondaryColor = "white";

    polygonVertices = 4;
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::cpyImg(QImage* cpy,QImage* src){
    for(int i=0; i<wys; i++){
        for(int j=0; j<szer; j++){
            cpy->bits()[szer*4*i + 4*j] = src->bits()[szer*4*i + 4*j];
            cpy->bits()[szer*4*i + 4*j + 1] = src->bits()[szer*4*i + 4*j + 1];
            cpy->bits()[szer*4*i + 4*j + 2] = src->bits()[szer*4*i + 4*j + 2];
            cpy->bits()[szer*4*i + 4*j + 3] = src->bits()[szer*4*i + 4*j + 3];
        }
    }
}


void mainWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void mainWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void mainWindow::paintPixels(int x, int y, Color clr){
    unsigned char *ptr;
    ptr = img->bits();
    if(clickedIntoWindow({x,y})){
        ptr[szer*4*y + 4*x] = clr.blue;
        ptr[szer*4*y + 4*x + 1] = clr.green;
        ptr[szer*4*y + 4*x + 2] = clr.red;
        ptr[szer*4*y + 4*x + 3] = clr.alpha;
    }
}

void mainWindow::paintPixels(int x, int y){
    paintPixels(x, y, primaryColor);
}

void mainWindow::on_cleanButton_clicked()
{
    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);


    for(int i=0; i<wys; i++){
        for(int j=0; j<szer; j++){
           paintPixels(j,i, primaryColor);
        }
    }

    if(!Bezier->control_points.empty())
        Bezier->control_points.clear();
    if(!Spline->control_points.empty())
        Spline->control_points.clear();

    update();
}

void mainWindow::on_penButton_clicked(){
    mode = 0;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);
}

void mainWindow::on_lineButton_clicked(){
    mode = 1;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);
}

void mainWindow::on_redButton_clicked(){
    primaryColor = "red";
}

void mainWindow::on_greenButton_clicked(){
    primaryColor = "green";
}

void mainWindow::on_blueButton_clicked(){
    primaryColor = "blue";
}

void mainWindow::on_blackButton_clicked(){
    primaryColor = "black";
}

void mainWindow::on_whiteButton_clicked(){
    primaryColor = "white";
}

void mainWindow::on_circleButton_clicked(){
    mode = 2;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);

}

void mainWindow::on_polygonButton_clicked(){
    mode = 3;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);

}

void mainWindow::on_spinBox_valueChanged(int value){
    polygonVertices = value;
}

void  mainWindow::on_addBezier_clicked(){
    mode = 4;
    Bezier -> current_adding = -1;

    std::vector<std::pair<int,int>> vctr;
    Bezier -> control_points.push_back(vctr);

    if(Spline->interface)
        Spline->Interface(false);
    if(!Bezier->interface)
        Bezier->Interface(true);
}

void  mainWindow::on_modifyBezier_clicked(){
    mode = 5;

    if(Spline->interface)
        Spline->Interface(false);
    if(!Bezier->interface)
        Bezier->Interface(true);
}

void  mainWindow::on_deleteBezier_clicked(){
    mode = 6;

    if(Spline->interface)
        Spline->Interface(false);
    if(!Bezier->interface)
        Bezier->Interface(true);
}

void  mainWindow::on_addSpline_clicked(){
    mode = 7;
    Spline -> current_adding = -1;

    std::vector<std::pair<int,int>> vctr;
    Spline -> control_points.push_back(vctr);


    if(Bezier->interface)
        Bezier->Interface(false);
    if(!Spline->interface)
        Spline->Interface(true);
}

void  mainWindow::on_modifySpline_clicked(){
    mode = 8;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(!Spline->interface)
        Spline->Interface(true);
}

void  mainWindow::on_deleteSpline_clicked(){
    mode = 9;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(!Spline->interface)
        Spline->Interface(true);
}

void  mainWindow::on_floodFill_clicked(){
    mode = 10;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);
}

void  mainWindow::on_scanLine_clicked(){
    mode = 11;

    if(Bezier->interface)
        Bezier->Interface(false);
    if(Spline->interface)
        Spline->Interface(false);
}



/////mouse tracking

void mainWindow::mousePressEvent(QMouseEvent *event){
    isPressed = true;

    x0 = event->x() - poczX;
    y0 = event->y() - poczY;

    if(mode == 5){
        Bezier->copy_x0 = x0;
        Bezier->copy_y0 = y0;
    }
    if(mode == 8){
        Spline->copy_x0 = x0;
        Spline->copy_y0 = y0;
    }

    cpyImg(&imgCopy,img);
}

void mainWindow::mouseMoveEvent(QMouseEvent *event){
    x1 = event->x() - poczX;
    y1 = event->y() - poczY;

    if(mode == 0){
        if(isPressed){
            if(clickedIntoWindow()){
                paintPixels(x1, y1);
            }
        }
    }
    else if(mode == 1){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Line->draw();
        }
    }
    else if(mode == 2){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Circle->draw();
        }
    }
    else if(mode == 3){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Polygon->draw();
        }
    }
    else if(mode == 5 && clickedIntoWindow()){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Bezier->modifyBezier();
        }
    }
    else if(mode == 8 && clickedIntoWindow()){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Spline->modify();
        }
    }
    update();
}

void mainWindow::mouseReleaseEvent(QMouseEvent *event){
    x1 = event->x() - poczX;
    y1 = event->y() - poczY;
    isPressed = false;

    if(mode == 1)
        Line -> draw();
    else if(mode == 2)
        Circle -> draw();
    else if(mode == 3)
        Polygon -> draw();
    else if(mode == 4){
        Bezier->Interface(false);
        Bezier -> addControlPoint();
        Bezier->Interface(true);
    }
    else if(mode == 5 && clickedIntoWindow() && !Bezier -> control_points.empty()){
        Bezier -> modifyBezier();
    }
    else if(mode == 6 && clickedIntoWindow() && !Bezier -> control_points.empty()){
        Bezier->Interface(false);
        Bezier -> deleteBezier();
        Bezier->Interface(true);
    }
    else if(mode == 7){
        Spline->Interface(false);
        Spline->addControlPoint();
        Spline->Interface(true);
    }
    else if(mode == 8 && clickedIntoWindow() && !Spline -> control_points.empty()){
        Spline -> modify();
    }
    else if(mode == 9 && clickedIntoWindow() && !Spline -> control_points.empty()){
        Spline->Interface(false);
        Spline->del();
        Spline->Interface(true);
    }
    else if(mode == 10 && clickedIntoWindow())
        Fulfill->draw(x1, y1, mode, img->bits());
    else if(mode == 11 && clickedIntoWindow())
        Fulfill->draw(x1, y1, mode, img->bits());

    x0 = -1;
    y0 = -1;
    x1 = -1;
    y1 = -1;

    update();
}

bool mainWindow::clickedIntoWindow(std::pair<int, int> P){
    if(P.first >= 0 && P.second >= 0 && P.first < szer && P.second < wys)
        return true;
    else
        return false;
}

bool mainWindow::clickedIntoWindow(){
    if(clickedIntoWindow({x0, y0}) && clickedIntoWindow({x1, y1}))
        return true;
    else
        return false;
}
