#pragma once
#include"banklist.h"


bool transfer_accounts(struct Account people,double money,char ch1,char ch2);//输入转账用户people，转账金额money，转账方银行ch1,收账方银行ch2
//返回true:输出该账户转账后的账户信息，返回false：提示该用户