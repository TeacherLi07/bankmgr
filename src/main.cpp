SetConsoleOutputCP(936); 
SetConsoleCP(936);
#include <stdio.h>
#include <iostream>
#include "deposit&withdraw.h"
#include "banklist.h"
#include <windows.h>
using std::cout;
using std::cin;
int main(int argc, char **argv) 
{
    BankListNode* head=new BankListNode;
    cout<<"欢迎登陆梅依哥诗人---银行管理系统"<<'\n';
    while(1)
    {
        cout<<"请选择你需要操作的账户:a,b,c,d,e\n若想要退出请输入0\n";
        char choice_bank;
        cin>>choice_bank;
        if(choice_bank=='0')
        {
            break;
        }
        else if(choice_bank<='J'&&choice_bank>='A')
        {

        }
        else
        {
            printf("")
        }
    }
    //保存并退出

    return 0;
}
