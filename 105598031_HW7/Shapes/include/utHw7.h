#ifndef UTHW7_H_INCLUDED
#define UTHW7_H_INCLUDED
#include <string>
#include <iostream>
#include "Parser.h"
#include "CommandManager.h"
#include "Command.h"

// Problem 2-1
// Use CommandManager to control ExecuteCMD

TEST(ExecuteCMD, CommandManager) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    std::vector<Media *> sm{&c1};
    ComboMedia cm(sm);

    Command *c = new AddCommand(&r1, &cm);
    CommandManager manager;
    manager.ExecuteCMD(c);

    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv.getDescription());

}

// Problem 2-2
// Use CommandManager to control UndoCMD

TEST(UndoCMD, CommandManager) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    std::vector<Media *> sm{&c1};
    ComboMedia cm(sm);

    Command *c = new AddCommand(&r1, &cm);
    CommandManager manager;
    manager.ExecuteCMD(c);
    manager.UndoCMD();

    // Check the description of shpaeMedia
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) )") == dv.getDescription());
}

// Problem 2-3
// Use CommandManager to control RedoCMD

TEST(RedoCMD, CommandManager) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    std::vector<Media *> sm{&c1};
    ComboMedia cm(sm);

    Command *c = new AddCommand(&r1, &cm);
    CommandManager manager;
    manager.ExecuteCMD(c);
    manager.UndoCMD();
    manager.RedoCMD();

    // Check the description of shpaeMedia
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv.getDescription());
}

// Problem 3-1
// Implement undo/redo definition shapeMedia.

TEST(defineShapeMedia, UndoRedo ) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    vector<Media *> m;

    DefineCommand dc1(&m, &c1);
    dc1.Execute();
    DefineCommand dc2(&m, &r1);
    dc2.Execute();

    dc1.Undo();
    DescriptionVisitor dv;
    m[1]->accept(&dv);
    CHECK(string("r(1 2 3 4) ") == dv.getDescription());
    DOUBLES_EQUAL(1, m.size(), 0.01);

    dc1.Execute();
    DescriptionVisitor dv2;
    m[0]->accept(&dv2);
    CHECK(string("c(2 1 1) ") == dv2.getDescription());
    DOUBLES_EQUAL(2, m.size(), 0.01);
}


// Problem 3-2
// Implement undo/redo definition comboMedia.

TEST(defineComboMedia, UndoRedo ) {

    ShapeMedia c1(new Circle(2,1,1));
    ComboMedia cm;
    cm.add(&c1);
    vector<Media *> m;

    DefineCommand dc1(&m, &c1);
    dc1.Execute();
    DefineCommand dc2(&m, &cm);
    dc2.Execute();

    dc2.Undo();
    DescriptionVisitor dv;
    m[0]->accept(&dv);
    CHECK(string("c(2 1 1) ") == dv.getDescription());
    DOUBLES_EQUAL(1, m.size(), 0.01);

    dc2.Execute();
    DescriptionVisitor dv2;
    m[1]->accept(&dv2);
    CHECK(string("combo(c(2 1 1) )") == dv2.getDescription());
    DOUBLES_EQUAL(2, m.size(), 0.01);
}

// Problem 4-1
// Implement undo/redo adding shapeMedia into comboMedia.

TEST(addShapeMediaIntoComboMedia, UndoRedo) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    std::vector<Media *> sm{&c1};
    ComboMedia cm(sm);

    Command *c = new AddCommand(&r1, &cm);
    c->Execute();

    // Check the description of undo add ShapeMedia to ComboMedia
    c->Undo();
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) )") == dv.getDescription());

    // Check the description of redo add ShapeMedia to ComboMedia
    c->Execute();
    DescriptionVisitor dv2;
    cm.accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv2.getDescription());
}

// Problem 4-2
// Implement undo/redo adding comboMedia into comboMedia.

TEST(addComboMediaIntoComboMedia, UndoRedo) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    std::vector<Media *> sm{&c1};
    ComboMedia cm(sm);
    cm.add(&r1);

    ShapeMedia c2(new Circle(2,2,2));
    std::vector<Media *> sm2{&c2};
    ComboMedia cm2(sm2);
    cm2.add(&r1);

    Command *c = new AddCommand(&cm2, &cm);
    c->Execute();

    // Check the description of undo add ComboMedia to ComboMedia
    c->Undo();
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv.getDescription());

    // Check the description of redo add ComboMedia to ComboMedia
    c->Execute();
    DescriptionVisitor dv2;
    cm.accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) combo(c(2 2 2) r(1 2 3 4) ))") == dv2.getDescription());
}

// Problem 5-1
// Implement undo/redo delete shapeMedia from comboMedia

TEST(deleteShapeMediaFromComboMedia, UndoRedo) {

    // Define comboMedia
    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    ComboMedia cm;
    cm.add(&c1);
    cm.add(&r1);

    // Create a Command object
    Command *c = new DeleteFromCommand(&r1, &cm, 1);
    c->Execute();

    //Before undo delete
    DescriptionVisitor dv3;
    cm.accept(&dv3);
    CHECK(string("combo(c(2 1 1) )") == dv3.getDescription())

    // Undo the Command and get the undo description of comboMedia
    c->Undo();
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv.getDescription());

    // Redo the Command and get the redo description of comboMedia
    c->Execute();
    DescriptionVisitor dv2;
    cm.accept(&dv2);
    CHECK(string("combo(c(2 1 1) )") == dv2.getDescription());

}

