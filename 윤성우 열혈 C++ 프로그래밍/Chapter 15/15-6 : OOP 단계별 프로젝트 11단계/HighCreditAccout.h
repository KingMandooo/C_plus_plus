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
		if (money < 0)
			throw MinusException(money);

		NormalAccount::Deposit(money);   // 원금과 이자추가
		Account::Deposit((money * (speicalRate / 100.0))); // 특별이자추가
	}
};

#endif // !__HIGHTCREDIT_ACCOUNT__

