#ifndef UTHW4_H_INCLUDED
#define UTHW4_H_INCLUDED

#include<stack>
// Problem 1
// Use ShapeMediaBuilder to build a Circle ShapeMedia
TEST(shapeMedia, MediaBuilder) {

    ShapeMediaBuilder smb;
    Circle c1(0,0,5);
    smb.buildShapeMedia(&c1);

    DescriptionVisitor dv;
    Media* m  =smb.getMedia();
    m->accept(&dv);
    CHECK(string("c(0 0 5) ") == dv.getDescription());
}

// Problem 2
// Use ComboMediaBuilder to build a MultiLayer ComboMedia

TEST(comboMedia, MediaBuilder) {

    // build third layer comboMedia -> r1 & c1
    ComboMediaBuilder cmb;
    cmb.buildComboMedia();

    Rectangle r1(10,0,15,5);
    cmb.buildShapeMedia(&r1);
    Circle c1(12,5,2);
    cmb.buildShapeMedia(&c1);
    Media *cm = cmb.getMedia(); //comboMedia(r1, c1)


    // build second layer comboMedia -> layer3 & r2
    ComboMediaBuilder cmb2;
    cmb2.buildComboMedia();
    cmb2.buildAddComboMedia(cm);

    Rectangle r2(0,0,25,20);
    cmb2.buildShapeMedia(&r2);
    Media* cm2 = cmb2.getMedia(); // comboMedia (comboMedia(r1, c1), r1)

    // build first layer comboMedia -> layer2 & t1
    ComboMediaBuilder cmb3;
    cmb3.buildComboMedia();
    cmb3.buildAddComboMedia(cm2);

    Triangle t1(0,20,16,32,25,20);
    cmb3.buildShapeMedia(&t1);
    Media* cm3 = cmb3.getMedia(); // comboMedia (comboMedia (comboMedia(r1, c1), r1), t1)

    DescriptionVisitor dv;
    cm3->accept(&dv);
    CHECK(string("combo(combo(combo(r(10 0 15 5) c(12 5 2) )r(0 0 25 20) )t(0 20 16 32 25 20) )") == dv.getDescription());
}

// Problem 3
// Add TextMedia class inheriting from the Media interface

TEST(textMedia, MediaBuilder) {

    Rectangle r1(0,0,4,2);
    string text = "I am a boundingBox text";
    Text t(r1, text);
    TextMedia tm(&t);

    // assert 3 visitor of TextMedia
    DescriptionVisitor dv;
    tm.accept(&dv);
    CHECK(text == dv.getDescription());

    AreaVisitor av;
    tm.accept(&av);
    DOUBLES_EQUAL(8, av.getArea(), 0.0001);

    PerimeterVisitor pv;
    tm.accept(&pv);
    DOUBLES_EQUAL(12, pv.getPerimeter(), 0.0001);
}

// Problem 4
// Write remove function for ComboMedia
TEST(removeMedia, MediaBuilder) {

    Rectangle r1(10,0,15,5);
    ShapeMedia sm1(&r1);
    Circle c1(12,5,2);
    ShapeMedia sm2(&c1);
    std::vector<Media *> shapeMedia1{&sm1, &sm2};
    ComboMedia cm1(shapeMedia1);

    Rectangle r2(0,0,25,20);
    ShapeMedia sm3(&r2);
    std::vector<Media *> shapeMedia2{&cm1, &sm3};
    ComboMedia cm2(shapeMedia2);

    Triangle t1(0,20,16,32,25,20);
    ShapeMedia sm4(&t1);
    std::vector<Media *> shapeMedia3{&cm2, &sm4};
    ComboMedia cm3(shapeMedia3);

    cm3.removeMedia(&sm3); // remove r(0 0 25 20)
    DescriptionVisitor dv;
    cm3.accept(&dv);
    CHECK(string("combo(combo(combo(r(10 0 15 5) c(12 5 2) ))t(0 20 16 32 25 20) )") == dv.getDescription());

}


#endif // UTHW4_H_INCLUDED
