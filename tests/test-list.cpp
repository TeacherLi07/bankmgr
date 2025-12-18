#include <iostream>
#include "banklist.h"
using std::cin, std::cout, std::endl;

int main()
{
    // 测试 Date 结构体的运算符重载
    Date d1 = {2024, 2, 28};
    Date d2 = {2024, 2, 29};
    cout << "Initial Dates:" << endl;
    cout << "d1: " << d1.year << "-" << d1.month << "-" << d1.day << endl;
    cout << "d2: " << d2.year << "-" << d2.month << "-" << d2.day << endl;
    cout << "d1 == d2: " << (d1 == d2) << endl;
    cout << "d1 != d2: " << (d1 != d2) << endl;
    cout << "Incrementing d1 (postfix): " << endl;
    Date d1_post = d1++;
    cout << "d1 after postfix increment: " << d1.year << "-" << d1.month << "-" << d1.day << endl;
    cout << "Returned value from postfix increment: " << d1_post.year << "-" << d1_post.month << "-" << d1_post.day << endl;
    cout << "Date difference d1 - d2: " << (d1 - d2) << " days" << endl;
    cout << "Date difference d2 - d1: " << (d2 - d1) << " days" << endl;
    return 0;
}