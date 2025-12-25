#pragma once

#include <string>
using std::string;

#include <utility>
using std::swap;

#include<fstream>
#include <filesystem>
using std::ifstream;
using std::ofstream;
namespace fs = std::filesystem;

#include <sstream>
#include <iomanip>
using std::stringstream;


/**
 * @brief 日期结构体
 * ++ == != < > - 运算符均支持
 */
struct Date
{
    int year = 1970;
    int month = 1;
    int day = 1;
};

Date operator++(Date &d, int);
Date operator++(Date &d);
bool operator==(const Date &d1, const Date &d2);
bool operator!=(const Date &d1, const Date &d2);
bool operator<(const Date &d1, const Date &d2);
bool operator>(const Date &d1, const Date &d2);
int operator-(Date d1, Date d2);

bool isValid(const Date &d);

struct Account
{
    string accountID = "";
    string ownerName = "";
    bool gender = true; // true男性，false女性
    string password = "";
    long long balance = 0; // 以分为单位
    Date creationDate;
    bool isFixed = false; // true定期，false活期
};

bool operator==(const Account &a1, const Account &a2);

struct BankListNode
{
    Account account;
    BankListNode *next = nullptr;
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
 * @brief 删除指定账户
 * @param head 链表头节点指针
 * @param node 要删除的节点指针
 */
void deleteAccount(BankListNode *head, BankListNode *node);

// 改

/**
 * @brief 编辑指定节点的账户信息
 * @param node 要编辑的节点指针
 * @param newAccountData 新的账户信息
 */
void editAccount(BankListNode *node, const Account &newAccountData);

// 文件

/**
 * @brief 将账户信息转换为字符串格式，便于保存到文件
 * @param account 账户信息
 * @return 返回格式化后的字符串
 */
string accountToString(const Account &account);

/**
 * @brief 将字符串转换为账户信息
 * @param str 格式化后的字符串
 * @return 返回账户信息，若字符串格式错误则返回空账户(Account{})
 */
Account stringToAccount(const string &str);

/**
 * @brief 校验文件路径是否合法，可以是绝对或相对路径
 * @param filepath 文件路径字符串
 * @return true表示合法，false表示不合法
 */
bool isValidFilepath(const string &filepath);

/**
 * @brief 从文件加载账户信息到链表
 * @param head 链表头节点指针
 * @param filename 文件相对路径
 * @return true表示全部加载成功，false表示有账户加载失败
 */
bool loadFromFile(BankListNode *head, const string &filepath);

/**
 * @brief 将链表中的账户信息保存到文件
 * @param head 链表头节点指针
 * @param filename 文件相对路径
 * @return true表示全部保存成功，false表示保存失败或有账户为空
 */
bool saveToFile(BankListNode *head, const string &filepath);

