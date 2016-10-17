#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include "Shapes.h"
#include <vector>


#endif // MEDIA_H_INCLUDED

class Media {
public :
    virtual double area() = 0;

private:

};

double sumOfAreas(std::vector<Media *> media);

class ShapeMedia : public Media {
public :
    ShapeMedia(Shape *s): shape(s) {}

    double area() {
        return shape->area();
    }

private :
    Shape *shape;

};

class ComboMedia : public Media {
public :
    ComboMedia(std::vector<Media *> cm):comboShape(cm) {}

    double area() {
        return sumOfAreas(comboShape);
    }

    void add(Media *media) {
        comboShape.push_back(media);
    }
private :
    std::vector<Media *> comboShape;
};

double sumOfAreas(std::vector<Media *> media) {
    double total =0;
    for (Media *r : media)
        total += r->area();
    return total;
}

