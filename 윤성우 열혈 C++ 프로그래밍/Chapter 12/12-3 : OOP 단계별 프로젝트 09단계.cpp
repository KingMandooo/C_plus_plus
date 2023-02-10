
🎈🎈 "적절한 클래스의 등장은 다른 클래스의 정의를 간결하게 해 준다."


💙 Account.h 💙

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include "String.h"

class Account
{
private:
	int accID;    
	int balance;   
	String cusName;  

public:
	Account(int id, int money, String name);
	//Account(int id, int money, char* name);
	//Account(Account& copy);
	//Account& operator=(const Account& ref);

	int GetAccID() const;
	virtual void Deposit(int money);
	int Widthdraw(int money);
	void ShowAccInfo() const;
	//~Account();
};

#endif // !__ACCOUNT_H__


💙 Account.cpp 💙

#include <iostream>
#include "Account.h"
using namespace std;

Account::Account(int id, int money, String name) : accID(id), balance(money)
{
	//cusName = new char[strlen(name) + 1];
	//strcpy(cusName, name);
	cusName = name;
}

//Account::Account(Account& copy) {}

//Account& Account::operator=(const Account& ref) {}

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

//Account::~Account() {}


💙 NormalAccount.h 💙

#ifndef __NORMAL__ACCOUNT_H__
#define __NORMAL__ACCOUNT_H__
#include "Account.h"
#include "String.h"

class NormalAccount : public Account     // 보통예금계좌
{
private:
	int interRate;
public:
	//NormalAccount(int id, int money, char* name, int interest)
	NormalAccount(int id, int money, String name, int interest)
		: Account(id, money, name), interRate(interest)
	{}

	virtual void Deposit(int money)
	{
		Account::Deposit(money); // 원금추가
		Account::Deposit((money * (interRate / 100.0))); // 이자추가
	}
};

#endif // !__NORMAL__ACCOUNT_H__


💙 HighCreditAccout.h 💙

#ifndef __HIGHTCREDIT_ACCOUNT__
#define __HIGHTCREDIT_ACCOUNT__
#include "NormalAccount.h"
#include "String.h"

class HighCreditAccount : public NormalAccount // 신용신뢰계좌
{
private:
	int speicalRate;
public:
	//HighCreditAccount(int id, int money, char* name, int interest, int rank)
	HighCreditAccount(int id, int money, String name, int interest, int rank)
		: NormalAccount(id, money, name, interest), speicalRate(rank)
	{}

	virtual void Deposit(int money)
	{
		NormalAccount::Deposit(money);   // 원금과 이자추가
		Account::Deposit((money * (speicalRate / 100.0))); // 특별이자추가
	}
};

#endif // !__HIGHTCREDIT_ACCOUNT__


💙 AccountHandler.cpp 💙

#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "HighCreditAccout.h"
#include "NormalAccount.h"

AccountHandler::AccountHandler() : accNum(0) {}

void AccountHandler::ShowMenu() const
{
	cout << "-----Menu-----" << '\n';
	cout << "1. 계좌개설\n";
	cout << "2. 입 금\n";
	cout << "3. 출 금\n";
	cout << "4. 계좌정보 전체 출력\n";
	cout << "5. 프로그램 종료\n\n";
}

void AccountHandler::MakeAccount()
{
	int sel;
	cout << "[계좌종류선택]" << endl;
	cout << "1.보통예금계좌 ";
	cout << "2.신용신뢰계좌 " << endl;
	cout << "선택:  ";
	cin >> sel;

	if (sel == NORMAL)
		MakeNormalAccout();
	else
		MakeCreditAccout();
}

void AccountHandler::MakeNormalAccout()
{
	int id;
	//char name[NAME_LEN];
	String name;
	int balance;
	int interRate;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << "이자율: "; cin >> interRate;
	cout << endl;

	accArr[accNum++] = new NormalAccount(id, balance, name, interRate);
}

void AccountHandler::MakeCreditAccout()
{
	int id;
	//char name[NAME_LEN];
	String name;
	int balance;
	int interRate;
	int creditLevel;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << "이자율: "; cin >> interRate;
	cout << "신용등급(1toA, 2toB, 3toC): "; cin >> creditLevel;
	cout << endl;

	switch (creditLevel)
	{
	case 1:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_A);
		break;
	case 2:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
		break;
	case 3:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
		break;
	}
}

void AccountHandler::DepositMoney()
{
	int money, id;

	cout << "[입  금]\n";
	cout << "계좌ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "입금액: "; cin >> money;
			accArr[i]->Deposit(money);
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않는 ID 입니다.\n\n";
}

void AccountHandler::WidthdrawMoney()
{
	int id, money;

	cout << "[출  금]\n";
	cout << "계좌ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "출금액: "; cin >> money;
			if (accArr[i]->Widthdraw(money) == 0)
				cout << "잔액부족\n";
			else
				cout << "출금완료\n\n";

			return;
		}
	}

	cout << "유효하지 않는 ID 입니다.\n\n";
}

void AccountHandler::ShowAllAccInfo() const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}

AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accNum; i++)
		delete accArr[i];
}


💙 String.h 💙

#ifndef __STRING_H__
#define __STRING_H__
#include "BankingCommonDecl.h"

class String
{
private:
	int len;
	char* str;
public:
	String();
	String(const char* s);
	String(const String& s);
	~String();
	String& operator=(const String& s);
	String& operator+=(const String& s);
	bool operator==(const String& s);
	String operator+ (const String& s);

	friend ostream& operator<<(ostream& os, const String& copy);
	friend istream& operator>>(istream& is, String& copy);
};
#endif // !__STRING_H__


💙 String.cpp 💙

#include "String.h"

String::String()
{
	len = 0;
	str = NULL;
}

String::String(const char* s)
{
	len = strlen(s) + 1;
	str = new char[len];
	strcpy(str, s);
}

String::String(const String& s)
{
	len = s.len;
	str = new char[len];
	strcpy(str, s.str);
}

String::~String()
{
	if (str != NULL)
		delete[]str;
}

String& String::operator=(const String& s)
{
	if (str != NULL)
		delete[] str;
	len = s.len;
	str = new char[len];
	strcpy(str, s.str);
	return *this;
}

String& String::operator+=(const String& s)
{
	len += (s.len - 1);
	char* tempstr = new char[len];
	strcpy(tempstr, str);
	strcat(tempstr, s.str);

	if (str != NULL)
		delete[] str;
	str = tempstr;
	return *this;
}

bool String::operator==(const String& s)
{
	return strcmp(str, s.str) ? false : true;
}

String String::operator+ (const String& s)
{
	char* tempstr = new char[len + s.len - 1];
	strcpy(tempstr, str);
	strcat(tempstr, s.str);

	String temp(tempstr);
	delete[] tempstr;
	return temp;
}

ostream& operator<<(ostream& os, const String& copy)
{
	os << copy.str;
	return os;
}

istream& operator>>(istream& is, String& copy)
{
	char str[100];
	is >> str;
	copy = String(str);
	return is;
}
