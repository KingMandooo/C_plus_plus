💙 Account.h 💙

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

class Account
{
private:
	int accID;     
	int balance;   
	char* cusName;  

public:
	Account(int id, int money, char* name);
	Account(Account& copy);
	Account& operator=(const Account& ref);  // 대입연산자 오버로딩

	int GetAccID() const;
	virtual void Deposit(int money);
	int Widthdraw(int money);
	void ShowAccInfo() const;
	~Account();
};

#endif // !__ACCOUNT_H__


💙 Account.cpp 💙

#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(int id, int money, char* name) : accID(id), balance(money)
{
	cusName = new char[strlen(name) + 1];
	strcpy(cusName, name);
}

Account::Account(Account& copy) : accID(copy.accID), balance(copy.balance)
{
	cusName = new char[strlen(copy.cusName) + 1];
	strcpy(cusName, copy.cusName);
}

Account& Account::operator=(const Account& ref)   // 대입연산자 오버로딩
{
	accID = ref.accID;
	balance = ref.balance;

	delete[] cusName;
	cusName = new char[strlen(ref.cusName) + 1];
	strcpy(cusName, ref.cusName);
	return *this;
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)   
{
	balance += money;
}

int Account::Widthdraw(int money)  
{
	if (balance < money)
		return 0;

	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "계좌ID: " << accID << endl;
	cout << "이 름: " << cusName << endl;
	cout << "입금액: " << balance << endl << endl;
}

Account::~Account()
{
	delete[] cusName;
}


💙 AccountHandler.h 💙

#ifndef _ACCOUNT_HANDLER__
#define _ACCOUNT_HANDLER__
#include "Account.h"
#include "AccountArray.h"

class AccountHandler
{
private:
	BoundCheckAccountPtrArray accArr;   // 변경된 부분
	int accNum;
public:
	AccountHandler();

	void ShowMenu() const;     
	void MakeAccount();          
	void DepositMoney();		     
	void WidthdrawMoney();		 
	void ShowAllAccInfo() const; 
	~AccountHandler();
protected:
	void MakeNormalAccout();   
	void MakeCreditAccout();  
};

#endif // _ACCOUNT_HANDLER__


💙 AccountArray.h 💙

#ifndef __ACCOUN_ARRAY_H__
#define __ACCOUN_ARRAY_H__

#include "Account.h"
typedef Account* ACCOUNT_PTR;

class BoundCheckAccountPtrArray
{
private:
	ACCOUNT_PTR* arr;
	int arrlen;
	BoundCheckAccountPtrArray(const BoundCheckAccountPtrArray& arr) {}
	BoundCheckAccountPtrArray& operator=(const BoundCheckAccountPtrArray& arr) {}

public:
	BoundCheckAccountPtrArray(int len = 100);
	ACCOUNT_PTR& operator[] (int idx);
	ACCOUNT_PTR operator[] (int idx) const;
	int GetArrLen() const;
	~BoundCheckAccountPtrArray();
};
#endif


💙 AccountArray.cpp 💙

#include "BankingCommonDecl.h"
#include "AccountArray.h"

BoundCheckAccountPtrArray::BoundCheckAccountPtrArray(int len) : arrlen(len)
{
	arr = new ACCOUNT_PTR[len];
}

ACCOUNT_PTR& BoundCheckAccountPtrArray::operator[](int idx)
{
	if (idx < 0 || idx >= arrlen)
	{
		cout << "Array index out of bound exception" << endl;
		exit(1);
	}
	return arr[idx];
}

ACCOUNT_PTR BoundCheckAccountPtrArray::operator[](int idx) const
{
	if (idx < 0 || idx >= arrlen)
	{
		cout << "Array index out of bound exception" << endl;
		exit(1);
	}
	return arr[idx];
}

int BoundCheckAccountPtrArray::GetArrLen() const
{
	return arrlen;
}

BoundCheckAccountPtrArray::~BoundCheckAccountPtrArray()
{
	delete[] arr;
}
