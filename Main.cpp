#include <string>
#include <iostream>
#include <vector>
#include "Judge.cpp"
#include "Menu.cpp"
using namespace std;
int main(void)//main函数启动程序，实现交互。
{
    string choose;
    Menu menu;
    while(true)
    {
        start:
        system("cls");
        menu.printMenu();
        cin>>choose;
        if(!menu.isLegal(choose))
            goto start;
        switch(stoi(choose))
        {
            case 1:menu.Mode1();
            break;
            case 2:menu.Mode2();
            break;
            case 3:menu.calculate(1);
            break;
            case 4:menu.calculate(2);
            break;
            case 5:menu.calculate(3);
            default:
            goto start;
        }
    }
}

