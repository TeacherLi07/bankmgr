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

string accountToString(const Account &account)
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

Account stringToAccount(const string &str)
{
    stringstream ss(str);
    string buf[7];
    for(int i=0;i<7;i++)
    {
        if (!(ss >> buf[i])) return Account{};
    }
    string extra;
    if (ss >> extra) return Account{}; 

    Account acc;
    acc.accountID = buf[0];
    acc.ownerName = buf[1];

    if(buf[2] == "男")
        acc.gender = true;
    else if(buf[2] == "女")
        acc.gender = false;
    else
        return Account{};
        
    acc.password = buf[3];
    
    string bStr = buf[4];
    if (bStr.length() < 4 || bStr[bStr.length() - 3] != '.') return Account{};
    bStr.erase(bStr.length() - 3, 1); // 移除小数点
    try {
        acc.balance = std::stoll(bStr); // 直接转为以分为单位的整数
    } catch (...) {
        return Account{};
    }

    if (buf[5].length() != 8) return Account{};
    try {
        acc.creationDate.year = std::stoi(buf[5].substr(0, 4));
        acc.creationDate.month = std::stoi(buf[5].substr(4, 2));
        acc.creationDate.day = std::stoi(buf[5].substr(6, 2));
    } catch (...) {
        return Account{};
    }
    if (!isValid(acc.creationDate))
        return Account{};

    if (buf[6] == "定期")
        acc.isFixed = true;
    else if (buf[6] == "活期")
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
        outfile << accountToString(current->account) << std::endl;
        current = current->next;
    }
    return status;
}