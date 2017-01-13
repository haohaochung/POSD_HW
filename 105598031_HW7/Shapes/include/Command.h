#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

class Command {

public :
    Command(){}
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual void Redo(){}
};

class AddCommand : public Command {
public :
    AddCommand(Media *t, Media *d):  target(t), dest(d){}
    void Execute(){
        dest->add(target);
    }

    void Undo(){
        dest->removeMedia(target);
    }

private :
    Media *target;
    Media *dest;
};

class DefineCommand : public Command {
public :
    DefineCommand(vector<Media*> *mediaVector, Media *media): mv(mediaVector), m(media){}

    void Execute(){
        mv->push_back(m);
    }
    void Undo(){
        mv->pop_back();
    }

private:
    vector<Media*> *mv; // media vector's point
    Media *m;
};

class DeleteCommand : public Command {
public :
    DeleteCommand(vector<Media*> *mediaVector, Media *del, int deleteIndex, map<Media*, int> mapMedia)
    : mv(mediaVector), dm(del), index(deleteIndex), mm(mapMedia){}

    void Execute(){
        mv->erase(mv->begin()+index);
        for(Media *m :*mv) {
            m->removeMedia(dm);
        }
    }

    void Undo(){
        for(Media *m : *mv) {
            for(auto mapMedia : mm) {
                if(m->getName() == mapMedia.first->getName()){
                    m->addSpecificPosition(dm, mapMedia.second);
                    break;
                }
            }
        }
        mv->insert(mv->begin()+index, dm);

    }

private:
    vector<Media*> *mv; // media vector's point
    Media *dm;
    int index;
    map<Media*, int> mm;
};

class DeleteFromCommand : public Command {
public:
    DeleteFromCommand(Media *del, Media *from, int deleteIndex): dm(del), fm(from), index(deleteIndex){}

    void Execute(){
        fm->removeMedia(dm);
    }

    void Undo(){
        fm->addSpecificPosition(dm, index);
    }

private:
    Media *dm;
    Media *fm;
    int index;
};

#endif // COMMAND_H_INCLUDED
