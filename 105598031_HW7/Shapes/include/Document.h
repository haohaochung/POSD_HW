#ifndef DOCUMENT_H_INCLUDED
#define DOCUMENT_H_INCLUDED

#include<iostream>
#include<fstream>
#include<string>
#include <sys/stat.h>
#include <unistd.h>

class Document {
public :
    string openDocument(const string name) {
        if(!canOpenDocument(name))
            throw std::string("file is not existed.");
        openFile(name);
        return readFile();
    }
protected :
    virtual void openFile(const string name) = 0;
    virtual bool canOpenDocument(const string name) = 0;
    virtual string readFile() = 0;
};

class MyDocument : public Document {
public :
    void openFile(const string name) {
        myFile.open(name);
    }

    bool canOpenDocument(const string name) {

        struct stat buf;
        const char *c = name.c_str();
        int exist = stat(c, &buf);
        if(exist == 0){
            return true;
        }
        else {
            return false;
        }
    }

    string readFile() {
        string multiText;
        while (getline(myFile, text)) {
            multiText+=text+",";
        }
        myFile.close();
        return multiText;
    }

private:
    ifstream myFile;
    string text;
};

#endif // DOCUMENT_H_INCLUDED
