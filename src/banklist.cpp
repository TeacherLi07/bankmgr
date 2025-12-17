#include"banklist.h"

Date operator++(Date& d, int){
    Date temp = d; // 保存原始值用于返回
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);
    
    // 修改 d 本身
    d.day++;
    if(d.month == 2)
    {
        if(d.day > isr + daysInMonth[2])
        {
            d.day = 1;
            d.month++;
        }
    }else if(d.day > daysInMonth[d.month])
    {
        d.day = 1;
        d.month++;
        if(d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
    return temp; // 返回修改前的值
}
Date operator++(Date& d){
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);
    
    // 修改 d 本身
    d.day++;
    if(d.month == 2)
    {
        if(d.day > isr + daysInMonth[2])
        {
            d.day = 1;
            d.month++;
        }
    }else if(d.day > daysInMonth[d.month])
    {
        d.day = 1;
        d.month++;
        if(d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
    return d; // 返回修改前的值
}
// int operator-(const Date& d1, const Date& d2)
// {
//     const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
// }