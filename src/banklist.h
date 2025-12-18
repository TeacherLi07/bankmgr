#ifndef BANKLIST_H
#define BANKLIST_H

#include <string>
using std::string;

/**
 * @brief 日期结构体
 * ++ == != < > - 运算符均支持
 */
struct Date
{
    int year;
    int month;
    int day;
};

Date operator++(Date &d, int);
Date operator++(Date &d);
bool operator==(const Date &d1, const Date &d2);
bool operator!=(const Date &d1, const Date &d2);
bool operator<(const Date &d1, const Date &d2);
bool operator>(const Date &d1, const Date &d2);
int operator-(Date d1, Date d2);

struct Account
{
    string accountID;
    string ownerName;
    bool gender; // true男性，false女性
    string password;
    long long balance; // 以分为单位
    Date creationDate;
    bool isFixed; // true定期，false活期
};

struct BankListNode
{
    Account account;
    BankListNode *next;
};

// 建

/**
 * @brief 创建新链表
 * @return 返回头节点指针
 */
BankListNode *createList();

// 清

/**
 * @brief 删除链表，释放空间
 * @param head 链表头节点指针
 */
void destroyList(BankListNode *head);

// 判空

/**
 * @brief 判断链表是否为空
 * @param head 链表头节点指针
 * @return true表示空，false表示非空
 */
bool isEmpty(BankListNode *head);

// 增

/**
 * @brief 向链表尾部添加新账户
 * @param head 链表头节点指针
 * @param account 要插入的账户信息
 * @return 新节点指针
 */
BankListNode *appendAccount(BankListNode *head, const Account &account);

// 删

/**
 * @brief 删除指定账号的账户
 * @param head 链表头节点指针
 * @param accountID 账号
 * @return true表示账号存在且删除成功，false表示账号不存在
 */
bool deleteAccount(BankListNode *head, const string &accountID);

// 改

/**
 * @brief 编辑指定节点的账户信息
 * @param node 要编辑的节点指针
 * @param newAccountData 新的账户信息
 */
void editAccount(BankListNode *node, const Account &newAccountData);

// 查

/**
 * @brief 根据账号查找账户
 * @param head 链表头节点指针
 * @param accountID 账号
 * @return 找到返回该节点指针，未找到返回nullptr
 */
BankListNode *findByAccountID(BankListNode *head, const string &accountID);

// 文件

/**
 * @brief 从文件加载账户信息到链表
 * @param head 链表头节点指针
 * @param filename 文件相对路径
 * @return true表示加载成功，false表示失败
 */
bool loadFromFile(BankListNode *head, const string &filepath);

/**
 * @brief 将链表中的账户信息保存到文件
 * @param head 链表头节点指针
 * @param filename 文件相对路径
 * @return true表示保存成功，false表示失败
 */
bool saveToFile(BankListNode *head, const string &filepath);

#endif // BANKLIST_H
