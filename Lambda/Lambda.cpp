// Lambda.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//对于习惯了C#语言的人来说，这lambda确实舒服。个人感觉，C++里Lambda的语法比C#里的要复杂 一些，

//感觉编程语言里一些好的特性，都会被互相学习和借鉴。 在新版本js和Java中，也可以看到Lambda的身影

#include <iostream>
#include<algorithm>
#include<deque>
#include<string>

using std::deque;
using std::string;

class Person
{
private:
    string firstname;
    string lastname;
public:
    Person(string firstname, string lastname);
public:
    inline string GetFirstname() { return firstname; };
    inline string GetLastname() { return lastname; };
};

int main()
{
    auto a = [](double d) {return d * d * d; };
    //在C#里是这样的
    //Func<int, int> func = d => d * d * d;
    std::cout << a(10) << std::endl;

    deque<int> coll{ 1,3,19,5,13,7,11,2,17 };
    int x = 5;
    int y = 12;
    //跟C#里的断言(Predicate)是一样的
    auto pos = std::find_if(coll.cbegin(), coll.cend(),
        [=](int i) { return i > x && i < y; });

    std::cout << "first elem > 5 & < 12 : " << *pos << std::endl;

    //对应以下的代码
    deque<int>::iterator pos;
    for (pos = coll.begin(); pos != coll.end(); ++pos)
    {
        if (*pos > x && *pos < y)
            break;
    }

    //在C#里是这样的
    //var result = coll.Where(x = > i > x && i < y);

    //以lambda作为排序准则

}