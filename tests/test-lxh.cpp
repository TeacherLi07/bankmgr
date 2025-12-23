#include <iostream>
#include "banklist.h"
#include "deposit&withdraw.h"
using std::cin, std::cout, std::endl;

int main()
{
    cout<<"\nHello, this is lxh's test file.\n"<<endl;
    BankListNode *list = createList();
    Account acc = {"LXH001", "LXH", true, "password123", 100000, {2024, 1, 1}, false};
    list = appendAccount(list, acc);
    return 0;
}