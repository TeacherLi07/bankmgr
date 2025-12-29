#include "banklist.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include<iostream> 

// 辅助宏：强制字符串字面量为 UTF-8 编码，并转换为 const char* 以兼容 std::string 和 std::format
// 解决因 -fexec-charset=GBK 导致的字面量编码与文件内容(UTF-8)不一致的问题
#define U8(s) reinterpret_cast<const char*>(u8##s)

Date operator++(Date &d, int)
{
    Date temp = d; // 保存原始值用于返回
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);

    // 修改 d 本身
    d.day++;
    if (d.month == 2)
    {
        if (d.day > isr + daysInMonth[2])
        {
            d.day = 1;
            d.month++;
        }
    }
    else if (d.day > daysInMonth[d.month])
    {
        d.day = 1;
        d.month++;
        if (d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
    return temp; // 返回修改前的值
}

Date operator++(Date &d)
{
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);

    d.day++;
    if (d.month == 2)
    {
        if (d.day > isr + daysInMonth[2])
        {
            d.day = 1;
            d.month++;
        }
    }
    else if (d.day > daysInMonth[d.month])
    {
        d.day = 1;
        d.month++;
        if (d.month > 12)
        {
            d.month = 1;
            d.year++;
        }
    }
    return d; 
}

bool operator==(const Date &d1, const Date &d2)
{
    return (d1.year == d2.year) && (d1.month == d2.month) && (d1.day == d2.day);
}

bool operator!=(const Date &d1, const Date &d2)
{
    return !(d1 == d2);
}

bool operator<(const Date &d1, const Date &d2)
{
    if (d1.year != d2.year)
        return d1.year < d2.year;
    if (d1.month != d2.month)
        return d1.month < d2.month;
    return d1.day < d2.day;
}

bool operator>(const Date &d1, const Date &d2)
{
    if (d1.year != d2.year)
        return d1.year > d2.year;
    if (d1.month != d2.month)
        return d1.month > d2.month;
    return d1.day > d2.day;
}

int operator-(Date d1, Date d2)
{
    int d = 0, sign = 1;
    if (d1 == d2)
        return 0;
    if (d1 < d2)
    {
        swap(d1, d2);
        sign = -1;
    }
    while (d1 != d2)
    {
        ++d2;
        d++;
    }
    return d * sign;
}

bool operator==(const Account &a1, const Account &a2)
{
    return (a1.accountID == a2.accountID) &&
           (a1.ownerName == a2.ownerName) &&
           (a1.gender == a2.gender) &&
           (a1.password == a2.password) &&
           (a1.balance == a2.balance) &&
           (a1.creationDate == a2.creationDate) &&
           (a1.isFixed == a2.isFixed);
}

bool isValid(const Date &d)
{
    if (d.year < 1900 || d.year > 2500 || d.month < 1 || d.month > 12 || d.day < 1)
        return false;
    const int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isr = (d.year % 4 == 0 && d.year % 100 != 0) || (d.year % 400 == 0);
    int dim = daysInMonth[d.month];
    if (d.month == 2 && isr)
        dim++; // 闰年2月多一天
    return d.day <= dim;
}

BankListNode *createList()
{
    auto *head = new BankListNode;
    head->account = Account{};
    head->next = nullptr;
    return head;
}

void destroyList(BankListNode *head)
{
    auto *current = head;
    while (current != nullptr)
    {
        auto *tmp = current;
        current = current->next;
        delete tmp;
    }
}

bool isEmpty(BankListNode *head)
{
    return head->next == nullptr;
}

BankListNode *appendAccount(BankListNode *head, const Account &account)
{
    auto *newNode = new BankListNode;
    newNode->account = account;
    newNode->next = nullptr;

    auto *tail = head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    tail->next = newNode;
    return newNode;
}

void deleteAccount(BankListNode *head, BankListNode *node)
{
    auto *prev = head;
    while (prev->next != nullptr)
    {
        if (prev->next == node)
        {
            auto *tmp = prev->next;
            prev->next = tmp->next;
            delete tmp;
            return;
        }
        prev = prev->next;
    }
}

void editAccount(BankListNode *node, const Account &newAccountData)
{
    if (node != nullptr)
        node->account = newAccountData;
}

string accountToString(const Account &account)
{
    // 使用 std::format 手动添加引号，以便读取时 std::quoted 处理空格
    // 使用 U8 宏确保输出的中文字符为 UTF-8 编码
    return std::format("\"{}\" \"{}\" {} \"{}\" {:.2f} {}{:02}{:02} {}", 
        account.accountID,
        account.ownerName,
        (account.gender ? U8("男") : U8("女")),
        account.password,
        account.balance / 100.0, // 自动转为浮点格式化
        account.creationDate.year, 
        account.creationDate.month, 
        account.creationDate.day,
        (account.isFixed ? U8("定期") : U8("活期"))
    );
}

