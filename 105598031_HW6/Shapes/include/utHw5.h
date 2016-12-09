#ifndef UTHW5_H_INCLUDED
#define UTHW5_H_INCLUDED

#include "Document.h"
#include "MediaDirector.h"

//Problem 1
//Use MyDocument to load from the file myShape.txt

TEST(readFile, FileIO) {

    try {
        Document *doc = new MyDocument;
        std::string s = "combo(r(0 0 3 2) c(0 0 5) combo(r(0 0 5 4) c(0 0 10) )combo(r(0 1 8 7) c(0 1 10) ))";
        CHECK(s == doc->openDocument("myShape.txt"));
    }
    catch (std::string s) {
        CHECK(std::string("file is not existed.") == s);
                cout<<"The file did no exist"<<endl;

    }
}

// Problem 2
// Use MediaDirector class to handle the contents (buildComboMedia)

TEST(buildComboMedia, MediaDirector) {

    try {
        Document *doc = new MyDocument;
        MediaDirector md;
        std::stack<MediaBuilder*> mb; //object
        md.setMediaBuilder(&mb);
        std::string s = doc->openDocument("myShape.txt");
        md.concrete(s);

        DescriptionVisitor dv;
        mb.top()->getMedia()->accept(&dv);
        CHECK(s == dv.getDescription());
    }
    catch (std::string s) {
        CHECK(std::string("file is not existed.") == s);
        cout<<"The file did no exist"<<endl;
    }

}


// Problem 2
// Use MediaDirector class to handle the contents (buildShapeMedia)

TEST(buildShapeMedia, MediaDirector) {

    try {
        Document *doc = new MyDocument;
        MediaDirector md;
        std::stack<MediaBuilder*> mb; //object
        md.setMediaBuilder(&mb);
        std::string s = doc->openDocument("shape.txt"); // r(0 0 1 0)
        md.concrete(s);

        DescriptionVisitor dv;
        mb.top()->getMedia()->accept(&dv);
        CHECK(s == dv.getDescription());
    }
    catch (std::string s) {
        CHECK(std::string("file is not existed.") == s);
        cout<<"The file did no exist"<<endl;
    }

}

#endif // UTHW5_H_INCLUDED
