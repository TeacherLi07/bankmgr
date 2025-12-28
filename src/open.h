//----------------------------------------------------------------------------------------------
// Created on 2025-12-18
// Author: Li Zheyan
// the code is used to define the header function for  account manager including function as open, cancel, print and query
// Version 0.1 
//
//----------------------------------------------------------------------------------------------

#pragma once

#include "banklist.h"

void openAccount(BankListNode* head);
void cancelaccount(BankListNode* head);
void printAccount(const Account& acc);
void queryAccount(BankListNode* head, int choice, const string& targetID,const string& targetName, const Date& targetDate);