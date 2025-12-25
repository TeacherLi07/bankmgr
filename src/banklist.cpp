#include "banklist.h"

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
    if (d.year < 1900 || d.month < 1 || d.month > 12 || d.day < 1)
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

string accountToString_old(const Account &account)
{
    string str;
    str += account.accountID + " ";
    str += account.ownerName + " ";
    str += (account.gender ? "男" : "女") + string(" ");
    str += account.password + " ";
    stringstream ss;
    ss<<std::fixed<<std::setprecision(2)<<account.balance / 100.0;
    str += ss.str() + " ";
    ss.str("");
    ss<<account.creationDate.year<<std::setw(2)<<std::setfill('0')<<account.creationDate.month<<std::setw(2)<<std::setfill('0')<<account.creationDate.day;
    str += ss.str() + " ";
    str += (account.isFixed ? "定期" : "活期");
    return str;
}

string accountToString(const Account &account)
{
    // 使用 std::format 手动添加引号，以便读取时 std::quoted 处理空格
    return std::format("\"{}\" \"{}\" {} \"{}\" {:.2f} {}{:02}{:02} {}", 
        account.accountID,
        account.ownerName,
        (account.gender ? "男" : "女"),
        account.password,
        account.balance / 100.0, // 自动转为浮点格式化
        account.creationDate.year, 
        account.creationDate.month, 
        account.creationDate.day,
        (account.isFixed ? "定期" : "活期")
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
        return Account{};
    }

    string extra;
    if (ss >> extra) return Account{}; 

    if(genderStr == "男")
        acc.gender = true;
    else if(genderStr == "女")
        acc.gender = false;
    else
        return Account{};
        
    // 处理余额
    if (balanceStr.length() < 4 || balanceStr[balanceStr.length() - 3] != '.') return Account{};
    balanceStr.erase(balanceStr.length() - 3, 1); // 移除小数点
    try {
        acc.balance = std::stoll(balanceStr); // 直接转为以分为单位的整数
    } catch (...) {
        return Account{};
    }

    // 处理日期
    if (dateStr.length() != 8) return Account{};
    try {
        acc.creationDate.year = std::stoi(dateStr.substr(0, 4));
        acc.creationDate.month = std::stoi(dateStr.substr(4, 2));
        acc.creationDate.day = std::stoi(dateStr.substr(6, 2));
    } catch (...) {
        return Account{};
    }
    if (!isValid(acc.creationDate))
        return Account{};

    if (typeStr == "定期")
        acc.isFixed = true;
    else if (typeStr == "活期")
        acc.isFixed = false;
    else return
        Account{};

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

bool loadFromFile(BankListNode *head, const string &filepath)
{
    if(!isValidPath(filepath))
        return false;

    ifstream infile(filepath);
    if (!infile.is_open())
        return false;

    bool status = true;
    auto *current = head;
    string line;
    while (std::getline(infile, line))
    {
        auto account = stringToAccount(line);
        if(account == Account{})
        {
            status = false; 
            continue;
        }
        auto *newNode = new BankListNode;
        newNode->account = account;
        newNode->next = nullptr;
        current->next = newNode;
        current = newNode;
    }
    return status;
}

bool saveToFile(BankListNode *head, const string &filepath)
{
    ifstream in (filepath);
    return true;
    if(!isValidPath(filepath))
        return false;

    ofstream outfile(filepath);
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