
ππ "μ μ ν ν΄λμ€μ λ±μ₯μ λ€λ₯Έ ν΄λμ€μ μ μλ₯Ό κ°κ²°νκ² ν΄ μ€λ€."


π Account.h π

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


π Account.cpp π

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
	cout << "κ³μ’ID: " << accID << endl;
	cout << "μ΄ λ¦: " << cusName << endl;
	cout << "μκΈμ‘: " << balance << endl << endl;
}

//Account::~Account() {}


π NormalAccount.h π

#ifndef __NORMAL__ACCOUNT_H__
#define __NORMAL__ACCOUNT_H__
#include "Account.h"
#include "String.h"

class NormalAccount : public Account     // λ³΄ν΅μκΈκ³μ’
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
		Account::Deposit(money); // μκΈμΆκ°
		Account::Deposit((money * (interRate / 100.0))); // μ΄μμΆκ°
	}
};

#endif // !__NORMAL__ACCOUNT_H__


π HighCreditAccout.h π

#ifndef __HIGHTCREDIT_ACCOUNT__
#define __HIGHTCREDIT_ACCOUNT__
#include "NormalAccount.h"
#include "String.h"

class HighCreditAccount : public NormalAccount // μ μ©μ λ’°κ³μ’
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
		NormalAccount::Deposit(money);   // μκΈκ³Ό μ΄μμΆκ°
		Account::Deposit((money * (speicalRate / 100.0))); // νΉλ³μ΄μμΆκ°
	}
};

#endif // !__HIGHTCREDIT_ACCOUNT__


π AccountHandler.cpp π

#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "HighCreditAccout.h"
#include "NormalAccount.h"

AccountHandler::AccountHandler() : accNum(0) {}

void AccountHandler::ShowMenu() const
{
	cout << "-----Menu-----" << '\n';
	cout << "1. κ³μ’κ°μ€\n";
	cout << "2. μ κΈ\n";
	cout << "3. μΆ κΈ\n";
	cout << "4. κ³μ’μ λ³΄ μ μ²΄ μΆλ ₯\n";
	cout << "5. νλ‘κ·Έλ¨ μ’λ£\n\n";
}

void AccountHandler::MakeAccount()
{
	int sel;
	cout << "[κ³μ’μ’λ₯μ ν]" << endl;
	cout << "1.λ³΄ν΅μκΈκ³μ’ ";
	cout << "2.μ μ©μ λ’°κ³μ’ " << endl;
	cout << "μ ν:  ";
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

	cout << "[λ³΄ν΅μκΈκ³μ’ κ°μ€]" << endl;
	cout << "κ³μ’ID: "; cin >> id;
	cout << "μ΄ λ¦: "; cin >> name;
	cout << "μκΈμ‘: "; cin >> balance;
	cout << "μ΄μμ¨: "; cin >> interRate;
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

	cout << "[λ³΄ν΅μκΈκ³μ’ κ°μ€]" << endl;
	cout << "κ³μ’ID: "; cin >> id;
	cout << "μ΄ λ¦: "; cin >> name;
	cout << "μκΈμ‘: "; cin >> balance;
	cout << "μ΄μμ¨: "; cin >> interRate;
	cout << "μ μ©λ±κΈ(1toA, 2toB, 3toC): "; cin >> creditLevel;
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

	cout << "[μ  κΈ]\n";
	cout << "κ³μ’ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "μκΈμ‘: "; cin >> money;
			accArr[i]->Deposit(money);
			cout << "μκΈμλ£" << endl << endl;
			return;
		}
	}
	cout << "μ ν¨νμ§ μλ ID μλλ€.\n\n";
}

void AccountHandler::WidthdrawMoney()
{
	int id, money;

	cout << "[μΆ  κΈ]\n";
	cout << "κ³μ’ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "μΆκΈμ‘: "; cin >> money;
			if (accArr[i]->Widthdraw(money) == 0)
				cout << "μμ‘λΆμ‘±\n";
			else
				cout << "μΆκΈμλ£\n\n";

			return;
		}
	}

	cout << "μ ν¨νμ§ μλ ID μλλ€.\n\n";
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


π String.h π

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


π String.cpp π

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
