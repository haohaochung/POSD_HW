#ifndef MEDIAVISITOR_H_INCLUDED
#define MEDIAVISITOR_H_INCLUDED

class ShapeMedia;
class ComboMedia;
class TextMedia;

class MediaVisitor {
public :
    virtual void visitShapeMedia(ShapeMedia *sm){}
    virtual void visitComboMedia(ComboMedia *cm){}
    virtual void visitTextMedia(TextMedia *tm){}
private:

};

class AreaVisitor: public MediaVisitor {
public :

    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm);
    void visitTextMedia(TextMedia *tm);


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
    void visitTextMedia(TextMedia *tm);


    double getPerimeter() const {
        return perimeter;
    }

private:
    double perimeter;
};

class DescriptionVisitor : public MediaVisitor {
public :
    void visitShapeMedia(ShapeMedia *sm);
    void visitComboMedia(ComboMedia *cm);
    void visitTextMedia(TextMedia *tm);


    string getDescription() {
        return description;
    }
private :
    string description;
};
#endif // MEDIAVISITOR_H_INCLUDED
