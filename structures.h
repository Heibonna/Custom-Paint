#ifndef STRUCTURES_H
#define STRUCTURES_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <iostream>
#include <cmath>

enum kernel{
    cross, cube
};

enum mm{
     erosion, dilation, opening, closing
};

enum blending{
    normal,
    multiple,
    darken,
    lighten,
    difference,
    additive,
    substractive
};

enum transformationMode{
    translation,
    rotation,
    scaling,
    shearing
};

struct Color{
    int red = 0;
    int green = 0;
    int blue = 0;
    int alpha = 255;

    Color(){};
    Color(int red, int green, int blue): red(red), green(green), blue(blue){};
    Color(int red, int green, int blue, int alpha): red(red), green(green), blue(blue), alpha(alpha){};
    Color(unsigned char *bits){
        blue = (int)*bits;
        green = (int)*(bits+1);
        red = (int)*(bits+2);
        alpha = (int)*(bits+3);
    }


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

    bool operator==(unsigned char* rhs){
        return (this->red == *(rhs+2) && this->green == *(rhs+1) && this->blue == *rhs);
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

    Color operator*(const double second){
        return Color(red * second, green*second, blue*second, alpha);
    }

    Color operator+(const Color second){
        if(alpha != 0 && second.alpha != 0)
            return Color(red + second.red, green + second.green, blue + second.blue, alpha+second.alpha);
        else if(alpha != 0)
            return *this;
        else if(second.alpha != 0)
            return second;
        else
            return Color(0, 0, 0, 0);
    }

    void convertToUChar(unsigned char* bits){
        *bits = (unsigned char)this->blue;
        *(bits+1) = (unsigned char)this->green;
        *(bits+2) = (unsigned char)this->red;
        *(bits+3) = (unsigned char)this->alpha;
    }
};

struct Point{
    int x;
    int y;

    Point(): x(0.0), y(0.0) {};
    Point(int x, int y): x(x), y(y){};

    void swap(){
        x += y;
        y = x - y;
        x -= y;
    }

    void swap(Point &second){
        Point tmp(x, y);
        this->x = second.x;
        this->y = second.y;
        second.x = tmp.x;
        second.y = tmp.y;
    }

    bool inRange(const Point second){
        return (this->x - second.x <= 2 && this->x - second.x >= -2
                && this->y - second.y <= 2 && this->y - second.y >= -2);
    }

    bool operator==(const Point second){
        return (this->x == second.x && this->y == second.y);
    }

    Point& operator=(int xy[2]){
        x = xy[0];
        y = xy[1];
        return *this;
    }

    //TO DO:
    //przeciążenia operatorów  < > iostream
    //dodanie do w punktu {w->szer, w->wys} i dodanie tego do tools
};

struct ET{
    Point P0;
    Point P1;
    int Ymax;
    int Ymin;
    int Xmax;
    int Xmin;
    double m;


    ET(Point P0, Point P1):P0(P0), P1(P1){
        if(P0.x <= P1.x){
            Xmin = P0.x;
            Xmax = P1.x;
        }
        else{
            Xmin = P1.x;
            Xmax = P0.x;
        }

        if(P0.y <= P1.y){
            Ymax = P1.y;
            Ymin = P0.y;
        }
        else{
            Ymax = P0.y;
            Ymin = P1.y;
        }
        if(Ymax == Ymin)
            m = 0;
        else
            m = (1.0*P1.x-P0.x)/(1.0*P1.y-P0.y);
    }

    ET(){
        ET({-1,-1},{-1,-1});
    }

    bool operator< (const ET& other) const {
        return Ymax < other.Ymax;
    }
};


struct Matrix{
    double fields[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};

    Matrix(int fields1[3],int fields2[3],int fields3[3]){
        for(int i = 0; i < 3; i++)
                this->fields[0][i] = fields1[i];
        for(int i = 0; i < 3; i++)
                this->fields[1][i] = fields2[i];
        for(int i = 0; i < 3; i++)
                this->fields[2][i] = fields3[i];
    }

    Matrix(int a, int b, int c, int d, int e, int f, int g, int h, int i){
        this->fields[0][0] = a;
        this->fields[0][1] = b;
        this->fields[0][2] = c;
        this->fields[1][0] = d;
        this->fields[1][1] = e;
        this->fields[1][2] = f;
        this->fields[2][0] = g;
        this->fields[2][1] = h;
        this->fields[2][2] = i;
    }

    Matrix(){}

    Matrix(double el){
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                fields[i][j] = el;
    }

    Matrix operator*(const int second[3]){
        Matrix tmp(0);

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++)
                tmp.fields[i][2] += 1.0*fields[i][j] * second[j];
        }
        return tmp;
    }

    Matrix operator*(const Matrix second){
        Matrix tmp(0);
        double temp;

        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++){
                temp = 0;
                for(int k = 0; k < 3; k++)
                    temp += fields[i][k] * second.fields[k][j];
                tmp.fields[i][j] = temp;
            }

        return tmp;
    }

    Matrix& operator=(const Matrix& tmp){
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                fields[i][j] = tmp.fields[i][j];

        return *this;
    }

    Point getLstClmn(){
        return *new Point((int)round(fields[0][2]), (int)round(fields[1][2]));
    }

    bool isInt(){
        double absoluteX = std::abs(fields[0][2]);
        double absoluteY = std::abs(fields[1][2]);

        if(absoluteX == floor(absoluteX) && absoluteY == floor(absoluteY))
            return true;
        else
            return false;
    }
};

#endif // STRUCTURES_H
