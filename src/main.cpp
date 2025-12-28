#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "deposit&withdraw.h"
#include "banklist.h"
#include"interest.h"
#include"transfer_accounts.h"
#include "Sort.h"
#include "RecorrectKey.h"
using std::cout;
using std::cin;
using std::getline;
//打印所有账户信息，测试用
void print_whole_account(BankListNode* head)
{
    BankListNode* p=head->next;
    while(p!=nullptr)
    {
        cout<<"账户ID:"<<p->account.accountID<<'\n';
        cout<<"账户姓名:"<<p->account.ownerName<<'\n';
        cout<<"账户性别:"<< (p->account.gender ? "男" : "女")<<'\n';
        cout<<"账户余额:"<<p->account.balance/100.0<<'\n';      
        cout<<"账户创建日期:"<<p->account.creationDate.year<<"-"<<p->account.creationDate.month<<"-"<<p->account.creationDate.day<<'\n';
        cout<<"账户类型:"<<(p->account.isFixed ? "定期" : "活期")<<'\n';
        cout<<"---------------------------"<<'\n';
        p=p->next;
    }
}
int main(int argc, char **argv) 
{
    SetConsoleOutputCP(936); 
    SetConsoleCP(936);
    cout<<"欢迎登陆梅依哥诗人---银行管理系统"<<'\n';
    while(1)
    {
        
        cout<<"请选择你需要操作的账户所在的银行代码:a,b,c,d,e\n若想要退出请输入0\n";
        char choice_bank;
        cin>>choice_bank;
        choice_bank=tolower(choice_bank);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if(choice_bank=='0')
        {
            break;
        }
        else if(choice_bank<='e'&&choice_bank>='a')
        {
            BankListNode* head=createList();
            loadFromFile(head, std::format("bankdata\\{}.txt", choice_bank));
            //手动输入一些账户用于测试
            // Account acc1;
            // acc1.accountID="1001";
            // acc1.ownerName="张三";
            // acc1.gender=true;
            // acc1.password="pass123";
            // acc1.balance=500000; // 5000.00元
            // acc1.creationDate={2022,5,20};
            // acc1.isFixed=false;
            // appendAccount(head,acc1);
            // Account acc2;
            // acc2.accountID="1002";
            // acc2.ownerName="李四";
            // acc2.gender=false;
            // acc2.password="word456";\
            // acc2.balance=1000000; // 10000.00元
            // acc2.creationDate={2021,8,15};
            // acc2.isFixed=true;
            // appendAccount(head,acc2);
            // Account acc3;
            // acc3.accountID="1003";
            // acc3.ownerName="王五";
            // acc3.gender=true;
            // acc3.password="abc789";
            // acc3.balance=750000; // 7500.00元
            // acc3.creationDate={2023,1,10};
            // acc3.isFixed=false;
            // appendAccount(head,acc3);
            // print_whole_account(head);
            bool flag=1;
            while(flag)
            {
                printf("请输入你要进行的操作的代号：\nA.查询\nB.开户\nC.销户\nD.修改账户密码\nE.账户排序\nF.存款\nG.取款\nH.转账\nI.计算利息\nJ.退出该银行\n");
                char choice_operation;
                cin>>choice_operation;
                choice_operation=toupper(choice_operation);
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                switch(choice_operation)
                {
                    case 'A':
                    {
                        
                    }
                    break;
                    case 'B':
                    {

                    }
                    break;
                    case 'C':
                    {

                    }
                    break;
                    case 'D':
                    {
                        RecorrectKey(head);
                    }
                    break;
                    case 'E':
                    {
                        Sort(head);
                    }
                    break;
                    case 'F':
                    {
                        while(1)
                        {
                            show_all_accountIDs(head);
                            printf("请输入你要查询账户的编号:（输入0以退出）");//增加输出所有账户ID的功能，并提示用户输入0返回上一级菜单
                            string temp_account;
                            getline(cin,temp_account);
                            if(temp_account=="0")
                            {
                                break;
                            }
                            BankListNode* ptarget_account=find_accountID(head,temp_account);
                            if(ptarget_account!=nullptr)
                            {
                                while(1)
                                {
                                    printf("请输入该账户的密码:");
                                    string temp_password;
                                    getline(cin,temp_password);
                                    if(password_correct(ptarget_account,temp_password))
                                    {
                                        printf("密码正确！\n");
                                        while(1)
                                        {
                                            printf("当前账户余额为: %.2f元\n",ptarget_account->account.balance/100.0);
                                            printf("请输入存款金额:");//增加显示当前金额的功能
                                            double cin_money;
                                            cin>>cin_money;
                                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            long long deposit_balance=(long long) cin_money*100;
                                            if(deposit_balance<=0)
                                            {
                                                printf("请输入正确的存款金额（输入0退出）\n");
                                            }
                                            else
                                            {
                                                depositmoney(ptarget_account,deposit_balance);
                                                printf("存款成功！\n");
                                                printf("存款后账户余额为: %.2f元\n",ptarget_account->account.balance/100.0);
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        printf("密码错误！请重新输入\n");
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                printf("请输入正确的账户编号\n");
                            }
                        }

                    }
                    break;
                    case 'G':
                    {
                        while(1)
                        {
                            show_all_accountIDs(head);
                            printf("请输入你要查询账户的编号:（输入0以退出）");//增加输出所有账户ID的功能，并提示用户输入0返回上一级菜单
                            string temp_account;
                            getline(cin,temp_account);
                            if(temp_account=="0")
                            {
                                break;
                            }
                            BankListNode* ptarget_account=find_accountID(head,temp_account);
                            if(ptarget_account!=nullptr)
                            {
                                while(1)
                                {
                                    printf("请输入该账户的密码:");
                                    string temp_password;
                                    getline(cin,temp_password);
                                    if(password_correct(ptarget_account,temp_password))
                                    {
                                        printf("密码正确！\n");
                                        while(1)
                                        {
                                            printf("当前账户余额为: %.2f元\n",ptarget_account->account.balance/100.0);
                                            printf("请输入取款金额:");//增加显示当前金额的功能
                                            double cin_money;
                                            cin>>cin_money;
                                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            long long withdraw_balance=(long long) cin_money*100;
                                            if(withdraw_balance<=0)
                                            {
                                                printf("请输入正确的取款金额（输入0退出）\n");
                                            }
                                            else if(!check_diposit_valid(ptarget_account,withdraw_balance))
                                            {
                                                printf("余额不足，请重新输入取款金额\n");
                                            }
                                            else
                                            {
                                                withdrawmoney(ptarget_account,withdraw_balance);
                                                printf("取款成功！\n");
                                                printf("取款后账户余额为: %.2f元\n",ptarget_account->account.balance/100.0);
                                                break;
                                            }
                                        }
                                        break;
                                    }
                                    else
                                    {
                                        printf("密码错误！请重新输入\n");
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                printf("请输入正确的账户编号\n");
                            }
                        }
                    }
                    break;
                    case 'H':
                    {
                        
                    }
                    break;
                    case 'I':
                    {
                        
                    }
                    break;

                    case 'J':
                    flag=0;
                    break;

                    default:
                    printf("别闹！输入正确的代号！");
                    break;
                }
            }
        }
        else
        {
            printf("你这个家伙，请输入正确的银行编号！！\n");
            continue;
        }
    }
    //保存并退出

    return 0;
}
