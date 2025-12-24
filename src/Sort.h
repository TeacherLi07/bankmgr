#pragma once
#include<iostream>
#include<set>
#include"banklist.h"
using std::cin,std::cout,std::endl,std::set;

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
        return a.ownerName < b.ownerName;
    }
};

/**
 * @brief 创建用金额排序的结构体
 */
struct MoneyCmp{
    bool operator()(const Account &a, const Account &b) const{
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




