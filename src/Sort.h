#pragma once
#include<iostream>
#include<set>
#include<iomanip>
#include"banklist.h"
#ifdef _WIN32
#include <windows.h>
#endif

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
#ifdef _WIN32
        // 转换 UTF-8 到 wstring 以使用 Windows API
        auto toWString = [](const std::string& str) -> std::wstring {
            if (str.empty()) return L"";
            int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
            std::wstring wstrTo(size_needed, 0);
            MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
            return wstrTo;
        };

        std::wstring s1 = toWString(a.ownerName);
        std::wstring s2 = toWString(b.ownerName);

        // 使用 Windows API 进行拼音排序
        // LOCALE_ZH_CN (0x0804) 的默认排序 (SORT_DEFAULT) 即为拼音排序
        // 注意：SORT_CHINESE_PRC (0x2) 实际上是笔画排序，不要使用它！
        DWORD localeId = MAKELCID(MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), SORT_DEFAULT);
        int result = CompareStringW(localeId, 0, s1.c_str(), -1, s2.c_str(), -1);

        if (result == CSTR_EQUAL) {
            return a.accountID < b.accountID;
        }
        return result == CSTR_LESS_THAN;
#else
        // 非 Windows 平台回退到默认字符串比较
        if (a.ownerName==b.ownerName)return a.accountID<b.accountID;
        return a.ownerName < b.ownerName;
#endif
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