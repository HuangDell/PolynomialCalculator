//在这里定义各种多项计算的操作符
typedef Polynomial py;
py ans;
py &operator+(py&py1, py& py2)
{
    vector<double> temp(py1.getPoly());
    for (auto num : py2.getPoly())
        temp.push_back(num);
    ans = py(temp, "ans");
    return ans;
}
py &operator-(py& py1, py& py2)
{
    vector<double> temp(py1.getPoly());
    int index=0;
    for (auto num : py2.getPoly())
    {
        if(index++%2==0)
            num=-num;
        temp.push_back(num);

    }
    ans = py(temp, "ans");
    return ans;
}
py &operator*(py& py1,py& py2)
{
    vector<double> temp;
    int size1=py1.getPoly().size();
    int size2=py2.getPoly().size();
    for(int i=0;i<size1;i+=2)
    {
        for(int j=0;j<size2;j+=2)
        {
            temp.push_back(py1.getPoly()[i]*py2.getPoly()[j]);
            temp.push_back(py1.getPoly()[i+1]+py2.getPoly()[j+1]);
        }
    }
    ans = py(temp, "ans");
    return ans;
}
bool operator==(py &py1,py &py2)
{
    if(py1.to_string()==py2.to_string())
    return true;
    return false;
}