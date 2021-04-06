#include <regex>
#include <cctype>
#include <string>
#include <vector>
using namespace std;
class Judge
{
    private:
    regex str_reg;
    regex str_draw;
    regex str_name;
    smatch matchResult;
    string poly_name;
    
    public:
    Judge()
    {
        poly_name="None";
        str_reg=regex("((\\w+)=)?(\\(-?\\d+,-?\\d+\\))+");//用于判断输入的多项式是否合法
        str_draw=regex(R"~((-?\d+),(-?\d+))~");//提取多项式的系数和指数
        str_name=regex("(\\w+)=.*");//提取多项式名称
    }

    vector<double> polynomial(string input)//此函数用于解析输入的多项式，并将结果以vector形式返回。
    {
        vector<double> poly;
        if(regex_match(input,matchResult,str_reg) && matchResult[0].length()==input.size())//判断是否输入了合法的表达式
        {
            sregex_iterator iter(input.begin(), input.end(), str_draw);//使用迭代器获取多项式的系数和指数
            sregex_iterator end;
            while(iter!=end)
            {
                for (int i=1;i<iter->size();i++)
                    poly.push_back(stod((*iter)[i]));
                    iter++;
            }
            if(regex_match(input,matchResult,str_name))//正则表达式提取多项式名称
                poly_name=matchResult[1];
        }
        return poly;
    }
    string getName()
    {
        return poly_name;
    }
    void clear()
    {
        poly_name="None";
    }
    bool isName(string input)
    {
        for (auto ch:input)
            if(!isalnum(ch))
                return false;
        return true;

    }

};
