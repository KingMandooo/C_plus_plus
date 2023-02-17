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