Account stringToAccount(const string &str)
{
    stringstream ss(str);
    Account acc;
    string genderStr, balanceStr, dateStr, typeStr;

    // 使用 std::quoted 读取带引号的字符串
    if (!(ss >> std::quoted(acc.accountID) 
             >> std::quoted(acc.ownerName) 
             >> genderStr 
             >> std::quoted(acc.password) 
             >> balanceStr 
             >> dateStr 
             >> typeStr))
    {
        // std::cout<<"Failed to parse account string: "<<str<<std::endl;
        return Account{};
    }

    string extra;
    if (ss >> extra)
    {   
        // std::cout<<"Extra data found: "<<extra<<std::endl;
        return Account{}; 
    }

    // 比较时使用 U8 宏，确保与读取到的 UTF-8 内容匹配
    if(genderStr == U8("男"))
        acc.gender = true;
    else if(genderStr == U8("女"))
        acc.gender = false;
    else
    {
        // std::cout<<"Invalid gender: "<<genderStr<<std::endl;
        return Account{};
    }
        
    // 处理余额
    if (balanceStr.length() < 4 || balanceStr[balanceStr.length() - 3] != '.') return Account{};
    balanceStr.erase(balanceStr.length() - 3, 1); // 移除小数点
    try {
        acc.balance = std::stoll(balanceStr); // 直接转为以分为单位的整数
    } catch (...) {
        // std::cout<<"Invalid balance: "<<balanceStr<<std::endl;
        return Account{};
    }

    // 处理日期
    if (dateStr.length() != 8)
    {
        // std::cout<<"Invalid date length: "<<dateStr<<std::endl;
        return Account{};
    }
    try {
        acc.creationDate.year = std::stoi(dateStr.substr(0, 4));
        acc.creationDate.month = std::stoi(dateStr.substr(4, 2));
        acc.creationDate.day = std::stoi(dateStr.substr(6, 2));
    } catch (...) {
        // std::cout<<"Invalid date: "<<dateStr<<std::endl;
        return Account{};
    }
    if (!isValid(acc.creationDate))
    {
        // std::cout<<"Date is not valid: "<<dateStr<<std::endl;
        return Account{};
    }

    if (typeStr == U8("定期"))
        acc.isFixed = true;
    else if (typeStr == U8("活期"))
        acc.isFixed = false;
    else
    {
        // std::cout<<"Invalid account type: "<<typeStr<<std::endl;
        return Account{};
    }

    // std::cout<<"Parsed account ID: "<<acc.accountID<<std::endl;
    return acc;
}

bool isValidPath(const string &filepath)
{
    if (filepath.empty()) return false;

    // Windows 非法字符校验 (除盘符 : 和路径分隔符 \ / 外)
    const string invalidChars = "*?\"<>|";
    if (filepath.find_first_of(invalidChars) != string::npos) return false;

    try {
        fs::path p(filepath);
        // 确保路径包含文件名，而不仅仅是目录或盘符
        if (!p.has_filename()) return false;
        
        if (p.has_parent_path() && !fs::exists(p.parent_path())) return false;
        
        return true;
    } catch (...) {
        return false;
    }
}

string getResourcePath(const string& filename) {
    
    fs::path currentPath = fs::current_path();
    
    // 向上查找 bankdata 目录
    fs::path p = currentPath;
    for (int i = 0; i < 5; ++i) { // 最多向上查找5层
        if (fs::exists(p / "bankdata") && fs::is_directory(p / "bankdata")) {
            return (p / "bankdata" / filename).string();
        }
        if (p.has_parent_path()) {
            p = p.parent_path();
        } else {
            break;
        }
    }

    // 如果找不到 bankdata 目录，默认拼接在当前目录下的 bankdata
    return (currentPath / "bankdata" / filename).string();
}

bool loadFromFile(BankListNode *head, const string &filename)
{
    // 强制设置控制台输入输出代码页为 UTF-8 (65001)
    // 确保 std::cout 能正确打印 UTF-8 字符而不乱码
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    #endif

    string standardPath = getResourcePath(filename);

    if(!isValidPath(standardPath))
        return false;

    ifstream infile(standardPath);
    if (!infile.is_open())
        return false;

    bool status = true;
    auto *current = head;
    string line;
    while (std::getline(infile, line))
    {
        // std::cout<<"Loading line: "<<line;
        auto account = stringToAccount(line);
        if(account == Account{})
        {
            status = false; 
            // std::cout<<" ... Failed (invalid format)\n";
            continue;
        }
        auto *newNode = new BankListNode;
        newNode->account = account;
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
        // std::cout<<" ... Success\n";
    }
    return status;
}

bool saveToFile(BankListNode *head, const string &filename)
{
    string fullPath = getResourcePath(filename);

    if(!isValidPath(fullPath))
        return false;

    ofstream outfile(fullPath);
    if (!outfile.is_open())
        return false;
    
    bool status = true;

    auto *current = head->next; 
    while (current != nullptr)
    {
        if(current->account == Account{}) 
        {
            current = current->next;
            status = false;
            continue; 
        }
        outfile << accountToString(current->account) << '\n';
        current = current->next;
    }
    return status;
}