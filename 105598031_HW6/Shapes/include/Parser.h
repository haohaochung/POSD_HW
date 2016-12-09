#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>
#include <stdlib.h>

using namespace std;

class Parser {

public:
    void textUI() {
        while (true) {

            char str[100];
            cout<< ":- ";
            cin.getline(str, 100);
            char *pch;
            const char *delimiters = " =,().{}";
            pch = strtok(str, delimiters);

            while(pch!=NULL) {
                v.push_back(pch);
                pch = strtok(NULL, delimiters);
            }

            if(v[0]== "def") {
                try {
                    if(v[2] == "combo")
                    //if(v[2].substr(0,6) == "combo{" && v.back().substr(last-1,1) == "}")
                         defineComboMedia();
                    else if(v[2]== "Triangle" || v[2] == "Rectangle" || v[2] == "Circle" )
                        cout<<defineShapeMedia()<<endl;
                    else
                        cout << " Error define" << endl;

                } catch (string s) {
                    cout << s << endl;
                }
            }

            else if(v[0] == "save" && v[2] == "to") {
                try {
                    if(v[3].substr(0,1) == "\"" && v[4]== "txt\"" )
                        cout << saveMedia(v[1], v[3].substr(1)) << endl;
                    else
                        cout<< "Save file need to obey rule \" \" and should be .txt file" <<endl;
                } catch (string s) {
                    cout << s <<endl;
                }
            }

            else if(v[0] == "load") {
                try {
                    if(v[1].substr(0,1) == "\"" && v[2] == "txt\"" ) {
                        string fileName = v[1].substr(1);
                        cout<< loadMedia(fileName) << endl;
                    }
                    else
                        cout<< "Load file need to obey rule \" \" and should be .txt file" <<endl;
                } catch (string s) {
                    cout << s << endl;
                }
            }

            else if(v[0] == "show")
                 showMedia();

            else if(v[0] == "add" && v[2] == "to") {
                 try {
                    addMedia();
                 } catch (string s) {
                    cout << s <<endl;
                 }
            }

            else if (v[0] == "delete") {
                 try {
                    deleteMedia();
                 } catch (string s) {
                    cout << s <<endl;
                 }
            }

            else if(v[1] == "perimeter?" || v[1] == "area?" ) {
                try {
                    cout<<calculateAreaOrPeri(v[0], v[1])<<endl;
                } catch (string s) {
                    cout<< s <<endl;
                }
            }

            else
                cout << "Invaild input" << endl;
            v.clear(); //Initialization
        }
    }

    void showMedia() {
        for (Media *mm : mb)
            cout << mm->getName()<<endl;
    }

    void addMedia() {
        stringstream ss;
        Media *dest = 0;
        Media *target =0;
        for(Media *mm : mb) {
            if(v[1] == mm->getName())
                target = mm;
            if(v[3] == mm->getName())
                dest = mm;
        }
        if(!target || !dest) throw string("Shape didn't exist.");

        dest->add(target);
        DescriptionVisitor dv;
        NameVisitor nv;
        dest->accept(&dv);
        dest->accept(&nv);
        ss << v[3] << " = " <<  nv.getName() << " = " << dv.getDescription();
        cout<< ss.str() <<endl;
    }

    void deleteMedia() {
        Media *del = 0;
        Media *from = 0;

        if(v[2] == "from") {
            for(Media *mm : mb) {
                if(v[1] == mm->getName())
                    del = mm;
                if(v[3] == mm->getName()) {
                    from = mm;
                }
            }
            if(!del || !from) throw string("The shape did't exist so can not delete");
            from->removeMedia(del);
        }
        else {
            int n =0;
            bool exist = false;
            for(Media *mm : mb) {
                if(v[1] == mm->getName()) {
                    mb.erase(mb.begin()+n);
                    del = mm;
                    exist = true;
                }
                n++;
            }
            if(exist == true) {
                for(Media *m : mb)
                    m->removeMedia(del);
            }
        }
    }

    string saveMedia(string mediaName, string fileName) {
        stringstream ss;
        ofstream fout(fileName+".txt");
        Media *target = 0;

        for(Media *mm : mb) {
            if(mediaName == mm->getName()) {
                target = mm;
                break;
            }
        }
        if(!target) throw string("THis shape name did't exist.");
        DescriptionVisitor dv;
        NameVisitor nv;
        target->accept(&dv);
        target->accept(&nv);

        fout<< dv.getDescription() <<"\n"  << nv.getName() ;
        ss << mediaName << " saved to " << fileName <<  ".txt" ;
        return ss.str();
    }

