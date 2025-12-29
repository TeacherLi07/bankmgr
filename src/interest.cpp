#include"interest.h"
#include"deposit&withdraw.h"
#include<iostream>
using std::cout; using std::cin; using std::getline;
int calculateDaysBetween(Date start, Date end);

void calculate_interest(BankListNode* head)
{
    string accountID_input;
    
    // 循环直到输入0退出或计算成功
    while(true)
    {
        cout << "请输入要计算利息的账户ID(输入0退出):";
        getline(cin, accountID_input);
        
        // 检查是否要退出
        if(accountID_input == "0")
        {
            cout << "退出利息计算\n";
            return;
        }
        
        // 在链表中查找账户
        BankListNode* target_account = find_accountID(head, accountID_input);
        
        if(target_account == nullptr)
        {
            cout << "账户不存在，请重新输入！\n";
            continue;
        }
        
        // 账户存在，验证密码
        string password_input;
        while(true)
        {
            cout << "请输入账户密码(输入0退出):";
            getline(cin, password_input);
            
            if(password_input == "0")
            {
                cout << "退出利息计算\n";
                return;
            }
            for(int i = 0; i < password_input.length(); i++) {
                if(password_input[i] == ' ') {
                    cout << "密码不能包含空格，请重新输入！\n";
                    continue;
                }
            }
            
            if(password_correct(target_account, password_input))
            {
                cout << "密码验证成功！\n";
                break;
            }
            else
            {
                cout << "密码错误，请重新输入！\n";
            }
        }
        
        // 获取账户信息
        long long balance_fen = target_account->account.balance;
        bool isFixed = target_account->account.isFixed;
        Date creationDate = target_account->account.creationDate;
        
        // 输入存款到期时间
        Date maturityDate;
        long long number;
        while(1)
        {
            cout << "请输入存款到期时间（YYYYMMDD）：（输入0退出计算服务）\n";
            cin >> number;
            if(number == 0)
            {
                cout << "退出利息计算\n";
                return;
            }
            maturityDate.year = number / 10000;
            maturityDate.month = (number - maturityDate.year*10000)/100;
            maturityDate.day = number - maturityDate.year*10000 - maturityDate.month*100;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if(isValid(maturityDate) && maturityDate > creationDate)
            {
                break;
            }
            else
            {
                cout << "输入的日期无效或早于开户日期，请重新输入！\n";
            }
        }
        
        
        
        // 计算存款天数
        int depositDays = calculateDaysBetween(creationDate, maturityDate);
        int depositDays1 = depositDays;
        int depositYears = 0;
        long long interest = 0;
        
        // 根据账户类型计算利息
        if(!isFixed) // 活期账户
        {
            // 活期年利率：0.35%
            double annualRate = 0.0035;
            while(depositDays >= 365){
            balance_fen += balance_fen * annualRate;
            bool isr = (creationDate.year % 4 == 0 && creationDate.year % 100 != 0) || (creationDate.year % 400 == 0);
            depositDays -= 365 + isr;
            depositYears++;
            }
            if(depositDays != 0) balance_fen += balance_fen * annualRate * 0.5;
        }
        else // 定期账户
        {
            // 根据存款年限确定利率
            while(depositDays >= 365){
                depositYears++;
            if(depositYears == 1)
            {
                // 第一年利率：2.75%
                double annualRate = 0.0275;
                balance_fen += balance_fen * annualRate;
            }
            else if(depositYears == 2)
            {
                // 第一年：2.75%，第二年：3.35%
                double annualRate = 0.0335;
                balance_fen += balance_fen * annualRate;
            }
            else
            {
                // 第一年：2.75%，第二年：3.35%，第三年及以后：4%
                double annualRate = 0.04;
                balance_fen += balance_fen * annualRate;
            }
            bool isr = (creationDate.year % 4 == 0 && creationDate.year % 100 != 0) || (creationDate.year % 400 == 0);
            depositDays -= 365 + isr;
        }
    }
            
            // 如果存款时间不是整年，按半年计算
            if(depositDays != 0)
            {
                if(depositYears == 0||depositYears == 1)
                balance_fen += balance_fen * 0.0275 * 0.5; // 按半年计算，利率取第一年利率的一半
                else if(depositYears == 2)
                balance_fen += balance_fen * 0.0335 * 0.5;
                else balance_fen += balance_fen * 0.04 * 0.5;
            }
        interest = balance_fen - target_account->account.balance;
        // 输出结果
        cout << "\n========== 利息计算结果 ==========\n";
        cout << "账户ID：" << target_account->account.accountID << "\n";
        cout << "账户姓名：" << target_account->account.ownerName << "\n";
        cout << "存款本金：" << target_account->account.balance/100 << " 元\n";
        cout << "开户日期：" << creationDate.year << "-" 
             << creationDate.month << "-" << creationDate.day << "\n";
        cout << "到期日期：" << maturityDate.year << "-" 
             << maturityDate.month << "-" << maturityDate.day << "\n";
        cout << "存款天数：" << depositDays1 << " 天\n";
        cout << "存款年限：" << depositYears << " 年\n";
        cout << "应得利息：" << interest/100 << " 元\n";
        cout << "本息合计：" << balance_fen/100 << " 元\n";
        cout << "=================================\n\n";
        return;
    }
}

int calculateDaysBetween(Date start, Date end)
{
    int startDays = start.year * 365 + start.month * 30 + start.day;
    int endDays = end.year * 365 + end.month * 30 + end.day;
    return endDays - startDays;
}