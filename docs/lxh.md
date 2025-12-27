# 详细设计
## 基本数据结构
### 日期
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

### 账户信息
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

### 链表节点
```cpp
struct BankListNode
{
    Account account;
    BankListNode *next = nullptr;
};
```
链表节点结构体包含账户信息和指向下一个节点的指针。在后续操作中，采用了带头指针的链表设计，方便操作。

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
- git与github相关操作不熟悉，多次调整了项目协作方式和分支管理方式
- 使用xmake构建，但是在main.cpp未完成前，需要用各人的测试cpp作为主函数测试，为此创建了多个xmake构建目标。

## 代码实现
