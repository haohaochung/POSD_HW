#ifndef MEDIABUILDER_H_INCLUDED
#define MEDIABUILDER_H_INCLUDED

class MediaBuilder {
public:

    virtual void buildComboMedia() = 0;
    virtual void buildShapeMedia(Shape *s) = 0;
    virtual Media *getMedia() const = 0;


private:
    ComboMedia *combo;
};

class ShapeMediaBuilder : public MediaBuilder {
public:

    void buildComboMedia(){}
    void buildShapeMedia(Shape *s) {
        shape = new ShapeMedia(s);
    }

    Media *getMedia() const { return shape; }

private :
    ShapeMedia *shape;
};

class ComboMediaBuilder : public MediaBuilder {
public :

    void buildComboMedia() {
        combo = new ComboMedia();
    }

    void buildShapeMedia(Shape *s) {
        combo->add(new ShapeMedia(s));
    }

    void buildAddComboMedia(Media *m) {
        combo->add(m);
    }

    Media *getMedia() const { return combo; }

private :
    ComboMedia *combo;
};

#endif // MEDIABUILDER_H_INCLUDED
