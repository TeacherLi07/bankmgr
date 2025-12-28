//----------------------------------------------------------------------------------------------
// Created on 2025-12-18
// Author: Li Zheyan
// the code is used to define the header function for  account manager including function as open, cancel, print and query
// Version 0.1 
//
//----------------------------------------------------------------------------------------------

#pragma once

#include "banklist.h"

/**
 * @brief 开户：创建新账户并添加到链表
 * @param head 链表头节点指针
 */
void openAccount(BankListNode* head);

/**
 * @brief 销户：删除指定账户
 * @param head 链表头节点指针
 */
void cancelaccount(BankListNode* head);

/**
 * @brief 打印账户信息到控制台
 * @param acc 账户信息
 */
void printAccount(const Account& acc);

/**
 * @brief 查询账户信息
 * @param head 链表头节点指针
 * @param choice 查询方式（0按ID，1按姓名，2按日期）
 * @param targetID 目标账户ID（当choice=0时有效）
 * @param targetName 目标姓名（当choice=1时有效）
 * @param targetDate 目标日期（当choice=2时有效）
 */
void queryAccount(BankListNode* head, int choice, const string& targetID,const string& targetName, const Date& targetDate);