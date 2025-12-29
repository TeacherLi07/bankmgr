#include"transfer_accounts.h"
#include"deposit&withdraw.h"
#include<iostream>
using std::cin,std::cout,std::getline;

void transfer_accounts(BankListNode* head,char choice_bank){
    string accountID_input;
    while (1) {
        cout << "请输入要转账的账户ID(输入0退出): ";
        getline(cin, accountID_input);
        
        // 检查是否要退出
        if (accountID_input == "0") {
            cout << "退出转账功能\n";
            return;
        }
        
        // 在链表中查找账户
        BankListNode* source_account = find_accountID(head, accountID_input);
        
        if (source_account == nullptr) {
            cout << "账户不存在，请重新输入！\n";
            continue;
        }
        
        // 账户存在，验证密码
        string password_input;
        while (true) {
            cout << "请输入账户密码(输入0退出): ";
            getline(cin, password_input);
            
            if (password_input == "0") {
                cout << "退出转账\n";
                return;
            }
            for(int i = 0; i < password_input.length(); i++) {
                if(password_input[i] == ' ') {
                    cout << "密码不能包含空格，请重新输入！\n";
                    continue;
                }
            }
            
            if (password_correct(source_account, password_input)) {
                cout << "密码验证成功！\n";
                break;
            } else {
                cout << "密码错误，请重新输入！\n";
            }
        }
        
        // 输入收款方银行代码
        char target_bank;
        while (1) {
            cout << "请输入收款方的账户所在的银行代码(a,b,c,d,e)(输入0退出): ";
            cin >> target_bank;
            target_bank = tolower(target_bank);
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (target_bank == '0') {
                cout << "退出转账\n";
                return;
            }
            
            if (target_bank >= 'a' && target_bank <= 'e') {
                break;
            } else {
                cout << "请输入正确的银行代码(a,b,c,d,e)！\n";
            }
        }
        
        // 输入收款方账户ID
        string target_accountID;
        while (1) {
            cout << "请输入收款方的账户ID(输入0退出): ";
            getline(cin, target_accountID);
            
            if (target_accountID == "0") {
                cout << "退出转账\n";
                return;
            }
            
            // 检查是否转账给自己（同一银行且同一账户）
            if (target_bank == choice_bank && target_accountID == accountID_input) {
                cout << "不能转账给自己！请重新输入收款方账户ID\n";
                continue;
            }
            
            // 查找收款方账户
            BankListNode* target_account = nullptr;
            
            if (target_bank == choice_bank) {
                // 同一银行，在当前链表中查找
                target_account = find_accountID(head, target_accountID);
            } else {
                // 不同银行，需要加载目标银行的链表
                BankListNode* target_head = createList();
                loadFromFile(target_head, std::format("{}.txt", target_bank));
                target_account = find_accountID(target_head, target_accountID);
                if (target_account) {
                    // 保存指针以便后续使用
                    target_account = find_accountID(target_head, target_accountID);
                    // 保存链表信息
                }
            }
            
            if (target_account == nullptr) {
                cout << "收款方账户不存在，请重新输入！\n";
            } else {
                // 找到收款方账户，继续输入转账金额
                double money;
                while (1) {
                    cout << "请输入转账金额(元)(输入0退出): ";
                    cin >> money;
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    
                    if (money == 0) {
                        cout << "退出转账\n";
                        return;
                    }
                    
                    if (money <= 0) {
                        cout << "转账金额必须大于0！\n";
                        continue;
                    }
                    
                    long long money_in_cents = money * 100;  // 转换为分
                    
                    // 计算手续费（跨行转账扣除1%，最高50元）
                    long long fee = 0;
                    if (target_bank != choice_bank) {
                        // 跨行转账，计算手续费
                        fee = money_in_cents * 0.01;  // 1%手续费
                        if (fee > 5000) {
                            fee = 5000;  // 最高50元
                        }
                    }
                    
                    // 检查余额是否足够（转账金额+手续费）
                    if (source_account->account.balance < money_in_cents + fee) {
                        cout << "余额不足！当前余额: " << source_account->account.balance / 100.0 
                             << "元，需要: " << (money_in_cents + fee) / 100.0 << "元\n";
                    } else {
                        // 执行转账
                        // 1. 扣减转账方余额
                        source_account->account.balance -= (money_in_cents + fee);
                        
                        // 2. 增加收款方余额
                        // 这里需要根据目标银行更新对应的数据文件
                        if (target_bank == choice_bank) {
                            // 同一银行，直接在当前链表中操作
                            target_account = find_accountID(head, target_accountID);
                            if (target_account) {
                                target_account->account.balance += money_in_cents;
                                // 保存到文件
                                saveToFile(head, std::format("bankdata\\{}.txt", choice_bank));
                            }
                        } else {
                            // 不同银行，需要加载目标银行文件，修改后保存
                            BankListNode* target_head = createList();
                            loadFromFile(target_head, std::format("bankdata\\{}.txt", target_bank));
                            BankListNode* target_acc = find_accountID(target_head, target_accountID);
                            if (target_acc) {
                                target_acc->account.balance += money_in_cents;
                                // 保存目标银行文件
                                saveToFile(target_head, std::format("bankdata\\{}.txt", target_bank));
                            }
                            
                            
                            // 保存转账方银行文件
                            saveToFile(head, std::format("bankdata\\{}.txt", choice_bank));
                        }
                        
                        // 输出转账成功信息
                        cout << "\n转账成功！\n";
                        cout << "转账金额: " << money << "元\n";
                        if (fee > 0) {
                            cout << "手续费: " << fee / 100.0 << "元\n";
                        }
                        // 显示转账方账户信息
                        cout << "\n转账方账户信息:\n";
                        cout << "账户ID: " << source_account->account.accountID << '\n';
                        cout << "账户姓名: " << source_account->account.ownerName << '\n';
                        cout << "账户余额: " << source_account->account.balance / 100.0 << "元\n";
                        
                        return;  // 转账完成，退出函数
                    }
                }
            }
        }
    }
}