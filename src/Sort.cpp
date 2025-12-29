#include"Sort.h"
BankListNode* SortByName(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    multiset<Account,NameCmp>ByName;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByName.insert(p->account);//把原链表的account通过multiset排序
    }
    BankListNode *p =head->next;
    for (const auto &it :ByName)
    {
        p->account=it;
        p=p->next;
    }
    return head;
}
//姓名排序实现函数
BankListNode* SortByMoney(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    multiset<Account,MoneyCmp>ByMoney;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByMoney.insert(p->account);//把原链表的account通过multiset排序
    }
    BankListNode *p =head->next;
    for (const auto &it :ByMoney)
    {
        p->account=it;
        p=p->next;
    }
    return head;
}
//金额排序实现函数
BankListNode* SortByAccount(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    multiset<Account,AccountCmp>ByAccount;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByAccount.insert(p->account);//把原链表的account通过multiset排序
    }
    BankListNode *p =head->next;
    for (const auto &it :ByAccount)
    {
        p->account=it;
        p=p->next;
    }
    return head;
}
//账号排序实现函数
BankListNode* SortByDate(BankListNode *head)
{
    if (head->next==nullptr)return nullptr;//如果是空，直接返回
    multiset<Account,DateCmp>ByDate;
    for (BankListNode *p =head->next;p!=nullptr;p = p->next)
    {
        ByDate.insert(p->account);//把原链表的account通过multiset排序
    }
    BankListNode *p =head->next;
    for (const auto &it :ByDate)
    {
        p->account=it;
        p=p->next;
    }
    return head;
}
//开户日期排序实现函数
void Sort(BankListNode *head)
{
    cout<<"欢迎使用排序功能(输入1为账户排序,2为开户人姓名排序,3为金额排序,4为开户日期排序,0为退出排序功能):\n";
    string choice;
    cin>>choice;
    if (choice!="0")
    {
        while (choice!="1"&&choice!="2"&&choice!="3"&&choice!="4")
    {
        cout<<"没有这个选项,请重新输入:\n";
        cin>>choice;
    }
    if (choice=="1")
    {
        SortByAccount(head);
        print_whole_account(head);
    }
    else if (choice=="2")
    {
        SortByName(head);
        print_whole_account(head);
    }
    else if (choice=="3")
    {
        SortByMoney(head);
        print_whole_account(head);
    }
    else
    {
        SortByDate(head);
        print_whole_account(head);
    }
    }
}
//排序逻辑实现函数
void print_whole_account(BankListNode* head)
{
    BankListNode* p=head->next;
    if(p==nullptr)
    {
        cout<<"当前银行无任何账户信息！\n"<<endl;
        return;
    }
    while(p!=nullptr)
    {
        cout<<"账户ID: "<<p->account.accountID<<'\n';
        cout<<"账户姓名: "<<p->account.ownerName<<'\n';
        cout<<"账户性别: "<< (p->account.gender ? "男" : "女")<<'\n';
        cout<<"账户余额: "<< std::fixed << std::setprecision(2) << p->account.balance/100.0<<'\n';      
        cout<<"账户创建日期: "<<p->account.creationDate.year<<"-"<<p->account.creationDate.month<<"-"<<p->account.creationDate.day<<'\n';
        cout<<"账户类型: "<<(p->account.isFixed ? "定期" : "活期")<<'\n';
        cout<<"---------------------------"<<'\n';
        p=p->next;
    }
}