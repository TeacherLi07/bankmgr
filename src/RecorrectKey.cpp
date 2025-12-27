#include"RecorrectKey.h"
//判断密码正确函数
bool password_is_correct(BankListNode* target_Account,string Orginalpassword)
{
    if (target_Account->account.password==Orginalpassword)return 1;
    else return 0;
}
//修改密码函数
void RecorrectKey(BankListNode *head)
{
    cout<<"请输入你要查询账户的编号:";
    string temp_account;
    int flag=0;
    while(1)
    {
        cin>>temp_account;
        if (temp_account=="0")break;
        else if(find_accountID(head,temp_account)==nullptr)
        {
            cout<<"未找到该账户，请重新输入:";
            continue;
        }
        else
        {
            cout<<"请输入你的原密码:";
            while(1)
            {
                string password;
                cin>>password;
                if (password_is_correct(find_accountID(head,temp_account),password))
                {
                    cout<<"请输入你要修改的密码:";
                    string RecorrectPassword;
                    cin>>RecorrectPassword;
                    find_accountID(head,temp_account)->account.password=RecorrectPassword;
                    flag=1;
                    break;
                }
                else if (password=="0")
                {
                    flag=1;
                    break;
                }
                else
                {
                    cout<<"密码错误，请重新输入:";
                }
            }
            if (flag)break;
        }
    }

    
}