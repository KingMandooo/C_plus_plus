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