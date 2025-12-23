#include "deposit&withdraw.h"
#include <iostream>
using std::cin;
using std::string;
//传入带头结点的链表
BankListNode* find_accountID(BankListNode* head, string accountID_0)
{
    if(head->next==NULL)
    {
        return NULL;
    }
    BankListNode* p=head->next;
    while(p!=NULL)//检查！
    {
        if(p->account.accountID==accountID_0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}

bool password_correct(BankListNode* p_node,string password_0)
{
    if(p_node->account.password==password_0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void depositmoney(BankListNode* p_node,long long dbalance)
{
    p_node->account.balance+=dbalance;
}

bool check_diposit_valid(BankListNode* p_node,long long withdraw)
{
    if(p_node->account.balance>=withdraw)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void withdrawmoney(BankListNode* p_node,long long withdraw)
{
    p_node->account.balance-=withdraw;
}