// Exception.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<exception>
#include<typeinfo>
#include<Windows.h>
#include<future>
#include<iostream>

template<typename T>
void processCodeException(const T& e)
{
    using namespace std;
    auto c = e.code();
    cerr << "-category :    " << c.category().name() << endl;
    cerr << "-value:        " << c.value() << endl;
    cerr << "-msg:          " << c.message() << endl;
    cerr << "-def category: " << c.default_error_condition().category().name() << endl;
    cerr << "-def value:    " << c.default_error_condition().value() << endl;
    cerr << "-def msg:        " << c.default_error_condition().message() << endl;
}

void processException()
{
    using namespace std;

    try
    {
        throw;
    }
    catch (const ios_base::failure& e)
    {
        cerr << "I/O exception" << e.what() << endl;
        processCodeException(e);
    }
}

int main()
{
    processException();
}