    string loadMedia(string fileName) {
        string fileContent;
        stringstream ss;
        try {
            Document *doc = new MyDocument;
            fileContent = doc->openDocument(fileName+".txt");
            size_t found = fileContent.find(",", 0);
            string content1 = fileContent.substr(0, found); // ex combo(c(1 2 3) r(1 2 3 4))
            string content2 = fileContent.substr(found+1, fileContent.size()- found -3); // real name

            //convert string to char *
            char *cstr = new char[content2.length() + 1];
            strcpy(cstr, content2.c_str());

            char *pch;
            const char *delimiters = " {}";
            vector<string> shapeName;
            pch = strtok(cstr, delimiters);

            while(pch!=NULL) {
                shapeName.push_back(pch);
                pch = strtok(NULL, delimiters);
            }
            delete [] cstr;
            int shapeNameCount = shapeName.size();
            for(Media *mm : mb) {
                for(int i=0 ; i<shapeNameCount; i++) {
                    if(shapeName[i] == mm->getName()) {
                        throw string("Already have this shape name");
                        break;
                    }
                }
            }
            MediaDirector md;
            std::stack<MediaBuilder*> builder; //object
            md.setMediaBuilder(&builder);
            md.concrete(content1);
            Media *m = builder.top()->getMedia();

            SetNameVisitor snv(shapeName);
            DescriptionVisitor dv;
            NameVisitor nv;
            CreateShapeVisitor csv(mb);
            m->accept(&snv);
            m->accept(&dv);
            m->accept(&nv);
            m->accept(&csv);

            mb = csv.getMediaVector();

            ss << "loading " << fileName << ".txt ..." <<"\n";
            ss << shapeName[0] << " = "  << nv.getName() << "= " << dv.getDescription();

        } catch (string s) {
            cout << s <<endl;
        }
        return ss.str();
//return "c";
    }

    string defineShapeMedia() {

        string mediaName = v[1];
        stringstream ss;
        ShapeMediaBuilder sm;

        if(v[2] == "Triangle" && v.size()>8 ) {
            double fx = atof(v[3].c_str());
            double fy = atof(v[4].c_str());
            double sx = atof(v[5].c_str());
            double sy = atof(v[6].c_str());
            double ty = atof(v[7].c_str());
            double tx = atof(v[8].c_str());

            for(Media* mm : mb) {
                if(mediaName == mm->getName()) {
                    throw string("Already have this shape name");
                    break;
                }
            }
            sm.buildShapeMedia(new Triangle(fx, fy, sx, sy, tx, ty));
            ss << ">> Triangle(" << v[3] << "," << v[4] << "," << v[5] << "," << v[6] << "," << v[7] << "," << v[8] << ")";
        }

        else if(v[2] == "Circle" && v.size()>5) {
            double cx = atof(v[3].c_str());
            double cy = atof(v[4].c_str());
            double r = atof(v[5].c_str());

            for(Media* mm : mb) {
                if(mediaName == mm->getName()) {
                    throw string("Already have this shape name");
                    break;
                }
            }
            sm.buildShapeMedia(new Circle(cx, cy, r));
            ss << ">> Circle(" << v[3] << "," << v[4] << "," << v[5] << ")";
        }

        else if(v[2] == "Rectangle" && v.size()>6) {
            double x = atof(v[3].c_str());
            double y = atof(v[4].c_str());
            double l = atof(v[5].c_str());
            double w = atof(v[6].c_str());


            for(Media* mm : mb) {
                if(mediaName == mm->getName()) {
                    throw string("Already have this shape name");
                    break;
                }
            }
            sm.buildShapeMedia(new Rectangle(x, y, l, w));
            ss << ">> Rectangle(" << v[3] << "," << v[4] << "," << v[5] << "," <<v[6]<<")";
        }

        else {
            throw string("Can not define Shape (Wrong Shape Name or parameters)");
        }

        sm.getMedia()->setName(v[1]);
        mb.push_back(sm.getMedia());

        return ss.str();
    }

    void defineComboMedia() {

        string comboMediaName = v[1];
        vector<string> name;
        stringstream ss;
        int j =0;
        int len = v.size();
        for(int i =3 ; i<len ; i++) {
            name.push_back(v[i]);
            j++;
        }

        ComboMediaBuilder cm ;
        cm.buildComboMedia();
        int nameLen = name.size();

        for(Media *mm : mb) {
            for(int i =0; i< nameLen ; i++) {
                if(name[i] == mm->getName()) {
                    cm.buildAddComboMedia(mm);
                }
            }
        }
        cm.getMedia()->setName(v[1]);
        mb.push_back(cm.getMedia());
    }

    string calculateAreaOrPeri(string mediaName, string mediaCalculate) {

        string name = mediaName;
        string calculate = mediaCalculate;
        stringstream ss;
        Media *target = 0;

        for(Media* mm : mb) {
            if(name == mm->getName()) {
                target = mm;
                break;
            }
        }

        if(!target) throw std::string("Target is not found.");

        if(calculate == "perimeter?") {
            PerimeterVisitor *pv = new PerimeterVisitor;
            target->accept(pv);
            ss <<">> "<<pv->getPerimeter();
        }

        else if (calculate == "area?") {
            AreaVisitor *av = new AreaVisitor;
            target->accept(av);
            ss <<">> "<<av->getArea();
        }

        else {

            throw std::string("Input error");
        }
        return ss.str();
    }

private:
    vector<string> v;
    vector<Media *> mb;
};

#endif // PARSER_H
