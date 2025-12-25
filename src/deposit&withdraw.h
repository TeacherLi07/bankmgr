#pragma once
#include "banklist.h"
BankListNode* find_accountID(BankListNode* head, string accountID_0);
bool password_correct(BankListNode* p_node,string password_0);
void depositmoney(BankListNode* p_node,long long dbalance);
bool check_diposit_valid(BankListNode* p_node,long long withdraw);
void withdrawmoney(BankListNode* p_node,long long withdraw);