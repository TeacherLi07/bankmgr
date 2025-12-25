#include"transfer_accounts.h"

bool transfer_accounts(struct Account *people_1,struct Account *people_2,double money,char ch1,char ch2){//people为转账的用户，money为转账金额，ch1为转账方银行，ch2为收账方银行
    int flag = 1;//判断满不满足转账条件，1为满足，0为不满足
    long long money_1 = 100*money;//使金额以分为单位
    if(ch1 == ch2){
        if(people_1->balance < money_1) flag = 0;//不满足转账条件。
        else{//满足转账条件，输出转账方转账后的账户信息。
            people_1->balance-=money_1;
            people_2->balance+=money_1;//收账方
        }
    }
    else{
        long long coin;//手续费
        coin = money_1*0.01;//手续费为转账金额的1%
        if(coin > 5000) coin = 5000;//手续费不超过5000分
        people_1->balance-=coin;
        if(people_1->balance < money_1) flag = 0;//不满足转账条件
        else {
            people_1->balance-=money_1;//满足转账条件，输出转账方转账后的账户信息。
            people_2->balance+=money_1;//收账方
        }
    }
    return flag;
}