#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include "Shapes.h"
#include "Text.h"
#include "MediaVisitor.h"

#include <vector>


#endif // MEDIA_H_INCLUDED

class Media {
public :

    //Because ShapeMedia didn't have accept(), we can't assign value to this method.
    virtual void accept(MediaVisitor *mv){}
    virtual void removeMedia(Media *m){}


private:

};

class ShapeMedia : public Media {
public :
    ShapeMedia(Shape *s): shape(s) {}

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
    ComboMedia() {}

    void add(Media *media) {
        comboShape.push_back(media);
    }

    void removeMedia(Media *media) {

        DescriptionVisitor removeShape;
        media->accept(&removeShape);
        string removeItem = removeShape.getDescription();
        string iteration;
        int n = 0;

        for(Media *m : comboShape) {
            DescriptionVisitor iterShape;
            m->accept(&iterShape);
            iteration = iterShape.getDescription();
            //cout<<iteration<<endl;

            if(iteration != removeItem) {
                m->removeMedia(media);
            }
            else {
                comboShape.erase(comboShape.begin()+ n);
                break;
            }
            n++;
        }
    }

    void accept(MediaVisitor *mv) {
        mv->visitComboMediaPre(this);

        for (Media *m :comboShape) {
            m->accept(mv);
        }
        mv->visitComboMediaPost(this);
    }

private :
    std::vector<Media *> comboShape;
};

class TextMedia : public Media {
public :
    TextMedia(Text *t):text(t){}

    void accept(MediaVisitor *mv) {
        mv->visitTextMedia(this);
    }

    Text *getText() const { return text; };
private :
    Text *text;
};


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

void DescriptionVisitor::visitShapeMedia(ShapeMedia *sm) {
    description += sm->getShape()->description();
}

void DescriptionVisitor::visitComboMedia(ComboMedia *cm) {
    description = string("combo(")+description+string(")");
}

void AreaVisitor::visitTextMedia(TextMedia *tm) {
    area = tm->getText()->getBoundingBox()->area();
}

void PerimeterVisitor::visitTextMedia(TextMedia *tm) {
    perimeter = tm->getText()->getBoundingBox()->perimeter();
}

void DescriptionVisitor::visitTextMedia(TextMedia *tm) {
    description = tm->getText()->text();
}

// use for combo description
void DescriptionVisitor::visitComboMediaPre(ComboMedia *cm) {
    description = description + std::string("combo(");
}

void DescriptionVisitor::visitComboMediaPost(ComboMedia *cm) {
    description = description + std::string(")");

}




