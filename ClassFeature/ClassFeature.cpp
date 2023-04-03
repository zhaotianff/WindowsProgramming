// ClassFeature.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}


/*
 * default
 * C++11 provides more control over which methods are used. 
 * Suppose that you wish to use a defaulted function that, 
 * due to circumstances, isn’t created automatically. For example, 
 * if you provide a move constructor, then the default constructor, 
 * the copy constructor, and the copy assignment operator are not provided. 
 * In that case, you can use the keyword default to explicitly declare the defaulted versions of these methods:
 */
class Animal
{
public:
    Animal() = default;
    Animal(const Animal& animal) = default;
    Animal& operator=(const Animal& animal) = default;
};

/*
 * The compiler provides the same constructor that it would have provided automatically had you not provided the move constructor.
 * The delete keyword, on the other hand, can be used to prevent the compiler from using a particular method. For example, to prevent an object from being copied, you can disable the copy constructor and copy assignment operator:
 */

class Animal
{
public:
    Animal() = delete;
    Animal(const Animal& animal) = delete;
};