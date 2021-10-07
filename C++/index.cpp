#include <stdio.h>
#include <string>
#include <list>
#include "./Hemex/Hemex.cpp"


bool SayileriBul(Hemex n,bool e){
    switch (n.getChar()) {
        case '1':
        case '2':
        case '3':{
            return false;
            break;
        }
        default:{
            return true;
        }
    }
}

int main()
{
    /**/
    Hemex abc;
    abc.setText("Merhaba 123");

    std::string a = abc.readWhileFunc(SayileriBul, true);
    printf("%s", a.data());
    /**/
    return 0;
}