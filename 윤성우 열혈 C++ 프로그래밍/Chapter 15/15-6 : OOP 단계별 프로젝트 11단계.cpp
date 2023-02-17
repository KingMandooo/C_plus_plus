
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
	int GetAccID() const;
	virtual void Deposit(int money);
	int Widthdraw(int money);
	void ShowAccInfo() const;
};

#endif // !__ACCOUNT_H__


💙 Account.cpp 💙

#include "BankingCommonDecl.h"
#include "Account.h"
#include "AccountException.h"
using namespace std;

Account::Account(int id, int money, String name) : accID(id), balance(money)
{
	cusName = name;
}

int Account::GetAccID() const { return accID; }

void Account::Deposit(int money)   
{
	if (money < 0)
		throw MinusException(money);
	balance += money;
}

int Account::Widthdraw(int money)  
{
	if (money < 0)
		throw MinusException(money);

	if (balance < money)
		throw InsuffException(balance, money);

	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "계좌ID: " << accID << endl;
	cout << "이 름: " << cusName << endl;
	cout << "입금액: " << balance << endl << endl;
}


💙 AccountHandler.h 💙

#ifndef _ACCOUNT_HANDLER__
#define _ACCOUNT_HANDLER__
#include "Account.h"
#include "BoundCheckArray.h"

class AccountHandler
{
private:
	BoundCheckArray<Account*> accArr;
	int accNum;
public:
	AccountHandler();
	void ShowMenu() const;       // 메뉴츌력
	void MakeAccount();          // 계좌개설을 위한 함수
	void DepositMoney();		     // 입     금
	void WidthdrawMoney();		   // 출     금
	void ShowAllAccInfo() const; // 잔액조회
	~AccountHandler();
protected:
	void MakeNormalAccout();   // 보통예금계좌 생성
	void MakeCreditAccout();   // 신용신뢰계좌 생성
};

#endif // _ACCOUNT_HANDLER__


💙 AccountHandler.cpp 💙

#include "BankingCommonDecl.h"
#include "AccountHandler.h"
#include "Account.h"
#include "NormalAccount.h"
#include "HighCreditAccout.h"
#include "String.h"

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

	while (true)
	{
		cout << "입금액: "; cin >> money;

		try
		{
			for (int i = 0; i < accNum; i++)
			{
				if (accArr[i]->GetAccID() == id)
				{
					accArr[i]->Deposit(money);
					cout << "입금완료" << endl << endl;
					return;
				}
			}
			cout << "유효하지 않는 ID 입니다.\n\n";
			return;
		}
		catch (MinusException& expt)
		{
			expt.ShowExceptionInfo();
			cout << "입금액만 재입력하세요." << endl;
		}
	}
}

void AccountHandler::WidthdrawMoney()
{
	int id, money;

	cout << "[출  금]\n";
	cout << "계좌ID: "; cin >> id;

	while (true)
	{
		cout << "출금액: "; cin >> money;
		
		try
		{
			for (int i = 0; i < accNum; i++)
			{
				if (accArr[i]->GetAccID() == id)
				{
					accArr[i]->Widthdraw(money);
					cout << "출금완료\n\n";
					return;
				}
			}
			cout << "유효하지 않는 ID 입니다.\n\n";
			return;
		}
		catch (MinusException& expt)
		{
			expt.ShowExceptionInfo();
			cout << "입금액만 재입력하세요." << endl;
		}
		catch (InsuffException& expt)
		{
			expt.ShowExceptionInfo();
			cout << "출금액만 재입력하세요." << endl;
		}
	}
}

AccountHandler::AccountHandler() : accNum(0) {}

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
