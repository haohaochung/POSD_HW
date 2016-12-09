#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"

#include "Shapes.h"
#include "Media.h"
#include "MediaVisitor.h"
#include "MediaBuilder.h"
#include "Text.h"
#include <vector>
#include <iostream>

#include "utHw4.h"


const double epsilon = 0.0001;
using namespace std;
// added this line
TEST (first, Rectangle) {
    Rectangle rect(0,0,4,2);
    DOUBLES_EQUAL(8, rect.area(),epsilon);
    DOUBLES_EQUAL(12, rect.perimeter(), epsilon);
}

TEST(second, Circle) {
    Circle circ(0,0,10);
    DOUBLES_EQUAL(300, circ.area(), epsilon);
    DOUBLES_EQUAL(60, circ.perimeter(), epsilon);
}

TEST(third, Triangle) {
    Triangle tri(0,0,0,1,1,0);
    DOUBLES_EQUAL(3.41421, tri.perimeter(), epsilon);
    DOUBLES_EQUAL(0.5, tri.area(), epsilon);
}

TEST(fourth, sumOfPerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,0,1,1,0);

    std::vector<Shape *> peris;
    peris.push_back(&r1);
    peris.push_back(&c1);
    peris.push_back(&t1);

    DOUBLES_EQUAL(75.41421, sumOfPerimeter(peris), epsilon);
}


TEST(comboMedia , MediaVisitor){
    Rectangle r1(0,0,2,2*sqrt(3));
    Triangle t1(0,0,-1,sqrt(3),0,2*sqrt(3));
    Triangle t2(2,0,3,sqrt(3),2,2*sqrt(3));

    ShapeMedia media(&r1);
    ShapeMedia media2(&t1);
    ShapeMedia media3(&t2);

    // assert shape step by step.
    std::vector<Media *> shapeMedia1{&media};
    ComboMedia comboMedia1(shapeMedia1);
    comboMedia1.add(&media2);

    std::vector<Media *> shapeMedias{&comboMedia1};
    ComboMedia comboMedia2(shapeMedias);
    comboMedia2.add(&media3);

    AreaVisitor av;
    PerimeterVisitor pv;
    DescriptionVisitor dv;
    comboMedia2.accept(&av);
    comboMedia2.accept(&pv);
    comboMedia2.accept(&dv);

    DOUBLES_EQUAL(6*sqrt(3), av.getArea(), epsilon);
    DOUBLES_EQUAL(12+8*sqrt(3), pv.getPerimeter(), epsilon);
    //cout<<dv.getDescription();

}

#endif // UTSHAPES_H_INCLUDED
