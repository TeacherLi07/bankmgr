# 数据结构设计
## 日期
```cpp
struct Date
{
int year = 1970;
int month = 1;
int day = 1;
};
```
单独建立日期结构，并重载相关数学符号，方便日期间比较和计算
```cpp
Date operator++(Date &d, int);
Date operator++(Date &d);
bool operator==(const Date &d1, const Date &d2);
bool operator!=(const Date &d1, const Date &d2);
bool operator<(const Date &d1, const Date &d2);
bool operator>(const Date &d1, const Date &d2);
int operator-(Date d1, Date d2);
```
用于判断日期是否有效的函数
```cpp
bool isValidDate(const Date &date);
```

## 账户信息
```cpp
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
```
账户信息结构体中包含所有必要字段，包括：
- 账户ID，字符串
- 拥有者姓名，字符串
- 性别，布尔值
- 密码，字符串
- 余额，以分为单位的长整型
- 开户日期，日期结构体
- 是否为定期账户，布尔值

重载账户==运算符，主要用于判断空账户。

## 链表节点
```cpp
struct BankListNode
{
Account account;
BankListNode *next = nullptr;
};
```
链表节点结构体包含账户信息和指向下一个节点的指针。在后续操作中，采用了带头指针的链表设计，方便操作。

# 详细设计
## 链表功能
函数`BankListNode *createList();`用于创建链表头节点。

函数`void destroyList(BankListNode *head);`销毁整条链表，释放内存。

函数`bool isEmpty(BankListNode *head);`判断链表是否为空。

函数`BankListNode *appendAccount(BankListNode *head, const Account &account);`在链表末尾添加账户信息。

函数`void deleteAccount(BankListNode *head, BankListNode *node);`删除指定节点。

函数`void editAccount(BankListNode *node, const Account &newAccountData);`修改指定节点的账户信息。

## 文件操作
函数`string accountToString(const Account &account);`将账户信息转换为字符串格式，便于文件存储。其中：
- 对于原本就为字符串的字段，添加引号存储，以兼容可能存在的空格。
- 对于余额，将分转换为元为单位的两位小数格式存储。
- 对于日期，采用YYYYMMDD格式存储。

函数`Account stringToAccount(const string &str);`将字符串格式的账户信息转换为账户结构体。字符串格式错误时返回空的账户结构体。

函数`bool isValidFilepath(const string &filepath);`用于判断文件路径是否合法。

函数`string getResourcePath(const string& filename);`从当前执行目录向上遍历，查找资源文件所在路径，返回标准化的文件路径字符串。

函数`bool loadFromFile(BankListNode *head, const string &filepath);`从指定文件加载账户信息到链表。

函数`bool saveToFile(BankListNode *head, const string &filepath);`将链表中的账户信息保存到指定文件中。

# 调试过程中的问题
## 协作和构建配置
git与github相关操作不熟悉，多次调整了项目协作方式和分支管理方式。

使用xmake构建，但是在main.cpp未完成前，需要用各人的测试cpp作为主函数测试，为此创建了多个xmake构建目标。

## 代码实现
### 头文件与源文件分离的问题
项目规划时我们便决定采用头文件与源文件分离的方式进行项目设计，但是在实际操作中，我们在不断试错、摸索中，学习到了`#include`的使用规范，了解到了`#pragma once`和宏定义防止重复包含的作用，最终完成了这一多文件架构。

### 中文文字编码问题
本项目的中文编码分为代码存储编码、数据存储编码、控制台显示编码、可执行文件内字符串编码等多个层面。

首先确定代码文件和数据文件均使用UTF-8编码存储，但由于Windows控制台使用GBK，一开始设置可执行文件内字符串为GBK，消除了显示乱码问题。

但是后来发现，在读入UTF-8字符串后，与可执行文件中的GBK字符串进行比较时会失败，导致文件读入功能始终不可用。

最终统一所有编码为UTF-8，使用相关函数在控制台输出前进行编码转换，解决了所有编码问题。

### 文件路径问题
由于我们使用xmake构建项目，默认的可执行文件路径为build目录下，而银行数据文件位于根目录下的`bankdata/`目录中，同时又要兼容最终用户运行时可执行文件与数据文件位于同一目录的情况。

最终使用逐层向上查找的方式，主动查找数据文件路径，解决了该问题。

### 处理含空格字符串的问题
课堂上，我们常用的读入含空格字符串的方法是使用`getline`函数，但是在本项目中，账户信息的每个字段均需要从一行字符串中提取出来，即使使用`getline`，仍然需要对整行字符串进行解析。空格会干扰解析流程。

解决方案是使用引号括起所有字符串后保存，读入时使用`std::quote`。

# 功能测试
## 结构体
测试了各结构体的基本赋值、空值初始化功能。对于`Date`结构体，测试了各重载运算符的功能，特别是在含闰年等边界情况下的运算正确性。

## 链表
测试了链表的创建、销毁、判空、添加节点、删除节点、修改节点等功能，确认了对空链表、头结点等边界情况的正确处理。

## 文件
对于字符串向账户信息的转换，充分考虑了各种可能的错误输入，测试了缺少字段、字段格式错误等情况返回空结构体。另测试了对含空格项的正确读取。

对于账户信息向字符串的转换，测试了各种字段内容，尤其是含空格的字符串，确认了写入格式正确，且可以被正常读取。

对于实际文件读写操作，测试了文件在不同位置下均能正确被读取，测试了文件不存在时能够在写入时新建。

# 总结
在程序设计能力上，本项目让我更加熟练地掌握了链表的设计与实现，理解了文件读写与字符串处理的相关知识。

在工程能力上，本项目是我首次运用xmake进行项目构建管理的尝试，学习了相关配置方法，尝试了头文件与源文件分离的项目结构设计，抛弃了写`#include<bits/stdc++.h>`和`using namespace std;`的习惯，使项目代码更加规范。在分离头文件与源文件的过程中，我进一步学习了预处理指令，也加深了对C++编译链接过程的理解。与中文编码斗智斗勇的经历也是日常算法题无法弥补的宝贵经验。

在团队协作上，本项目也是我首次使用git与github进行多人协作开发的尝试。我在不断试错中学习，同时指导队友配置环境、编译代码、提交和同步代码、合并分支，与同伴们共同进步。