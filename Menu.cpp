#include <string>
#include <conio.h>
#include <cctype>
#include "DataBase.cpp"
#include "Calculate.cpp"
class Menu//Menu��ֻ�������û����н������������������ʵ��
{
    string input;
    Judge judge;
    DataBase data;
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
        printf("1.��Ӷ���ʽ\t\t2.�鿴����ʽ\t\t3.�ӷ�����\n");
        printf("4.��������\t\t  5.�˷�����\t\t  6.��ֵ\n");
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
        printf("������һ������ʽ(��ʽ:����(��ѡ)=(ϵ��,ָ��))\n");
        cin>> input;
        while (!createPoly());
        printf("�������������\n");
        getch();
    }
    void Mode2()
    {
        system("cls");
        auto data_poly=data.getData();
        printf("Ŀǰ����Ķ���ʽ�У�");
        for (auto temp:data_poly)
            printf("%s=%s\n",temp.getName().c_str(),temp.to_string().c_str());
        printf("�������������\n");
        getch();
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
        for (int i = 0; i < 2; i++)//forѭ����ȡ��������ʽ
        {
            printf("�������%s������ʽ:",i==0?"һ":"��");
        start:
            cin >> input;
            if (judge.isName(input))//���ʹ����������
            {
                int index = data.getPoly(input);
                if (index == -1)
                {
                    printf("�Ҳ�������ʽ��%s,����������\n", input.c_str());
                    goto start;
                }
                py[i] = data.getData()[index];
                printf("������Ķ���ʽ�ǣ�%s=%s\n", py[i].getName().c_str(), py[i].to_string().c_str());
            }
            else//��������
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
        printf("�����ans=%s\n", ans.to_string().c_str());
        printf("�������������\n");
        getch();
    }
};