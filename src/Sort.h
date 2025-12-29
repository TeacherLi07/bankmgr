#pragma once
#include<iostream>
#include<set>
#include<iomanip>
#include"banklist.h"
using std::cin,std::cout,std::endl,std::multiset;
BankListNode* SortByName(BankListNode *head);

/**
 * @brief 传输结构体成员的头指针(用姓名排序的函数)
 * @param head 链表头节点指针
 */
BankListNode* SortByName(BankListNode *head);

/**
 * @brief 传输结构体成员的头指针(用金额排序的函数)
 * @param head 链表头节点指针
 */
BankListNode* SortByMoney(BankListNode *head);

/**
 * @brief 传输结构体成员的头指针(用账号排序的函数)
 * @param head 链表头节点指针
 */
BankListNode* SortByAccount(BankListNode *head);

/**
 * @brief 创建用姓名排序的结构体
 */
struct NameCmp{
    bool operator()(const Account &a, const Account &b) const{
        if (a.ownerName==b.ownerName)return a.accountID<b.accountID;
        return a.ownerName < b.ownerName;
    }
};

/**
 * @brief 创建用金额排序的结构体
 */
struct MoneyCmp{
    bool operator()(const Account &a, const Account &b) const{
        if (a.balance==b.balance)return a.accountID<b.accountID;
        return a.balance > b.balance;
    }
};


/**
 * @brief 创建用账户ID排序的结构体
 */
struct AccountCmp{
    bool operator()(const Account &a, const Account &b) const{
        return a.accountID < b.accountID;
    }
};
/**
 * @brief 创建用开户日期排序的结构体
 */
struct DateCmp{
    bool operator()(const Account &a,const Account &b) const{
        if (a.creationDate.year  != b.creationDate.year)
            return a.creationDate.year  < b.creationDate.year;
        if (a.creationDate.month != b.creationDate.month)
            return a.creationDate.month < b.creationDate.month;
        if (a.creationDate.day   != b.creationDate.day)
            return a.creationDate.day   < b.creationDate.day;
        return a.accountID < b.accountID;
    }
};
/**
 * @brief 排序逻辑实现函数
 */
void Sort(BankListNode *head);
/**
 * @brief 打印链表
 */
void print_whole_account(BankListNode* head);