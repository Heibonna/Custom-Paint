#include "mainWindow.h"
#include "ui_mainWindow.h"
#include "tools.h"
#include "toolLine.h"
#include "toolCircle.h"
#include "toolPolygon.h"
#include "toolBezierCurve.h"
#include "toolBSpline.h"
#include "toolFulfill.h"
#include "toolFulfilledPolygon.h"
#include "colorPresentation.h"
#include "layer.h"
#include "transformations.h"

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
    FullPolygon = new toolFulfilledPolygon(this);
    ColorPresentation = new colorPresentation(this, wys, szer);
    imgCopy = QImage(szer,wys,QImage::Format_RGB32);
    layers = new layer[layerNumber];
    transform = new transformations(":/resources/virus-icon.jpg", img);

    layers[0] = layer(":/resources/aurora.jpg");
    layers[1] = layer(":/resources/linux.png");
    layers[2] = layer(":/resources/mlp.jpg");

    isPressed = 0;
    mode = 0;
    P0 = {-1,-1};
    P1 = {-1,-1};

    secondaryColor = "white";

    cleanWindow();

    polygonVertices = 4;

    kernelType = cross;
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::cpyImg(QImage* cpy,QImage* src){
    if(cpy->width() != src->width()
    || cpy->height() != src->width())
        std::cout << "Cannot copy image" << std::endl;
    else
        for(int i=0; i<wys; i++)
        for(int j=0; j<szer;j++){
            cpy->bits()[szer*4*i + 4*j] = src->bits()[szer*4*i + 4*j];
            cpy->bits()[szer*4*i + 4*j + 1] = src->bits()[szer*4*i + 4*j + 1];
            cpy->bits()[szer*4*i + 4*j + 2] = src->bits()[szer*4*i + 4*j + 2];
            cpy->bits()[szer*4*i + 4*j + 3] = src->bits()[szer*4*i + 4*j + 3];
        }
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

void mainWindow::updateInterfaces(bool bezier, bool bspline){
    if(!bezier && bspline){
        if(Bezier->interface)
            Bezier->Interface(false);
        if(!Spline->interface)
            Spline->Interface(true);
    }
    else if(bezier && !bspline){
        if(Spline->interface)
            Spline->Interface(false);
        if(!Bezier->interface)
            Bezier->Interface(true);
    }
    else if(!bezier && !bspline){
        if(Bezier->interface)
            Bezier->Interface(false);
        if(Spline->interface)
            Spline->Interface(false);
    }
}

void mainWindow::updateInterfaces(){
    updateInterfaces(false, false);
}

void mainWindow::bezierInterface(){
    updateInterfaces(true, false);
}

void mainWindow::splineInterface(){
    updateInterfaces(false, true);
}

void mainWindow::setMode(int mode){
    this->mode = mode;
    FullPolygon -> points.clear();

    if(mode < 4 || mode > 9)
        updateInterfaces();
    else if(mode >= 4 && mode <= 6)
        bezierInterface();
    else if(mode >= 7 && mode <= 9)
        splineInterface();
}

void mainWindow::cleanWindow(){
    for(int i=0; i<wys; i++){
        for(int j=0; j<szer; j++){
            paintPixels(j,i, secondaryColor);
        }
    }

    if(!Bezier->control_points.empty())
        Bezier->control_points.clear();
    if(!Spline->control_points.empty())
        Spline->control_points.clear();
    FullPolygon -> points.clear();


    update();
}


void mainWindow::on_cleanButton_clicked()
{
    updateInterfaces();
    cleanWindow();
}

void mainWindow::on_penButton_clicked(){
    setMode(0);
}

void mainWindow::on_lineButton_clicked(){
    setMode(1);
}

void mainWindow::on_redButton_clicked(){
    primaryColor = Color(255, 0, 0);

}

void mainWindow::on_greenButton_clicked(){
    primaryColor = Color(0, 255, 0);

}

void mainWindow::on_blueButton_clicked(){
    primaryColor = Color(0, 0, 255);
}

void mainWindow::on_blackButton_clicked(){
    primaryColor = Color(0, 0, 0);
}

void mainWindow::on_whiteButton_clicked(){
    primaryColor = Color(255, 255, 255);
}

void mainWindow::on_redBackgroundButton_clicked(){
    secondaryColor = Color(255, 0, 0);

}

void mainWindow::on_greenBackgroundButton_clicked(){
    secondaryColor = Color(0, 255, 0);

}

void mainWindow::on_blueBackgroundButton_clicked(){
    secondaryColor = Color(0, 0, 255);
}

void mainWindow::on_blackBackgroundButton_clicked(){
    secondaryColor = Color(0, 0, 0);
}

void mainWindow::on_whiteBackgroundButton_clicked(){
    secondaryColor = Color(255, 255, 255);
}

void mainWindow::on_circleButton_clicked(){
    setMode(2);
}

void mainWindow::on_polygonButton_clicked(){
    setMode(3);
}

void mainWindow::on_spinBox_valueChanged(int value){
    polygonVertices = value;
}

void  mainWindow::on_addBezier_clicked(){
    setMode(4);

    Bezier -> current_adding = -1;
    std::vector<Point> vctr;
    Bezier -> control_points.push_back(vctr);
}

void  mainWindow::on_modifyBezier_clicked(){
    setMode(5);
}

void  mainWindow::on_deleteBezier_clicked(){
    setMode(6);
}

void  mainWindow::on_addSpline_clicked(){
    setMode(7);

    Spline -> current_adding = -1;
    std::vector<Point> vctr;
    Spline -> control_points.push_back(vctr);

}

void  mainWindow::on_modifySpline_clicked(){
    setMode(8);
}

void  mainWindow::on_deleteSpline_clicked(){
    setMode(9);
}

void  mainWindow::on_floodFillButton_clicked(){
    setMode(10);
}

void  mainWindow::on_scanLineButton_clicked(){
    setMode(11);
}

void  mainWindow::on_slider1_sliderMoved(int value){
    setMode(0);
    ColorPresentation->present(1, value);
    update();
}

void  mainWindow::on_slider2_sliderMoved(int value){
    setMode(0);
    ColorPresentation->present(2, value);
    update();
}

void  mainWindow::on_slider3_sliderMoved(int value){
    setMode(0);
    ColorPresentation->present(3, value);
    update();
}

void  mainWindow::on_slider4_sliderMoved(int value){
    setMode(0);
    ColorPresentation->present(4, value);
    update();
}

void  mainWindow::on_slider5_sliderMoved(int value){
    setMode(0);
    ColorPresentation->present(5, value);
    update();
}

void  mainWindow::on_slider6_sliderMoved(int value){
    setMode(0);
    ColorPresentation->present(6, value);
    update();
}


void mainWindow::on_alphaValue_sliderMoved(int value){
    layers[selectedLayer].updateLayer(value, static_cast<blending>(ui->blendingMode->currentIndex()));
    cleanWindow();
    layers[0].getImage(layerNumber, layers, img);
    update();
}

void mainWindow::on_blendingMode_currentIndexChanged(int value){
    layers[selectedLayer].updateLayer(ui->alphaValue->value(), static_cast<blending>(value));
    cleanWindow();
    layers[0].getImage(layerNumber, layers, img);
    update();
}

void mainWindow::on_listWidget_currentRowChanged(int i){
    selectedLayer = i;
    ui->alphaValue->setValue((int)100*layers[i].alpha);
    ui->blendingMode->setCurrentIndex(static_cast<int>(layers[i].mode));
}

void mainWindow::imageProcessing(mm morfologyType){
    mode = 0;
    morfology::draw(morfologyType, kernelType, primaryColor, secondaryColor, img);
    update();
}

void mainWindow::on_crossBox_clicked(){
    kernelType = cross;
}

void mainWindow::on_cubeBox_clicked(){
    kernelType = cube;
}

void mainWindow::on_erosionButton_clicked(){
    imageProcessing(erosion);
}

void mainWindow::on_dilationButton_clicked(){
    imageProcessing(dilation);
}

void mainWindow::on_openingButton_clicked(){
    imageProcessing(opening);
}

void mainWindow::on_closingButton_clicked(){
    imageProcessing(closing);
}

void mainWindow::chooseTransformation(int i, int value){
    cleanWindow();
    if(i == 0)
        transform->translocation(value, ui->translationSlider2->value());
    else if(i == 1)
        transform->translocation(ui->translationSlider->value(), value);
    else if(i == 2)
        transform->rotating(value);
    else if(i == 3)
        transform->scalling(value, ui->scalingSlider2->value());
    else if(i == 4)
        transform->scalling(ui->scalingSlider->value(), value);
    else if(i == 5)
        transform->shearing(value, ui->shearingSlider2->value());
    else if(i == 6)
        transform->shearing(ui->shearingSlider->value(), value);

    update();
}

void mainWindow::on_translationSlider_sliderMoved(int value){
    chooseTransformation(0, value);
}
void mainWindow::on_translationSlider2_sliderMoved(int value){
    chooseTransformation(1, value);
}
void mainWindow::on_rotationSlider_sliderMoved(int value){
    chooseTransformation(2, value);
}
void mainWindow::on_scalingSlider_sliderMoved(int value){
    chooseTransformation(3, value);
}
void mainWindow::on_scalingSlider2_sliderMoved(int value){
    chooseTransformation(4, value);
}
void mainWindow::on_shearingSlider_sliderMoved(int value){
    chooseTransformation(5, value);
}
void mainWindow::on_shearingSlider2_sliderMoved(int value){
    chooseTransformation(6, value);
}
void mainWindow::on_resetButton_clicked(){
     ui->translationSlider2->setValue(0);
     ui->translationSlider->setValue(0);
     ui->scalingSlider2->setValue(500);
     ui->scalingSlider->setValue(500);
     ui->rotationSlider->setValue(0);
     ui->shearingSlider->setValue(0);
     ui->shearingSlider2->setValue(0);

     cleanWindow();
     transform -> reset();
     update();
}


/////mouse tracking

void mainWindow::mousePressEvent(QMouseEvent *event){
    isPressed = true;

    P0.x = event->x() - poczX;
    P0.y = event->y() - poczY;

    if(mode == 5){
        Bezier->copy_x0 = P0.x;
        Bezier->copy_y0 = P0.y;
    }
    if(mode == 8){
        Spline->copy_x0 = P0.x;
        Spline->copy_y0 = P0.y;
    }

    cpyImg(&imgCopy,img);
}

void mainWindow::mouseMoveEvent(QMouseEvent *event){
    P1.x = event->x() - poczX;
    P1.y = event->y() - poczY;

    if(mode == 0){
        if(isPressed){
            if(clickedIntoWindow()){
                paintPixels(P1.x, P1.y);
            }
        }
    }
    else if(mode == 1){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Line->draw(P0, P1);
        }
    }
    else if(mode == 2){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Circle->draw(P0, P1);
        }
    }
    else if(mode == 3){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Polygon->draw(P0, P1);
        }
    }
    else if(mode == 5 && clickedIntoWindow()){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Bezier->modifyBezier(P0, P1, isPressed);
        }
    }
    else if(mode == 8 && clickedIntoWindow()){
        if(isPressed){
            cpyImg(img, &imgCopy);
            Spline->modify(P0, P1, isPressed);
        }
    }
    update();
}

