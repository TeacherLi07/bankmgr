#pragma once

#include "banklist.h"

void openAccount(BankListNode* head);
void cancelaccount(BankListNode* head);
void printAccount(const Account& acc);
void queryAccount(BankListNode* head, int choice, const string& targetID,
const string& targetName, const Date& targetDate);