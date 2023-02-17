#ifndef __NORMAL__ACCOUNT_H__
#define __NORMAL__ACCOUNT_H__
#include "Account.h"
#include "String.h"
#include "AccountException.h"

class NormalAccount : public Account     // 보통예금계좌
{
private:
	int interRate;
public:
	NormalAccount(int id, int money, String name, int interest)
		: Account(id, money, name), interRate(interest)
	{}
	virtual void Deposit(int money)
	{
		if (money < 0)
			throw MinusException(money);

		Account::Deposit(money); // 원금추가
		Account::Deposit((money * (interRate / 100.0))); // 이자추가
	}
};

#endif // !__NORMAL__ACCOUNT_H__


