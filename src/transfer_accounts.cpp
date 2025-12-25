#include"transfer_accounts.h"

bool transfer_accounts(struct Account *people_1,struct Account *people_2,long long money,char ch1,char ch2){//people为转账的用户，money为转账金额，ch1为转账方银行，ch2为收账方银行
    if(ch1 == ch2){
        if(people_1->balance < money) return 0;//不满足转账条件。
        else{//满足转账条件，输出转账方转账后的账户信息。
            people_1->balance-=money;
            people_2->balance+=money;//收账方
        }
    }
    else{
        long long coin;//手续费
        coin = money*0.01;//手续费为转账金额的1%
        if(coin > 5000) coin = 5000;//手续费不超过5000分
        if(people_1->balance+coin < money) return 0;//不满足转账条件
        else {
            people_1->balance-=coin;//扣除手续费
            people_1->balance-=money;//满足转账条件，输出转账方转账后的账户信息。
            people_2->balance+=money;//收账方
        }
    }
    return 1;
}