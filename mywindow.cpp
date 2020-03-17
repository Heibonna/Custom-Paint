#include "mywindow.h"
#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow){

    ui->setupUi(this);

    setMouseTracking(true);

    szer = ui->rysujFrame->width();
    wys = ui->rysujFrame->height();
    poczX = ui->rysujFrame->x();
    poczY = ui->rysujFrame->y();

    img = new QImage(szer,wys,QImage::Format_RGB32);

    isPressed = 0;
    mode = 0;
    x0 = -1;
    y0 = -1;
    x1 = -1;
    y1 = -1;
    color = 'w';
    on_cleanButton_clicked();
    color = 'b';
}

MyWindow::~MyWindow()
{
    delete ui;
}

void MyWindow::on_exitButton_clicked()
{
    qApp->quit();
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    p.drawImage(poczX,poczY,*img);
}

void MyWindow::on_cleanButton_clicked()
{
    for(int i=0; i<wys; i++){
        for(int j=0; j<szer; j++){
           paintPixels(j,i);
        }
    }
    update();
}

void MyWindow::on_draw1Button_clicked()
{
    rysuj1();
    update();
}

void MyWindow::on_draw2Button_clicked()
{
    rysuj2();
    update();
}

void MyWindow::on_penButton_clicked(){
    mode = 0;
}

void MyWindow::on_lineButton_clicked(){
    mode = 1;
}

void MyWindow::on_redButton_clicked(){
    color = 'r';
}

void MyWindow::on_greenButton_clicked(){
    color = 'g';
}

void MyWindow::on_blueButton_clicked(){
    color = 'l';
}

void MyWindow::on_blackButton_clicked(){
    color = 'b';
}

void MyWindow::on_whiteButton_clicked(){
    color = 'w';
}

void MyWindow::on_circleButton_clicked(){
    mode = 2;
}

void MyWindow::paintPixels(int x, int y){
    unsigned char *ptr;
    ptr = img->bits();

    if(color == 'b'){
        ptr[szer*4*y + 4*x] = 0;
        ptr[szer*4*y + 4*x + 1] = 0;
        ptr[szer*4*y + 4*x + 2] = 0;
        ptr[szer*4*y + 4*x + 3] = 255;
    }
    else if(color == 'w'){
        ptr[szer*4*y + 4*x] = 255;
        ptr[szer*4*y + 4*x + 1] = 255;
        ptr[szer*4*y + 4*x + 2] = 255;
        ptr[szer*4*y + 4*x + 3] = 255;
    }
    else if(color == 'l'){
        ptr[szer*4*y + 4*x] = 255;
        ptr[szer*4*y + 4*x + 1] = 0;
        ptr[szer*4*y + 4*x + 2] = 0;
        ptr[szer*4*y + 4*x + 3] = 255;
    }
    else if(color == 'r'){
        ptr[szer*4*y + 4*x] = 0;
        ptr[szer*4*y + 4*x + 1] = 0;
        ptr[szer*4*y + 4*x + 2] = 255;
        ptr[szer*4*y + 4*x + 3] = 255;
    }
    else if(color == 'g'){
        ptr[szer*4*y + 4*x] = 0;
        ptr[szer*4*y + 4*x + 1] = 255;
        ptr[szer*4*y + 4*x + 2] = 0;
        ptr[szer*4*y + 4*x + 3] = 255;
    }
    else{
        std::cout << "Error: wrong color\n";
    }
}

void MyWindow::rysuj1()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

        int i,j;

        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i*j;
                }
        }
}

