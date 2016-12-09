#ifndef MEDIADIRECTOR_H_INCLUDED
#define MEDIADIRECTOR_H_INCLUDED

#include <sstream>

class MediaDirector {
public :
    void setMediaBuilder(std::stack<MediaBuilder *> *mbs){
        mb = mbs;
    }
    void concrete(string content) {
        while(!content.empty()){

            size_t pos = content.find_first_not_of(" ");
            size_t found = content.find("combo(", pos);

            if(found == pos) {
                mb->push(new ComboMediaBuilder());
                mb->top()->buildComboMedia();
                content = content.substr(pos+6);
            }

            found = content.find("r(",pos);
            if(found == pos) {
                content = content.substr(pos+2);
                std::stringstream ss;
                ss << content; // content'string gives to stringstream ss
                double ulcx, ulcy, length, width;
                ss >> ulcx >> ulcy >> length >> width;

                if(mb->empty()) {
                     mb->push(new ShapeMediaBuilder());
                     mb->top()->buildShapeMedia(new Rectangle(ulcx, ulcy, length, width));
                     break;
                }
                else
                    mb->top()->buildShapeMedia(new Rectangle(ulcx, ulcy, length, width));
                found = content.find(")", pos);
                content = content.substr(found + 1);
                continue;
            }

            found = content.find("c(", pos);
            if(found == pos) {
                content = content.substr(pos+2);
                std::stringstream ss;
                ss << content;
                double cx, cy, r;
                ss >> cx >> cy >> r;

                if(mb->empty()) {
                    mb->push(new ShapeMediaBuilder());
                    mb->top()->buildShapeMedia(new Circle(cx, cy, r));
                    break;
                }
                else
                    mb->top()->buildShapeMedia(new Circle(cx, cy, r));
                found = content.find(")", pos);
                content = content.substr(found + 1);
                continue;
            }

            found = content.find("t(", pos);
            if(found == pos) {
                content = content.substr(pos+2);
                std::stringstream ss;
                ss << content;
                double fx, fy, sx, sy, tx, ty;
                ss >> fx >> fy >> sx >> sy >> tx >>ty;

                if(mb->empty()) {
                    mb->push(new ShapeMediaBuilder());
                    mb->top()->buildShapeMedia(new Triangle(fx, fy, sx, sy , tx, ty));
                    break;
                }
                else
                    mb->top()->buildShapeMedia(new Triangle(fx, fy, sx, sy , tx, ty));
                found = content.find(")", pos);
                content = content.substr(found + 1);
                continue;
            }

            found = content.find(")", pos); //combo's end
            if(found == pos) {
                content = content.substr( found + 1); // next char is a new combo or the end.
                if(content.size()>0) {
                    Media *cm = mb->top()->getMedia();
                    mb->pop();
                    mb->top()->buildAddComboMedia(cm);
                }
                else {
                    break;
                }
            }
        }
    }

private :
    std::stack<MediaBuilder *> *mb;
};

#endif // MEDIADIRECTOR_H_INCLUDED
