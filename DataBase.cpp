#include <vector>
#include "Polynomial.cpp"
using namespace std;
class DataBase{//定义临时存储类
    vector<Polynomial> data;//本质上是使用vector来存储
    public:
    DataBase(){}
    void addPoly(Polynomial &py)//将多项式添加到data中
    {
        int index=getPoly(py.getName());//先判断data中是否有重名的多项式
        if(index!=-1)
        data.erase(data.begin()+index);//如果有就删除掉
        data.push_back(py);//添加多项式
    }

    vector<Polynomial>& getData()
    {
        return data;//将数据返回
    }

    int getPoly(const string &name)//通过多项式名称来获取多项式
    {
        int index=0;
        for (auto &temp:data)
        {
            if(temp.getName()==name)
                return index;//找到就返回多项式在data中的Index
            index++;
        }
        return -1;//如果没有找到就返回-1
    }
};