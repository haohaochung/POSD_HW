// With console output
#include "utShapes.h"
#include "Parser.h"
#include<conio.h>

int main()
{
    Parser p;
    CommandManager cm;
    p.getCommandManager(&cm);

    while(1)
    {
        char str[100];
        cout<< ":- ";
        cin.getline(str, 100);


        if(str[0]==25) {
            cm.RedoCMD();
        }
        else if(cin.eof()) {
            cm.UndoCMD();
        }
        else {
            p.textUI(str);
        }
        cout<<endl;
        cin.clear();
    }
    return 0;
}

