#include "RecorrectKey.h"
#include "input.h"
// 判断密码正确函数
bool password_is_correct(BankListNode *target_Account, string Orginalpassword)
{
    if (target_Account->account.password == Orginalpassword)
        return 1;
    else
        return 0;
}
// 修改密码函数
void RecorrectKey(BankListNode *head)
{
    cout << "请输入你要查询账户的编号: (输入0以退出)" << endl;
    string temp_account;
    while (1)
    {
        getline(cin, temp_account);
        if (temp_account == "0")
            return;
        else if (find_accountID(head, temp_account) == nullptr)
        {
            cout << "未找到该账户，请重新输入: " << endl;
            continue;
        }
        else
        {
            cout << "请输入你的原密码: " << endl;
            while (1)
            {
                string password;
                getline(cin, password);
                if (password == "0")
                {
                    printf("密码修改已取消！\n");
                    return;
                }
                if (password_is_correct(find_accountID(head, temp_account), password))
                {
                    while (1)
                    {
                        cout << "请输入你要修改的密码:(输入0以退出)" << endl;
                        string RecorrectPassword;
                        inputpassword(RecorrectPassword);
                        if(RecorrectPassword=="0")
                        {
                            printf("密码修改已取消！\n");
                            return;
                        }
                        else if (RecorrectPassword==find_accountID(head, temp_account)->account.password)
                        {
                            cout << "新密码不能与原密码相同，请重新输入:" << endl;
                            continue;
                        }
                        find_accountID(head, temp_account)->account.password = RecorrectPassword;
                        cout << "密码修改成功！\n";
                        return;
                    }
                }
                else
                {
                    cout << "密码错误，请重新输入: " << endl;
                }
            }
        }
    }
}