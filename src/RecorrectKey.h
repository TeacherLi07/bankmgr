#include <iostream>
#include"deposit&withdraw.h"
using std::cin,std::cout,std::endl;
void RecorrectKey(BankListNode*head);
//传输要修改的用户的指针
bool password_is_correct(BankListNode* target_Account,string Orginalpassword);
//传输用户的密码和要修改的用户的指针
