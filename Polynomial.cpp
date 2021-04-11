#include <string>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;
class Polynomial
{
private:
    vector<double> poly;
    string name;

public:
    Polynomial() {}
    Polynomial(vector<double> ve, string n)
    { //根据特殊格式的vector容器来创建多项式 n是多项式的名称
        vector<double> dp(ve.size() / 2, INT32_MIN);
        int index = 0;
        bool find;
        for (int i = 1; i < ve.size(); i += 2)
        {
            find = false;
            for (int j = 0; j <= i / 2; j++)
            {
                if (dp[j] == ve[i])
                {
                    ve[2 * j] += ve[i - 1];
                    ve.erase(ve.begin() + i);
                    ve.erase(ve.begin() + i - 1);
                    i -= 2;
                    find = true;
                    break;
                }
            }
            if (!find)
                dp[index++] = ve[i];
        }
        poly = vector<double>(ve);
        name = n;
    }

        string to_string() //将poly里面的数据转化为字符串，并且按照降序输出
        {
            stringstream ss;
            auto temp = vector<double>(poly);
            string str_poly;
            string val;
            bool isHead = true;
            while (!temp.empty()) //降序输出循环
            {
                int max_index = 1;
                for (int j = 1; j < temp.size(); j += 2) //先找出最大的指数项
                {
                    if (temp[j] > temp[max_index])
                        max_index = j;
                }
                ss.clear();
                ss << temp[max_index - 1];                               //获取最大项的系数
                ss >> val;                                               //通过stringstream将double类型数据转化为string类型
                if ((val == "-1" || val == "1") && temp[max_index] != 0) //1 或者-1要省略
                    val.pop_back();
                else if (temp[max_index - 1] == 0) //如果系数为0，则直接将0项删除
                {
                    temp.erase(temp.begin() + max_index);
                    temp.erase(temp.begin() + max_index - 1);
                    continue;
                }
                if (isHead) //在头部不需要添加加号或者减号
                {
                    str_poly += val; //将系数开始加入多项式字符串中
                    isHead = false;
                }
                else
                    str_poly += (val[0] == '-' ? val : "+" + val);
                ss.clear();
                ss << temp[max_index];
                ss >> val;
                if (temp[max_index] > 1) //将指数开始添加到多项式字符串中
                    str_poly += "x^" + val;
                else if (temp[max_index] == 1)
                    str_poly += "x";
                temp.erase(temp.begin() + max_index); //删除已经添加过的项
                temp.erase(temp.begin() + max_index - 1);
            }
            return str_poly.empty()?"0":str_poly;
        }
        string &getName()
        {
            return name;
        }
        vector<double> &getPoly()
        {
            return poly;
        }
};