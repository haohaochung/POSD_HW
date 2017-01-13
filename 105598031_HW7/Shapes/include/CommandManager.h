#ifndef COMMANDMANAGER_H_INCLUDED
#define COMMANDMANAGER_H_INCLUDED

#include "Command.h"

class CommandManager {
public :
    CommandManager() {}
    void ExecuteCMD(Command *cmd) {
        cmd->Execute();
        undocmds.push(cmd);
    }

    void RedoCMD() {

        if(!redocmds.empty()) {
            Command *cmd = redocmds.top();
            redocmds.pop();
            undocmds.push(cmd);
            cmd->Execute();
        }
        else {
            cout<<"Can not redo"<<endl;
        }
    }

    void UndoCMD() {

        if(undocmds.size()!=0) {
            Command *cmd = undocmds.top();
            undocmds.pop();
            redocmds.push(cmd);
            cmd->Undo();
        }
        else {
            cout<<"Can not undo"<<endl;
        }
    }

private :
    stack<Command*> undocmds;
    stack<Command*> redocmds;
};

#endif // COMMANDMANAGER_H_INCLUDED
