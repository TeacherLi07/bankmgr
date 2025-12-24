#pragma once
#include"banklist.h"

/**
 * @brief 计算利息函数
 * @param p 账户信息
 * @param day1 存款到期日期
 * @return 计算得到的利息（以分为单位）
 */
long long interest(struct Account p,struct Date day1);