#include <string>
#include <conio.h>
#include <cctype>
#include "DataBase.cpp"
#include "Calculate.cpp"
#define quit(input) \
if(input=="quit")\
return ;//������ʹ��macro������quit function
class Menu//Menu��ֻ�������û����н������������������ʵ��
{
    string input;
    Judge judge;
    DataBase data;
    void PressAny()
    {
        printf("�������������\n");
        getch();
    }
    bool createPoly()//��ȡ�û�����Ķ���ʽ
    {
        vector<double> poly;
        judge.clear();
        poly = judge.polynomial(input);
        if (!poly.empty())
        {
            Polynomial polynomial(poly, judge.getName());
            data.addPoly(polynomial);
            printf("������Ķ���ʽ�ǣ�%s=", judge.getName().c_str());
            cout << polynomial.to_string() << endl;
        }
        else
        {
            printf("�����ʽ�������������룡\n");
            cin>>input;
            return false;
        }
        return true;
    }

    public:
    void printMenu()
    {
        printf("\t\t\t����ʽ������\n");
        printf("1.��Ӷ���ʽ\t\t2.�鿴����ʽ\t\t3.�ӷ�����\n");
        printf("4.��������\t\t5.�˷�����\t\t6.��ֵ\n");
        printf("7.���㵼��\t\t8.�ж����\t\t9.�˳�\n");
        printf("�������������quit��������һ��\n");
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
        printf("������һ������ʽ(��ʽ:����(��ѡ)=(ϵ��,ָ��))(ע�����ǲ���Ҫ���㰴�ս��������������):\n");
        cin>> input;
        quit(input);
        while (!createPoly());
        PressAny();
    }
    void Mode2()
    {
        system("cls");
        auto data_poly=data.getData();
        printf("Ŀǰ����Ķ���ʽ�У�\n");
        for (auto temp:data_poly)
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
        printf("Ŀǰ����Ķ���ʽ�У�\n");
        for (auto temp:data_poly)
            printf("%s=%s\n",temp.getName().c_str(),temp.to_string().c_str());
        if(mode==1)
        printf("������Ҫ��ֵ�Ķ���ʽ(�����ʹ�ö���ʽ���ƻ�����������һ������ʽ):");
        else 
        printf("������Ҫ�󵼵Ķ���ʽ(�����ʹ�ö���ʽ���ƻ�����������һ������ʽ):");
        start:
            cin >> input;
            quit(input);
            if (judge.isName(input))//���ʹ����������
            {
                int index = data.getPoly(input);
                if (index == -1)
                {
                    printf("�Ҳ�������ʽ��%s,����������:", input.c_str());
                    goto start;
                }
                py= data.getData()[index];
                printf("������Ķ���ʽ�ǣ�%s=%s\n", py.getName().c_str(), py.to_string().c_str());
            }
            else //��������
            {
                
                while (!createPoly())
                quit(input);
                py= data.getData().back();
            }
        if(mode==1)
        {
            printf("������x��ֵ��");
        Again:
            if (!(cin >> x))
            {
                cout << "����������:";
                cin.clear();
                fflush(stdin);
                goto Again;
            }
        
            ans = evaluation(py, x);
        }
        else
            ans = diff(py);
        data.addPoly(ans);
        printf("�����ans=%s\n", ans.to_string().c_str());
        PressAny();
    }

    void calculate(int mode)
    {
        system("cls");
        Polynomial py[2];
        Polynomial ans;
        if(mode==1)
            printf("�ӷ�����\n");
        else if(mode==2)
            printf("��������\n");
        else if(mode==3)
            printf("�˷�����\n");
        else if(mode==4)
            printf("�ж����\n");
        for (int i = 0; i < 2; i++)//forѭ����ȡ��������ʽ
        {
            printf("�������%s������ʽ(�����ʹ�ö���ʽ���ƻ�����������һ������ʽ):",i==0?"һ":"��");
        start:
            cin >> input;
            quit(input);
            if (judge.isName(input))//���ʹ����������
            {
                int index = data.getPoly(input);
                if (index == -1)
                {
                    printf("�Ҳ�������ʽ��%s,����������:", input.c_str());
                    goto start;
                }
                py[i] = data.getData()[index];
                printf("������Ķ���ʽ�ǣ�%s=%s\n", py[i].getName().c_str(), py[i].to_string().c_str());
            }
            else//��������
            {
                while (!createPoly())
                quit(input);
                py[i] = data.getData().back();
            }
        }
        if(mode==1)
        ans=py[0]+py[1];
        else if (mode==2)
        ans=py[0]-py[1];
        else if(mode==3)
        ans=py[0]*py[1];
        else if(mode==4)
        {
            printf("�����%s\n", py[0] == py[1] ? "���" : "�����");
            PressAny();
            return;
        }
        data.addPoly(ans);
        printf("�����ans=%s\n", ans.to_string().c_str());
        PressAny();
    }
};