void MyWindow::rysuj2()
{
        unsigned char *ptr;
        ptr = img->bits();
        int szer = img->width();
        int wys = img->height();

        int i,j;
        for(i=0;i<wys;i++)
        {
                for(j=0;j<szer ;j++)
                {
                        ptr[szer*4*i + 4*j]=i;
                        ptr[szer*4*i + 4*j + 1] = j;
                        ptr[szer*4*i + 4*j + 2] = i+j;
                }
        }
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{
    isPressed = true;

    if(mode == 1 || mode == 2){
        imgCopy = *img;
        x0 = event->x() - poczX;
        y0 = event->y() - poczY;
    }
}

void MyWindow::mouseMoveEvent(QMouseEvent *event){
    x1 = event->x() - poczX;
    y1 = event->y() - poczY;
    //std::cout << x1 << "," << y1 << std::endl;

    if(mode == 0){
        if(isPressed){
            if(clickedIntoWindow()){
                paintPixels(x1, y1);
            }
        }
    }
    else if(mode == 1){
        if(isPressed){
            *img = imgCopy;
            drawLine(event);
        }
    }
    else if(mode == 2){
        if(isPressed){
            *img = imgCopy;
            drawCircle(event);
        }
    }
    update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event){
    isPressed = false;
    if(mode == 1){
        drawLine(event);
        x0 = -1;
        y0 = -1;
        x1 = -1;
        y1 = -1;
    }
    else if(mode == 2){
        drawCircle(event);
        x0 = -1;
        y0 = -1;
        x1 = -1;
        y1 = -1;
    }
    update();
}

bool MyWindow::clickedIntoWindow(){
    if(((x0>=0)&&(x0<szer)&&(y0>=0)&&(y0<wys)&&(x1<szer)&&(x1>=0)&&(y1<wys)&&(y1>=0))
        || ((x0>=0)&&(x0<szer)&&(y0>=0)&&(y0<wys)&&(x1==-1)&&(x1==-1))
            || ((x1>=0)&&(x1<szer)&&(y1>=0)&&(y1<wys)&&(x0==-1)&&(x0==-1)))
        return true;
    else
        return false;
}

bool MyWindow::clickedIntoRange(double range){
    if(clickedIntoWindow()&&(x0+range<szer)&&(y0+range<wys)&&(x0-range>=0)&&(y0-range>=0))
        return true;
    else
        return false;
}

void MyWindow::drawLine(QMouseEvent *event){
    x1 = event->x() - poczX;
    y1 = event->y() - poczY;

    if(clickedIntoWindow()){
        float a, b;
        if(x0 == x1){
            a = float(y0 - y1 + x0)/x0;
            b = y1 - x0;
        }
        else{
            a = float(y0 - y1)/(x0 - x1);
            b = y0 - a * x0;
        }
        if(a <= 1 && a >= -1){
            for(int x = x0; x != x1; x += (x0 < x1 ? 1 : -1)){
                int y = a*x+b;
                paintPixels(x, y);
            }
        }
        else{
            for(int y = y0; y != y1; y += (y0 < y1 ? 1 : -1)){
                int x = (y-b)/a;
                paintPixels(x, y);
            }
        }
    }
    update();
}

void MyWindow::drawCircle(QMouseEvent *event){
    x1 = event->x() - poczX;
    y1 = event->y() - poczY;

    int x, y;
    double r = sqrt(pow(x1-x0, 2.0) + pow(y1-y0, 2.0));

    //std::cout << "!!!r(" << r << ") "<< std::endl;
    //std::cout << "!!!xy0(" << x0 << "," << y0 << ")"<< std::endl;
    //std::cout << "!!!xy1(" << x1 << "," << y1 << ")"<< std::endl;

    if(clickedIntoRange(r)){
        for(x = 0; x < r; x++){
            y = int(sqrt(pow(r, 2.0) - pow(x, 2.0)));
            std::cout << "xy1(" << x << "," << y << ")"<< std::endl;
            paintPixels(x0 + x, y0 + y);
            paintPixels(x0 - x, y0 + y);
            paintPixels(x0 + x, y0 - y);
            paintPixels(x0 - x, y0 - y);
            paintPixels(x0 + y, y0 + x);
            paintPixels(x0 + y, y0 - x);
            paintPixels(x0 - y, y0 + x);
            paintPixels(x0 - y, y0 - x);
        }
    }
}
