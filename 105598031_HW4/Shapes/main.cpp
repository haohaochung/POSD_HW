#include "..\cppunitlite\TestHarness.h"
#include "utShapes.h"

#include <iostream>
#include <sstream>
#include <string>



using namespace std;

int main()
{
    TestResult tr;
    TestRegistry::runAllTests(tr);

//    std::string input;
//    while (true) {
//        cout<< ":-";
//        cin >> input;
//
//        if (input == "a") {
//            Rectangle rTall(1,0,4,1);
//            cout<<"Rectangle "<<rTall.area()<<" "<<endl;
//
//
//
//
//
//
//        }
//    }
    return 0;
}

