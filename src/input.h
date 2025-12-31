#pragma once

#include <string>
using std::string;

#include "banklist.h"

/**
 * @brief 输入选项字符（带合法性校验）
 * @param choice 用户输入的选项字符
 */
void inputchoice(char &choice);

/**
 * @brief 输入仅包含数字的账号ID
 * @param accountID 输入的账号ID字符串
 */
void inputAccountID(string &accountID);

/**
 * @brief 输入性别（0-女，1-男）
 * @param gender 输入的性别，0为女，1为男
 */
void inputgender(int &gender);

/**
 * @brief 输入金额（以分为单位，支持小数点后两位）
 * @param balance 输入的金额（分）
 */
void inputmoney(long long &balance);

/**
 * @brief 输入日期（格式：yyyymmdd）
 * @param date 输入的日期结构体
 */
void inputdate(Date &date);

/**
 * @brief 输入账户类型（0-活期，1-定期）
 * @param isFixed 输入的账户类型，0为活期，1为定期
 */
void inputAccountType(int &isFixed);

/**
 * @brief 输入姓名（允许包含空格等字符）
 * @param name 输入的姓名字符串
 */
void inputName(string &name);

/**
 * @brief 输入密码（允许包含字符，但不允许包含空格）
 * @param password 输入的密码字符串
 */
void inputpassword(string &password);