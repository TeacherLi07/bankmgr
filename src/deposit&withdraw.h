#pragma once

#include "banklist.h"

/**
 * 以accountID为关键字，查找对应节点
 * @param head 链表头节点指针
 * @param accountID_0 目标账户ID
 * @return 找到则返回对应节点指针，未找到则返回nullptr
 */
BankListNode* find_accountID(BankListNode* head, string accountID_0);


/**
 * @brief 验证密码是否正确
 * @param p_node 目标节点指针
 * @param password_0 输入的密码
 * @return 密码正确返回true，否则返回false
 */
bool password_correct(BankListNode* p_node,string password_0);

/**
 * @brief 存款操作
 * @param p_node 目标节点指针
 * @param dbalance 存款金额（以分为单位）
 */ 
void depositmoney(BankListNode* p_node,long long dbalance);

/**
 * @brief 检查取款是否合法
 * @param p_node 目标节点指针
 * @param withdraw 取款金额（以分为单位）
 * @return 合法返回true，否则返回false
 */
bool check_diposit_valid(BankListNode* p_node,long long withdraw);

/**
 * @brief 取款操作
 * @param p_node 目标节点指针
 * @param withdraw 取款金额（以分为单位）
 */
void withdrawmoney(BankListNode* p_node,long long withdraw);