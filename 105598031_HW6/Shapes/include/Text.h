#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

class Text {
public : Text(Rectangle boundingbox, string text):r(boundingbox),t(text){}

    Rectangle* getBoundingBox() { return &r; };
    string text() const { return t; };

private :
    Rectangle r;
    string t;
};

#endif // TEXT_H_INCLUDED
