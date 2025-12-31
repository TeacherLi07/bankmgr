#include "input.h"
#include "banklist.h"
#include <iostream>
using std::cin;
using std::cout;
using std::string;
// Function to input a choice character with validation
void inputchoice(char &choice)
{
    while (true)
    {
        cout << "请输入你的选择:\n";
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.length() != 1)
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        else
        {
            choice = temp_input[0];
            return;
        }
    }
}
// 该函数用于输入字符串，防止字符串中含有除数字之外其他字符
void inputAccountID(string &accountID)
{
    while (true)
    {
        bool flag_input = true;
        string temp_input;
        getline(cin, temp_input);
        if(temp_input.empty())
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        for (int i = 0; i < temp_input.size(); i++)
        {
            if (temp_input[i] < '0' || temp_input[i] > '9')
            {
                flag_input = false;
                break;
            }
        }
        if (!flag_input)
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        else
        {
            accountID = temp_input;
            return;
        }
    }
}
void inputName(string &name)
{
    while (true)
    {
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.empty())
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        else
        {
            name = temp_input;
            return;
        }
    }
}
void inputpassword(string &password)
{
    while (true)
    {
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.empty())
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        else
        {
            password = temp_input;
            return;
        }
    }
}
void inputgender(int &gender)
{
    while (true)
    {
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.length() != 1)
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        else
        {
            gender = temp_input[0] - '0';
            return;
        }
    }
}
void inputmoney(long long &balance)
{
    while (true)
    {
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.empty())
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        try
        {
            balance = (long long)(std::stod(temp_input)*100);
            return;
        }
        catch (const std::invalid_argument &)
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        catch (const std::out_of_range &)
        {
            cout << "输入的金额精度有误，请重新输入！\n";
            continue;
        }
    }
}
void inputdate(Date &date)
{
    while (true)
    {
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.length() != 8)
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        try
        {
            date.year = std::stoi(temp_input.substr(0, 4));
            date.month = std::stoi(temp_input.substr(4, 2));
            date.day = std::stoi(temp_input.substr(6, 2));
            return;
        }
        catch (const std::invalid_argument &)
        {
            cout << "输入的日期有误，请重新输入！\n";
            continue;
        }
    }
}
void inputAccountType(int &isFixed)
{
    while (true)
    {
        string temp_input;
        getline(cin, temp_input);
        if (temp_input.length() != 1)
        {
            cout << "输入错误，请重新输入！\n";
            continue;
        }
        else
        {
            char ch = temp_input[0];
            isFixed = ch - '0';
            return;
        }
    }
}