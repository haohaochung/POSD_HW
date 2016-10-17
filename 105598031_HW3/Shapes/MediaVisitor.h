#ifndef MEDIAVISITOR_H_INCLUDED
#define MEDIAVISITOR_H_INCLUDED

class ShapeMedia;
class ComboMedia;


class MediaVisitor {
public :
    virtual void visitShapeMedia(ShapeMedia *sm){}
    virtual void visitComboMedia(ComboMedia *cm){}

private:

};

class AreaVisitor: public MediaVisitor {
public :

    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm);

    double getArea() const {
        return area;
    }

private:
    double area ;

};

class PerimeterVisitor : public MediaVisitor {
public :

    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm);

    double getPerimeter() const {
        return perimeter;
    }

private:
    double perimeter;
};

#endif // MEDIAVISITOR_H_INCLUDED
