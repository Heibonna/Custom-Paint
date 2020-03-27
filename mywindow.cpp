#include "mywindow.h"
#include "ui_mywindow.h"

MyWindow::MyWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyWindow){

    ui->setupUi(this);

    setMouseTracking(true);

    szer = ui->Frame->width();
    wys = ui->Frame->height();
    poczX = ui->Frame->x();
    poczY = ui->Frame->y();

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
    polygonVertices = 4;
    filling = false;
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

void MyWindow::on_polygonButton_clicked(){
    mode = 3;
}

void MyWindow::on_spinBox_valueChanged(int value){
    polygonVertices = value;
}

void MyWindow::on_fillingBox_stateChanged(int state){
    if(state)
        filling = true;
    else
        filling = false;
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

    imgCopy = *img;

    x0 = event->x() - poczX;
    y0 = event->y() - poczY;
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
            drawLine();
        }
    }
    else if(mode == 2){
        if(isPressed){
            *img = imgCopy;
            drawCircle();
        }
    }
    else if(mode == 3){
        if(isPressed){
            *img = imgCopy;
            drawPolygon();
        }
    }
    update();
}

void MyWindow::mouseReleaseEvent(QMouseEvent *event){
    x1 = event->x() - poczX;
    y1 = event->y() - poczY;
    isPressed = false;

    if(mode == 1)
        drawLine();
    else if(mode == 2)
        drawCircle();
    else if(mode == 3)
        drawPolygon();

    x0 = -1;
    y0 = -1;
    x1 = -1;
    y1 = -1;

    update();
}

bool MyWindow::clickedIntoWindow(){
    if(clickedIntoWindow({x0, y0}) && clickedIntoWindow({x1, y1}))
        return true;
    else
        return false;
}

bool MyWindow::clickedIntoWindow(std::pair<int, int> P){
    if(P.first >= 0 && P.second >= 0 && P.first < szer && P.second < wys)
        return true;
    else
        return false;
}

bool MyWindow::clickedIntoRange(double range){
    if(clickedIntoWindow({x0+range, y0+range}) && clickedIntoWindow({x0-range, y0-range})
            && clickedIntoWindow({x0+range, y0-range}) && clickedIntoWindow({x0-range, y0+range}))
        return true;
    else
        return false;
}

void MyWindow::drawLine(){
    if(clickedIntoWindow()){
        float a, b;
        if(x0 == x1){
            for(int y = y0; y != y1; y += (y0 < y1 ? 1 : -1))
                paintPixels(x0, y);
        }
        else{
            a = float(y0 - y1)/(x0 - x1);
            b = y0 - a * x0;

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
    }
}

void MyWindow::drawCircle(){
    int x, y;
    double r = sqrt(pow(x1-x0, 2.0) + pow(y1-y0, 2.0));

    if(clickedIntoRange(r)){
        if(!filling || isPressed){
            for(x = 0; x < r; x++){
                y = int(sqrt(pow(r, 2.0) - pow(x, 2.0)));
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
        else{
            for(int x = 0; x < r; x++){
                for(int y = 0; y < r; y++){
                    if(y*y + x*x <= r*r){
                        paintPixels(x0 + x, y0 + y);
                        paintPixels(x0 - x, y0 + y);
                        paintPixels(x0 + x, y0 - y);
                        paintPixels(x0 - x, y0 - y);
                    }
                }
            }
        }
    }
}

void MyWindow::drawPolygon(){
    std::pair<double, double> copy[2] = {{x0,y0}, {x1,y1}};
    double x, y;
    double alpha = 2 * M_PI/polygonVertices;
    double a, b;
    std::vector<std::pair<double,double>> points;

    if(!clickedIntoWindow())
        return;

    a = double(x1>=x0 ? x1-x0 : x0-x1);
    b = double(y1>=y0 ? y1-y0 : y0-y1);

    for(double beta = alpha; beta <= 2*M_PI; beta += 2 * M_PI/polygonVertices){
        y = (b * sin(beta));
        x = (a * cos(beta));

        if(!clickedIntoWindow({x+x0,y+y0}))
            return;

        points.push_back({x0+x, y0+y});

    }
    for(int i = 0; i < polygonVertices-1; i++){
        x0 = points[i].first;
        y0 = points[i].second;
        x1 = points[i+1].first;
        y1 = points[i+1].second;

        drawLine();
    }
    x0 = points[polygonVertices-1].first;
    y0 = points[polygonVertices-1].second;
    x1 = points[0].first;
    y1 = points[0].second;
    drawLine();

    //std::cout << "x0,x1,y0,y1,alhpa,a,b(" << x0 << "," << x1 << "," << y0 << "," << y1 << "," << alpha << "," << a << "," << b << ")"<< std::endl;

    x0 = copy[0].first;
    y0 = copy[0].second;
    x1 = copy[1].first;
    y1 = copy[1].second;
}