// Problem 5-2
// Implement undo/redo delete comboMedia from comboMedia

TEST(deleteComboMediaFromComboMedia, UndoRedo) {

    // Define comboMedia1
    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    ComboMedia cm;
    cm.add(&c1);
    cm.add(&r1);

    // Define comboMedia2
    ShapeMedia c2(new Circle(2,2,2));
    ComboMedia cm2;
    cm2.add(&r1);
    cm2.add(&c2);

    // Add cm2 to cm
    cm.add(&cm2);

    // Create a Command object
    Command *c = new DeleteFromCommand(&cm2, &cm, 2);
    c->Execute();

    //Before undo delete
    DescriptionVisitor dv3;
    cm.accept(&dv3);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv3.getDescription())

    // Undo the Command and get the undo description of comboMedia
    c->Undo();
    DescriptionVisitor dv;
    cm.accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) combo(r(1 2 3 4) c(2 2 2) ))") == dv.getDescription());


    // Redo the Command and get the redo description of comboMedia
    c->Execute();
    DescriptionVisitor dv2;
    cm.accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv2.getDescription());
}


// Problem 5-3
// Implement undo delete shapeMedia

TEST(deleteShapeMedia, Undo) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    ComboMedia cm;
    vector<Media *> m;
    m.push_back(&c1);
    m.push_back(&r1);
    m.push_back(&cm);
    cm.add(&c1);
    cm.add(&r1);

    map<Media*, int> del;
    del.insert(std::pair<Media*,int>(m[2], 1));

    Command *c = new DeleteCommand(&m, &r1, 1 , del);
    c->Execute();
     // The size of vector should become 2
    DOUBLES_EQUAL(2, m.size(), 0.01);

    // r1 has disappear in cm
    DescriptionVisitor dv3;
    m[1]->accept(&dv3);
    CHECK(string("combo(c(2 1 1) )") == dv3.getDescription());

    c->Undo();
    // r1 has come back to vector
    DescriptionVisitor dv;
    m[1]->accept(&dv);
    CHECK(string("r(1 2 3 4) ") == dv.getDescription());

    // r1 has come back to cm
    DescriptionVisitor dv2;
    m[2]->accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv2.getDescription());
}

// Problem 5-4
// Implement Redo delete shapeMedia

TEST(deleteShapeMedia, Redo) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    ComboMedia cm;
    vector<Media *> m;
    m.push_back(&c1);
    m.push_back(&r1);
    m.push_back(&cm);
    cm.add(&c1);
    cm.add(&r1);

    map<Media*, int> del;
    del.insert(std::pair<Media*,int>(m[2], 1));

    Command *c = new DeleteCommand(&m, &r1, 1 , del);
    c->Execute();
    c->Undo();
    c->Execute();

    // The size of vector should become 2
    DOUBLES_EQUAL(2, m.size(), 0.01);

    DescriptionVisitor dv;
    m[1]->accept(&dv);
    CHECK(string("combo(c(2 1 1) )") == dv.getDescription());
}

// Problem 5-5
// Implement Undo delete comboMedia

TEST(deleteComboMedia, Undo) {

    // Define media
    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    ComboMedia cm;
    ComboMedia cm2;
    vector<Media *> m;
    m.push_back(&c1);
    m.push_back(&r1);
    m.push_back(&cm);
    m.push_back(&cm2);
    cm.add(&c1);
    cm.add(&r1);
    cm2.add(&c1);
    cm.add(&cm2);

    map<Media*, int> del;
    del.insert(std::pair<Media*,int>(&cm, 2));

    Command *c = new DeleteCommand(&m, &cm2, 3, del);

    // Delete the combomedia
    c->Execute();
    DescriptionVisitor dv;
    m[2]->accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv.getDescription());
    DOUBLES_EQUAL(3, m.size(), 0.01);

    // Undo delete the comboMedia
    c->Undo();
    DescriptionVisitor dv2;
    m[2]->accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) combo(c(2 1 1) ))") == dv2.getDescription());
    DOUBLES_EQUAL(4, m.size(), 0.01);

}

// Problem 5-6
// Implement Redo delete comboMedia

TEST(deleteComboMedia, Redo) {

    ShapeMedia c1(new Circle(2,1,1));
    ShapeMedia r1(new Rectangle(1,2,3,4));
    ComboMedia cm;
    ComboMedia cm2;
    vector<Media *> m;
    m.push_back(&c1);
    m.push_back(&r1);
    m.push_back(&cm);
    m.push_back(&cm2);
    cm.add(&c1);
    cm.add(&r1);
    cm2.add(&c1);
    cm.add(&cm2);

    map<Media*, int> del;
    del.insert(std::pair<Media*,int>(&cm, 2));

    // Before execute the delete command
    DescriptionVisitor dv2;
    m[2]->accept(&dv2);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) combo(c(2 1 1) ))") == dv2.getDescription());

    Command *c = new DeleteCommand(&m, &cm2, 3, del);
    c->Execute();

    c->Undo();
    c->Execute();
    DescriptionVisitor dv;
    m[2]->accept(&dv);
    CHECK(string("combo(c(2 1 1) r(1 2 3 4) )") == dv.getDescription());

}
#endif // UTHW7_H_INCLUDED
