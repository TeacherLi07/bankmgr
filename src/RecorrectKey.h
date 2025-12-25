#include <iostream>
#include"deposit&withdraw.h"
using std::cin,std::cout,std::endl;
bool RecorrectKey(BankListNode*target_Account,string RecorrectPassword);
//传输要修改的用户的指针和要修改的密码
bool password_is_correct(BankListNode* target_Account,string Orginalpassword);
//传输用户的密码和要修改的用户的指针
