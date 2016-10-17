#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include "Shapes.h"
#include "MediaVisitor.h"

#include <vector>


#endif // MEDIA_H_INCLUDED

class Media {
public :
    virtual double area() = 0;
    virtual double perimeter() = 0;

    //Because ShapeMedia didn't have accept(), we can't assign value to this method.
    virtual void accept(MediaVisitor *mv){}

private:

};

double sumOfAreas(std::vector<Media *> media);
double sumOfPerimeters(std::vector<Media *> media) ;

class ShapeMedia : public Media {
public :
    ShapeMedia(Shape *s): shape(s) {}

    double area() {
        return shape->area();
    }

    double perimeter() {
        return shape->perimeter();
    }

    void accept(MediaVisitor *mv){
        mv->visitShapeMedia(this);
    }

    Shape *getShape() const {return shape;}

private :
    Shape *shape;

};

class ComboMedia : public Media {
public :
    ComboMedia(std::vector<Media *> cm):comboShape(cm) {}

    double area() {
        return sumOfAreas(comboShape);
    }

    double perimeter() {
        return sumOfPerimeters(comboShape);
    }

    void add(Media *media) {
        comboShape.push_back(media);
    }

    void accept(MediaVisitor *mv) {
        for (Media *m :comboShape) {
            m->accept(mv);
        }
        mv->visitComboMedia(this);
    }

private :
    std::vector<Media *> comboShape;
};

double sumOfAreas(std::vector<Media *> media) {
    double total = 0;
    for (Media *a : media)
        total += a->area();
    return total;
}

double sumOfPerimeters(std::vector<Media *> media) {
    double total = 0;
    for (Media *p : media) {
        total+= p->perimeter();
    }
    return total;
}


void AreaVisitor::visitShapeMedia(ShapeMedia *sm) {
    area += sm->getShape()->area();
}

void AreaVisitor::visitComboMedia(ComboMedia *cm) {

}

void PerimeterVisitor::visitShapeMedia(ShapeMedia *sm) {
    perimeter += sm->getShape()->perimeter();

}

void PerimeterVisitor::visitComboMedia(ComboMedia *cm) {

}




