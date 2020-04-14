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
    switcher = false;
    clickedBefore = false;
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
    backgroundColor = color;
    if(!control_points.empty())
        control_points.clear();
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
    updateBezierInterface();
    mode = 0;
}

void MyWindow::on_lineButton_clicked(){
    updateBezierInterface();
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
    updateBezierInterface();
    mode = 2;
}

void MyWindow::on_polygonButton_clicked(){
    updateBezierInterface();
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

void  MyWindow::on_addBezier_clicked(){
    updateBezierInterface();

    mode = 4;

    if(!control_points.empty() && control_points.back().size() != 4)
        control_points.back().clear();
}

void  MyWindow::on_modifyBezier_clicked(){
    mode = 5;

    if(!control_points.empty() && control_points.back().size() != 4)
        control_points.back().clear();

    if(!clickedBefore){
        switcher = true;
        bezierInterface();
        update();
    }
    clickedBefore = true;
}

void  MyWindow::on_deleteBezier_clicked(){
    mode = 6;

    if(!control_points.empty() && control_points.back().size() != 4)
        control_points.back().clear();

    if(!clickedBefore){
        switcher = true;
        bezierInterface();
        update();
    }
    clickedBefore = true;
}


////////////////////////////////////////////////////


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

/////mouse tracking

void MyWindow::mousePressEvent(QMouseEvent *event){
    isPressed = true;

    x0 = event->x() - poczX;
    y0 = event->y() - poczY;

    imgCopy = *img;
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
    else if(mode == 4)
        addControlPoint();
    else if(mode == 5 && clickedIntoWindow() && !control_points.empty()){
        *img = imgEditor;
        modifyBezier();
        clickedBefore = false;
    }
    else if(mode == 6 && clickedIntoWindow() && !control_points.empty()){
        *img = imgEditor;
        deleteBezier();
        clickedBefore = false;
    }

    x0 = -1;
    y0 = -1;
    x1 = -1;
    y1 = -1;

    update();
}

/////exceptions

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

bool MyWindow::clickedIntoWindow(double range){
    if(clickedIntoWindow({x0+range, y0+range}) && clickedIntoWindow({x0-range, y0-range})
            && clickedIntoWindow({x0+range, y0-range}) && clickedIntoWindow({x0-range, y0+range}))
        return true;
    else
        return false;
}

/////draw

void MyWindow::drawLine(std::pair<int,int> p1, std::pair<int,int> p2){
    if(clickedIntoWindow(p2)){
        float a, b;
        if(p1.first == p2.first){
            for(int y = p1.second; y != p2.second; y += (p1.second < p2.second ? 1 : -1))
                paintPixels(p1.first, y);
        }
        else{
            a = float(p1.second - p2.second)/(p1.first - p2.first);
            b = p1.second - a * p1.first;

            if(a <= 1 && a >= -1){
                for(int x = p1.first; x != p2.first; x += (p1.first < p2.first ? 1 : -1)){
                    int y = a*x+b;
                    paintPixels(x, y);
                }
            }
            else{
                for(int y = p1.second; y != p2.second; y += (p1.second < p2.second ? 1 : -1)){
                    int x = (y-b)/a;
                    paintPixels(x, y);
                }
            }
        }
    }
}

void MyWindow::drawLine(){
    drawLine({x0,y0},{x1,y1});
}

void MyWindow::drawCircle(){
    int x, y;
    double r = sqrt(pow(x1-x0, 2.0) + pow(y1-y0, 2.0));

    if(clickedIntoWindow(r)){
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

void MyWindow::addControlPoint(){
    std::vector<std::pair<int,int>> vctr;
    vctr.push_back({x1, y1});

    if(control_points.empty()){
        control_points.push_back(vctr);
    }
    else{
        control_points.back().push_back({x1, y1});

        if(control_points.back().size() == 4){
            drawBezier(control_points.back());
            control_points.push_back(vctr);
        }
    }
}

void MyWindow::drawBezier(std::vector<std::pair<int,int>> curve){
    std::pair<int,int> p0, p1;
    double t;
    //std::cout << curve[0].first << "," << curve[0].second << "," << curve[1].first << "," << curve[1].second << "," <<  curve[2].first << "," << curve[2].second << "," << curve[3].first << "," << curve[3].second << std::lastl;

    p0 = {0, 0};
    p1 = {0, 0};

    for(int i = 0;i <= 60; i++){
        t = i/60.0;

        if(p0.first != 0 && p0.second != 0){
            p1.swap(p0);
            p0.first = round(pow(1.0-t,3.0)*curve[0].first + 3*pow(1.0-t,2.0)*curve[1].first*t + 3*(1.0-t)*curve[2].first*t*t + curve[3].first*t*t*t);
            p0.second = round(pow(1.0-t,3.0)*curve[0].second + 3*pow(1.0-t,2.0)*curve[1].second*t + 3*(1.0-t)*curve[2].second*t*t + curve[3].second*t*t*t);
            drawLine(p0, p1);
        }
        else{
            p0.first = round(pow(1.0-t,3.0)*curve[0].first + 3*pow(1.0-t,2.0)*curve[1].first*t + 3*(1.0-t)*curve[2].first*t*t + curve[3].first*t*t*t);
            p0.second = round(pow(1.0-t,3.0)*curve[0].second + 3*pow(1.0-t,2.0)*curve[1].second*t + 3*(1.0-t)*curve[2].second*t*t + curve[3].second*t*t*t);
        }
        //std::cout << "p0,p1,t(" << p0.first << "," << p0.second << "," << p1.first << "," << p1.second << "," << t << ")"<< std::endl;
    }
}

void MyWindow::bezierInterface(){
    bool fillingTmp = filling;
    filling = true;

    if(switcher && !control_points.empty()){
        imgEditor = *img;
        char clr = color;

        for(unsigned long i = 0; i < control_points.size(); i++){
            for(unsigned long j = 0; j < control_points[i].size(); j++){
                if(backgroundColor != 'r')
                    color = 'r';
                else
                    color = 'g';

                x0 = control_points[i][j].first;
                y0 = control_points[i][j].second;
                x1 = control_points[i][j].first+4;
                y1 = control_points[i][j].second+4;
                drawCircle();

                color = clr;
                x0 = control_points[i][j].first;
                y0 = control_points[i][j].second;
                x1 = control_points[i][j].first+2;
                y1 = control_points[i][j].second+2;
                drawCircle();
            }
        }
        color = clr;
    }
    else if(!switcher){
        *img = imgEditor;
    }

    filling = fillingTmp;
}

void MyWindow::updateBezierInterface(){
    if(mode == 5 && switcher){
        clickedBefore = false;
        switcher = false;
        bezierInterface();
        update();
    }
}

void MyWindow::modifyBezier(){
    switcher = false;

    char colortmp;

    for(unsigned long  i=0; i < control_points.size()-1; i++){
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].first - x0) <= 5 && abs(control_points[i][j].second - y0) <= 5){
            colortmp = color;
            if(j == 3 && control_points.size() - 2 != i){
                if(control_points[i][3] == control_points[i+1][0] && control_points[i+1].size() != 0){
                    color = backgroundColor;
                    drawBezier(control_points[i+1]);
                    color = colortmp;

                    control_points[i+1][0].first = x1;
                    control_points[i+1][0].second = y1;
                    drawBezier(control_points[i+1]);
                }
            }
            color = backgroundColor;
            drawBezier(control_points[i]);
            color = colortmp;

            control_points[i][j].first = x1;
            control_points[i][j].second = y1;
            drawBezier(control_points[i]);

            return;
            }
        }
    }
}

