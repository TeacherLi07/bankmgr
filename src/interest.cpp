#include"interest.h"

long long interest(struct Account p,struct Date day1){//p为用户，day1 为存款到期日期
        Date day2 = p.creationDate;//开户日期
    int differ = day1 - day2;
    long long balance_1 = p.balance;//保存原存款
    if(!p.isFixed){//如果是活期
        for(;differ>=365;differ-=365){
            p.balance *= 1.0035;//活期每年利润
        }
        if(differ!=0)
            p.balance *= 1.00175;//不足一年当半年计算
    }
    else{
        int year = 0;
        for(;differ>=365;differ-=365){
            year++;
            if(year == 1) p.balance *= 1.0275;//定期第一年。
            else if(year == 2) p.balance *= 1.0335;//定期第二年。
            else p.balance *= 1.04;//定期第三年及之后的每一年。
        }
        if(differ!=0){//不足一年当半年计算
            if(year == 1) p.balance *= 1.01375;//定期第一年。
            else if(year == 2) p.balance *= 1.01675;//定期第二年。
            else p.balance *= 1.02;//定期第三年及之后的每一年。
        }
    }
    return p.balance - balance_1;
}