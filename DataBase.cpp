#include <vector>
#include "Polynomial.cpp"
using namespace std;
class DataBase{
    vector<Polynomial> data;
    public:
    DataBase(){}
    void addPoly(Polynomial &py)
    {
        int index=getPoly(py.getName());
        if(index!=-1)
        data.erase(data.begin()+index);
        data.push_back(py);
    }

    vector<Polynomial>& getData()
    {
        return data;
    }

    int getPoly(const string &name)
    {
        int index=0;
        for (auto &temp:data)
        {
            if(temp.getName()==name)
                return index;
            index++;
        }
        return -1;
    }
};