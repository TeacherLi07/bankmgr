#include "deposit&withdraw.h"
#include <iostream>
using std::cin;
using std::string;
//传入带头结点的链表
BankListNode* find_accountID(BankListNode* head, string accountID_0)
{
    if(head->next==nullptr)
    {
        return nullptr;
    }
    BankListNode* p=head->next;
    while(p!=nullptr)
    {
        if(p->account.accountID==accountID_0)
        {
            return p;
        }
        p=p->next;
    }
    return nullptr;
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

void show_all_accountIDs(BankListNode* head)
{
BankListNode* p=head->next;
    if(p==nullptr)
    {
        std::cout<<"该银行暂无账户信息！"<<'\n';
        return;
    }
    std::cout<<"该银行所有账户ID如下："<<'\n';
    while(p!=nullptr)
    {
        std::cout<<p->account.accountID<<'\n';
        p=p->next;
    }
}