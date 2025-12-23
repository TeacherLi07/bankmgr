#include"Sort.h"
BankListNode* SortByName(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    set<Account,NameCmp>ByName;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByName.insert(p->account);//把原链表的account通过set排序
    }
    BankListNode *dataHead= nullptr;
    BankListNode *tail =nullptr;
    for (const auto &it :ByName)
    {
        BankListNode *node = new BankListNode;
        node->account = it;
        node->next =nullptr;
        if (dataHead == nullptr){
            dataHead=node;
            tail=node;
        }
        else{
            tail->next=node;
            tail=node;
        }
    }
    BankListNode *newHead =new BankListNode;
    newHead->next=dataHead;
    return newHead;
}
//姓名排序实现函数
BankListNode* SortByMoney(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    set<Account,MoneyCmp>ByMoney;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByMoney.insert(p->account);//把原链表的account通过set排序
    }
    BankListNode *dataHead= nullptr;
    BankListNode *tail =nullptr;
    for (const auto &it :ByMoney)
    {
        BankListNode *node = new BankListNode;
        node->account = it;
        node->next =nullptr;
        if (dataHead == nullptr){
            dataHead=node;
            tail=node;
        }
        else{
            tail->next=node;
            tail=node;
        }
    }
    BankListNode *newHead =new BankListNode;
    newHead->next=dataHead;
    return newHead;
}
//金额排序实现函数
BankListNode* SortByAccount(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    set<Account,AccountCmp>ByAccount;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByAccount.insert(p->account);//把原链表的account通过set排序
    }
    BankListNode *dataHead= nullptr;
    BankListNode *tail =nullptr;
    for (const auto &it :ByAccount)
    {
        BankListNode *node = new BankListNode;
        node->account = it;
        node->next =nullptr;
        if (dataHead == nullptr){
            dataHead=node;
            tail=node;
        }
        else{
            tail->next=node;
            tail=node;
        }
    }
    BankListNode *newHead =new BankListNode;
    newHead->next=dataHead;
    return newHead;
}
//账号排序实现函数
