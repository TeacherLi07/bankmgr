#include<iostream>
#include"banklist.h"
using std::cin, std::cout, std::endl;

int main()
{
    Date d1{2024,2,28};
    cout<<"Date d1: "<<d1.year<<"-"<<d1.month<<"-"<<d1.day<<endl;
    d1++;
    cout<<"After d1++: "<<d1.year<<"-"<<d1.month<<"-"<<d1.day<<endl;
    ++d1;
    cout<<"After ++d1: "<<d1.year<<"-"<<d1.month<<"-"<<d1.day<<endl;
}