void MyWindow::deleteBezier(){
    switcher = false;
    unsigned long  min, max;
    char colortmp = color;
    for(unsigned long  i=0; i < control_points.size()-1; i++){
        if(control_points[i].size() == 0)
            continue;
        for(unsigned long  j=0; j < control_points[i].size(); j++){
            if(abs(control_points[i][j].first - x0) <= 5 && abs(control_points[i][j].second - y0) <= 5){
                max = i-1;
                do{
                    max++;
                    color = backgroundColor;
                    drawBezier(control_points[max]);
                    color = colortmp;
                    if(control_points.size() == max+2 ||control_points[max+1].size() == 0)
                        break;
                }
                while(control_points[max][3] == control_points[max+1][0]);
                min = i;

                if(j == 0 && control_points.size() != 1 && control_points[i][0] == control_points[i-1][3]){

                    min--;
                    color = backgroundColor;
                    drawBezier(control_points[min]);
                    color = colortmp;

                    control_points[i-1][3] = control_points[i][1];
                }
                if(j == 3 && control_points.size() > i+2 && control_points[i+1].size() != 0){
                    control_points[i][3] = control_points[i+1][1];
                    control_points[i+1][0] = control_points[i+1][1];

                    for(unsigned long  k=i+1; k < max; k++){
                        for(unsigned long  l=1; l < control_points[k].size(); l++){
                            if(l != 3)
                                control_points[k][l] = control_points[k][l+1];
                            else
                                control_points[k][l] = control_points[k+1][0];

                        }
                    }
                }
                else{
                    for(unsigned long  k=i; k <= max; k++){
                        for(unsigned long  l=0; l < control_points[k].size(); l++){
                            if(i == k && l < j)
                                continue;
                            else{
                                if(l != 3)
                                    control_points[k][l] = control_points[k][l+1];
                                else if(control_points[k].size() == l+1 && k == max)
                                    control_points[k].clear();
                                else
                                    control_points[k][l] = control_points[k+1][1];
                            }
                        }
                    }
                }
                for(unsigned long  k=min; k <= max; k++)
                    if(control_points[k].size() == 4)
                        drawBezier(control_points[k]);
                return;
            }
        }
    }
}