void mainWindow::mouseReleaseEvent(QMouseEvent *event){
    P1.x = event->x() - poczX;
    P1.y = event->y() - poczY;
    isPressed = false;

    if(mode == 1)
        Line -> draw(P0, P1);
    else if(mode == 2)
        Circle -> draw(P0, P1);
    else if(mode == 3)
        Polygon -> draw(P0, P1);
    else if(mode == 4)
        Bezier -> addControlPoint(P0, P1);
    else if(mode == 5 && clickedIntoWindow() && !Bezier -> control_points.empty())
        Bezier -> modifyBezier(P0, P1, isPressed);
    else if(mode == 6 && clickedIntoWindow() && !Bezier -> control_points.empty())
        Bezier -> deleteBezier(P1);
    else if(mode == 7)
        Spline->addControlPoint(P0, P1);
    else if(mode == 8 && clickedIntoWindow() && !Spline -> control_points.empty())
        Spline -> modify(P0, P1, isPressed);
    else if(mode == 9 && clickedIntoWindow() && !Spline -> control_points.empty())
        Spline->del(P1);
    else if(mode == 10 && clickedIntoWindow())
        Fulfill->draw(P1, img->bits());
    else if(mode == 11 && clickedIntoWindow())
        FullPolygon->draw(P1);

    P0 = {-1, -1};
    P1 = {-1, -1};

    update();
}

bool mainWindow::clickedIntoWindow(Point P){
    if(P.x >= 0 && P.y >= 0 && P.x < szer && P.y < wys)
        return true;
    else
        return false;
}

bool mainWindow::clickedIntoWindow(){
    if(clickedIntoWindow(P0) && clickedIntoWindow(P1))
        return true;
    else
        return false;
}
