#ifndef UTSHAPES_H_INCLUDED
#define UTSHAPES_H_INCLUDED

#include "..\cppunitlite\TestHarness.h"
#include "Shapes.h"
#include "Media.h"
#include <vector>

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

TEST(fifth, maxArea) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,0,1,1,0);

    std::vector<Shape *> mA;
    mA.push_back(&r1);
    mA.push_back(&c1);
    mA.push_back(&t1);
    DOUBLES_EQUAL(300, maxArea(mA), epsilon);
}

TEST(sixth, sortPerimeter) {
    Rectangle r1(0,0,4,2);
    Circle c1(0,0,10);
    Triangle t1(0,0,0,1,1,0);

    std::vector<Shape *> p;
    p.push_back(&r1);
    p.push_back(&c1);
    p.push_back(&t1);

    vector<Shape *> sortedData = sortByDecreasingPerimeter(p);
    DOUBLES_EQUAL(60, sortedData[0]->perimeter(), epsilon);
    DOUBLES_EQUAL(12, sortedData[1]->perimeter(), epsilon);
    DOUBLES_EQUAL(3.4142, sortedData[2]->perimeter(), epsilon);
}

TEST(comboShape, combo) {
    Rectangle rTall(0,0,4,2);
    Circle cSmall(0,0,10);

    std::vector<Shape *> combo{&rTall};
    ComboShape shape(combo);
    shape.add(&cSmall);
    DOUBLES_EQUAL(308, shape.area(), epsilon);
    DOUBLES_EQUAL(72, shape.perimeter(), epsilon);
}

TEST(comboMultipleComboShape, combo) {
    Rectangle rTall (0,0,4,2);
    Circle cSmall (0,0,10);

    std::vector<Shape *> combo{&rTall, &cSmall};
    std::vector<Shape *> combo2{&rTall};
    ComboShape shape(combo);
    ComboShape shape2(combo2);
    shape.add(&shape2);
    DOUBLES_EQUAL(316, shape.area(), epsilon);
    DOUBLES_EQUAL(84, shape.perimeter(), epsilon);
}

TEST(shapeMedia, media) {
    Rectangle rTall(0,0,4,2);
    ShapeMedia media(&rTall);
    DOUBLES_EQUAL(8, media.area(), epsilon);
}

TEST(comboMedia, media) {
    Rectangle rTall(0,0,4,2);
    Circle cSmall (0,0,10);

    ShapeMedia media(&rTall);
    ShapeMedia media2(&cSmall);
    std::vector<Media *> ss{&media};
    ComboMedia cm(ss);
    cm.add(&media2);
    DOUBLES_EQUAL(308, cm.area(), epsilon);

}
#endif // UTSHAPES_H_INCLUDED
