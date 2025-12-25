#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include "deposit&withdraw.h"
#include "banklist.h"
using std::cout;
using std::cin;
using std::getline;
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
            print_whole_account(head);
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

                    }
                    break;
                    case 'E':
                    {

                    }
                    break;
                    case 'F':
                    {
                        while(1)
                        {
                            printf("请输入你要查询账户的编号:");
                            string temp_account;
                            getline(cin,temp_account);
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
                                            printf("请输入存款金额:");
                                            double cin_money;
                                            cin>>cin_money;
                                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                            long long deposit_balance=(long long) cin_money*100;
                                            if(deposit_balance<=0)
                                            {
                                                printf("请输入正确的存款金额\n");
                                            }
                                            else
                                            {
                                                depositmoney(ptarget_account,deposit_balance);
                                                printf("存款成功！\n");
                                                break;
                                            }
                                        }
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
