#include <iostream>
#include <windows.h>
#include "banklist.h"
#include "deposit&withdraw.h"
using std::cin, std::cout, std::endl;

int main()
{
    SetConsoleOutputCP(936); 
    SetConsoleCP(936);
    cout<<"\nHello, this is lxh's test file.\n"<<endl;
    BankListNode *list = createList();
    Account acc1 = {"LXH001", "LXH", true, "password123", 100000, {2024, 1, 1}, false};
    Account acc2 = {"ABC002", "Alice", false, "alicepwd", 250000, {2023, 5, 15}, true};
    appendAccount(list, acc1);
    appendAccount(list, acc2);
    saveToFile(list, "test_accounts.txt");
    auto *newList = createList();
    loadFromFile(newList, "test_accounts.txt");
    auto *current = newList->next;
    while (current != nullptr)
    {
        cout << "Account ID: " << current->account.accountID << ", Owner: " << current->account.ownerName
             << ", Balance: " << current->account.balance / 100.0 << ", Created on: "
             << current->account.creationDate.year << "-" << std::setw(2) << std::setfill('0') << current->account.creationDate.month
             << "-" << std::setw(2) << std::setfill('0') << current->account.creationDate.day
             << ", Type: " << (current->account.isFixed ? "Fixed" : "Savings") << endl;
        current = current->next;
    }
    return 0;
}