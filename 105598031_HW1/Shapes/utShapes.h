#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include <vector>

const double epsilon = 0.0001;
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

TEST (third, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Rectangle r2(0,0,3,3);
    std::vector<Rectangle> rects;
    rects.push_back(r1);
    rects.push_back(r2);
    DOUBLES_EQUAL(17, sumOfArea(rects),epsilon);
}

TEST (fourth, sumOfArea) {
    std::vector<Rectangle> rects;
    DOUBLES_EQUAL(0, sumOfArea(rects),epsilon);
}

TEST (fifth, sumOfArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    std::vector<Shape *> ss;
    ss.push_back(&r1);
    ss.push_back(&c1);
    DOUBLES_EQUAL(308,sumOfArea(ss),epsilon);
}
#endif // UTSHAPES_H_INCLUDED
