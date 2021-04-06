#include <string>
#include <conio.h>
#include <cctype>
#include "DataBase.cpp"
#include "Calculate.cpp"
class Menu//Menu类只用于与用户进行交互，不负责具体计算的实现
{
    string input;
    Judge judge;
    DataBase data;
    bool createPoly()//获取用户输入的多项式
    {
        vector<double> poly;
        judge.clear();
        poly = judge.polynomial(input);
        if (!poly.empty())
        {
            Polynomial polynomial(poly, judge.getName());
            data.addPoly(polynomial);
            printf("你输入的多项式是：%s=", judge.getName().c_str());
            cout << polynomial.to_string() << endl;
        }
        else
        {
            printf("输入格式有误，请重新输入！\n");
            cin>>input;
            return false;
        }
        return true;
    }

    public:
    void printMenu()
    {
        printf("1.添加多项式\t\t2.查看多项式\t\t3.加法计算\n");
        printf("4.减法计算\t\t  5.乘法计算\t\t  6.求值\n");
    }

    bool isLegal(string choose)
    {
        if (!isdigit(choose[0]) || choose.size() > 1)
            return false;
        return true;
    }

    void Mode1()
    {
        system("cls");
        printf("请输入一个多项式(格式:名称(可选)=(系数,指数))\n");
        cin>> input;
        while (!createPoly());
        printf("输入任意键继续\n");
        getch();
    }
    void Mode2()
    {
        system("cls");
        auto data_poly=data.getData();
        printf("目前储存的多项式有：");
        for (auto temp:data_poly)
            printf("%s=%s\n",temp.getName().c_str(),temp.to_string().c_str());
        printf("输入任意键继续\n");
        getch();
    }
    void calculate(int mode)
    {
        system("cls");
        Polynomial py[2];
        Polynomial ans;
        if(mode==1)
            printf("加法运算\n");
        else if(mode==2)
            printf("减法运算\n");
        else if(mode==3)
            printf("乘法运算\n");
        for (int i = 0; i < 2; i++)//for循环读取两个多项式
        {
            printf("请输入第%s个多项式:",i==0?"一":"二");
        start:
            cin >> input;
            if (judge.isName(input))//如果使用名称输入
            {
                int index = data.getPoly(input);
                if (index == -1)
                {
                    printf("找不到多项式：%s,请重新输入\n", input.c_str());
                    goto start;
                }
                py[i] = data.getData()[index];
                printf("你输入的多项式是：%s=%s\n", py[i].getName().c_str(), py[i].to_string().c_str());
            }
            else//正常输入
            {
                while (!createPoly());
                py[i] = data.getData().back();
            }
        }
        if(mode==1)
        ans=py[0]+py[1];
        else if (mode==2)
        ans=py[0]-py[1];
        else if(mode==3)
        ans=py[0]*py[1];
        data.addPoly(ans);
        printf("结果：ans=%s\n", ans.to_string().c_str());
        printf("输入任意键继续\n");
        getch();
    }
};