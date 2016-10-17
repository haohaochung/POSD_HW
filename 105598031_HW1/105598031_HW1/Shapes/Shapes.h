#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED

#include <vector>
#include <iostream>
using namespace std;

class Shape {
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
};

class Rectangle : public Shape {
public:
    Rectangle(double ulcx, double ulcy, double length, double width):
        x(ulcx),y(ulcy),l(length),w(width){}

    double area() {
        return l*w;
    }
    double perimeter() {
        return 2*(l+w);
    }
private:
    double x,y,l,w;
};

class Circle : public Shape{
public:
    Circle(double centerX,double centerY,double radius):
        cx(centerX),cy(centerY),r(radius){}

    double area()  {
        return pi*r*r;
    }
    double perimeter()  {
        return 2*r*pi;
    }
private:
    double cx,cy,r;
    double pi = 3;
};

class Triangle : public Shape {
public:
    Triangle(double firstPointX, double firstPointY, double secondPointX,
             double secondPointY, double thirdPointX, double thirdPointY):
            fx(firstPointX),fy(firstPointY),sx(secondPointX),sy(secondPointY),tx(thirdPointX),ty(thirdPointY){}


    bool isTriangle() {

        slide1 = sqrt(pow((fx-sx), 2) + pow((fy-sy), 2));
        slide2 = sqrt(pow((sx-tx), 2) + pow((sy-ty), 2));
        slide3 = sqrt(pow((fx-tx), 2) + pow((fy-ty), 2));


        if( (slide1+slide2+slide3) <= 2*maxium(slide1, slide2, slide3) ) {
            cout <<"Points ("<<fx<<","<<fy<<") ("<<sx<<","<<sy<<") ("<<tx<<","<<ty<<")"
                 <<" can't become a triangle."<<endl;
            return false;
        }
        else {return true;}
    }

    double perimeter() {

        if (isTriangle()) {
           return slide1 + slide2 + slide3;
        }
        else {
            return 0;
        }
    }

    double area() {
        double s = perimeter() / 2;
        return sqrt(s*(s-slide1)*(s-slide2)*(s-slide3));
    }

    double maxium(double a, double b, double c) {
        double maxium = a;
        if (b>=maxium){maxium = b;}
        if (c>=maxium) {maxium = c;}

        return maxium;
    }

private:
    double fx,fy,sx,sy,tx,ty;
    double slide1, slide2, slide3;
};

double sumOfPerimeter(std::vector<Shape *> peris) {

    double total = 0;
    for(Shape *p : peris)
        total += p->perimeter();
    return total;
}

double sumOfArea(std::vector<Rectangle> rects) {
    double total =0;
    for (Rectangle r: rects)
        total += r.area();
    return total;
}

double sumOfArea(std::vector<Shape *> rects) {
    double total =0;
    for (Shape *r: rects)
        total += r->area();
    return total;
}

#endif // SHAPES_H_INCLUDED
