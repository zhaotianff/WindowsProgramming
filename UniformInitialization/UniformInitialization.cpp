// UniformInitialization.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<vector>
#include<string>

#include <time.h>

// No constructor
struct TempData
{
    int StationId;
    time_t timeSet;
    double current;
    double maxTemp;
    double minTemp;
};

// Has a constructor
struct TempData2
{
    TempData2(double minimum, double maximum, double cur, int id, time_t t) :
        stationId{ id }, timeSet{ t }, current{ cur }, maxTemp{ maximum }, minTemp{ minimum } {}
    int stationId;
    time_t timeSet;
    double current;
    double maxTemp;
    double minTemp;
};

class P
{
public:
    P();
    P(int, int);
    P(std::initializer_list<int>);
};

P::P()
{
}


P::P(int, int)
{

}

P::P(std::initializer_list<int>)
{

}

int main()
{
    int values[]{ 1,2,3,4,5 };

    std::vector<int> v{ 1,2,3,4,5,6 };
    std::vector<std::string> strs{"Hello", "World"};

    //i has undefined value
    int i;
    //j is initalized by 0
    int j{};

    //p has undefined value
    int* p;
    //q has initialized by nullptr
    int* q{};

    //narrowing is not allowed
    //error
    //int x{ 5.3 };


    //P::P(int,int)
    P pp{ 1,2 };  

    //P::P(initializer_list)
    P qq{ 1,2,3,4 };
    P rr = { 1,2,3,4 };
    
    time_t time_to_set;

    // Member initialization (in order of declaration):
    TempData td{ 45978, time(&time_to_set), 28.9, 37.0, 16.7 };

    // Default initialization = {0,0,0,0,0}
    TempData td_default{};

    // Uninitialized = if used, emits warning C4700 uninitialized local variable
    TempData td_noInit;

    // Member declaration (in order of ctor parameters)
    TempData2 td2{ 16.7, 37.0, 28.9, 45978, time(&time_to_set) };

}

