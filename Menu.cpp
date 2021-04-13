#include <string>
#include <conio.h>
#include <cctype>
#include "DataBase.cpp"
#include "Calculate.cpp"
#define quit(input) \
if(input=="quit")\
return ;//在这里使用macro来定义quit function
class Menu//Menu类只用于与用户进行交互，不负责具体计算的实现
{
    string input;
    Judge judge;
    DataBase data;
    void PressAny()
    {
        printf("输入任意键继续\n");
        getch();
    }
    bool createPoly()//获取用户输入的多项式
    {
        vector<double> poly;
        judge.clear();
        poly = judge.polynomial(input);//判断是否合法
        if (!poly.empty())
        {
            Polynomial polynomial(poly, judge.getName());
            data.addPoly(polynomial);//添加到临时存储中
            printf("你输入的多项式是：%s=", judge.getName().c_str());
            cout << polynomial.to_string() << endl;
        }
        else//输入不合法
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
        printf("\t\t\t多项式计算器\n");
        printf("1.添加多项式\t\t2.查看多项式\t\t3.加法计算\n");
        printf("4.减法计算\t\t5.乘法计算\t\t6.求值\n");
        printf("7.计算导数\t\t8.判断相等\t\t9.退出\n");
        printf("在任意界面输入quit来返回上一级\n");
    }

    bool isLegal(string choose)//判断是否合法
    {
        if (!isdigit(choose[0]) || choose.size() > 1)
            return false;
        return true;
    }

    void Mode1()
    {
        system("cls");
        printf("请输入一个多项式(格式:名称(可选)=(系数,指数))(注意我们并不要求你按照降序或者升序输入):\n");
        cin>> input;
        quit(input);
        while (!createPoly())
        quit(input);//如果不合法就一直循环，或者用户输入了quit
        PressAny();
    }
    void Mode2()
    {
        system("cls");
        auto data_poly=data.getData();
        printf("目前储存的多项式有：\n");
        for (auto temp:data_poly)//从数据库中获得多项式
            printf("%s=%s\n",temp.getName().c_str(),temp.to_string().c_str());
        PressAny();
    }
    void single(int mode)
    {
        system("cls");
        auto data_poly=data.getData();
        Polynomial ans;
        Polynomial py;
        double x;
        printf("目前储存的多项式有：\n");
        for (auto temp:data_poly)
            printf("%s=%s\n",temp.getName().c_str(),temp.to_string().c_str());
        if(mode==1)
        printf("请输入要求值的多项式(你可以使用多项式名称或者重新输入一个多项式):");
        else 
        printf("请输入要求导的多项式(你可以使用多项式名称或者重新输入一个多项式):");
        start:
            cin >> input;
            quit(input);
            if (judge.isName(input))//如果使用名称输入
            {
                int index = data.getPoly(input);
                if (index == -1)
                {
                    printf("找不到多项式：%s,请重新输入:", input.c_str());
                    goto start;
                }
                py= data.getData()[index];
                printf("你输入的多项式是：%s=%s\n", py.getName().c_str(), py.to_string().c_str());
            }
            else //正常输入
            {
                
                while (!createPoly())
                quit(input);
                py= data.getData().back();
            }
        if(mode==1)
        {
            printf("请输入x的值：");
        Again:
            if (!(cin >> x))//判断x是否合法
            {
                cout << "请重新输入:";
                cin.clear();
                fflush(stdin);
                goto Again;
            }
        
            ans = evaluation(py, x);//进行求值
        }
        else
            ans = diff(py);//进行求导
        data.addPoly(ans);//将结果添加到临时库中
        printf("结果：ans=%s\n", ans.to_string().c_str());
        PressAny();
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
        else if(mode==4)
            printf("判断相等\n");
        for (int i = 0; i < 2; i++)//for循环读取两个多项式
        {
            printf("请输入第%s个多项式(你可以使用多项式名称或者重新输入一个多项式):",i==0?"一":"二");
        start:
            cin >> input;
            quit(input);
            if (judge.isName(input))//如果使用名称输入
            {
                int index = data.getPoly(input);
                if (index == -1)
                {
                    printf("找不到多项式：%s,请重新输入:", input.c_str());
                    goto start;
                }
                py[i] = data.getData()[index];
                printf("你输入的多项式是：%s=%s\n", py[i].getName().c_str(), py[i].to_string().c_str());
            }
            else//正常输入
            {
                while (!createPoly())
                quit(input);
                py[i] = data.getData().back();
            }
        }
        if(mode==1)
        ans=py[0]+py[1];//使用运算符重载
        else if (mode==2)
        ans=py[0]-py[1];
        else if(mode==3)
        ans=py[0]*py[1];
        else if(mode==4)
        {
            printf("结果：%s\n", py[0] == py[1] ? "相等" : "不相等");
            PressAny();
            return;
        }
        data.addPoly(ans);
        printf("结果：ans=%s\n", ans.to_string().c_str());
        PressAny();
    }
};