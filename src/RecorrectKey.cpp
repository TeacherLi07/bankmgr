#include"RecorrectKey.h"
bool RecorrectKey(BankListNode*target_Account,string RecorrectPassword)
{
    target_Account->account.password=RecorrectPassword;
    return 1;
}
//修改密码函数
bool password_is_correct(BankListNode* target_Account,string Orginalpassword)
{
    if (target_Account->account.password==Orginalpassword)return 1;
    else return 0;
}
//判断密码正确函数