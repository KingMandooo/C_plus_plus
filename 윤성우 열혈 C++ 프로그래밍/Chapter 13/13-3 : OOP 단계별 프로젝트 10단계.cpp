
π BoundCheckArray.h π
#ifndef __BOUND_CHECK_ARRAY_H__
#define __BOUND_CHECK_ARRAY_H__

template <typename T>
class BoundCheckArray
{
private:
	T* arr;
	int arrlen;

	BoundCheckArray(const BoundCheckArray& copy) {}
	BoundCheckArray& operator= (const BoundCheckArray& ref) {}
public:
	BoundCheckArray(int len = 100) : arrlen(len)
	{
		arr = new T[len];
	}
	T& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	T operator[] (int idx) const      
	{                                   
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	T GetArrLen() const { return arrlen; }
	~BoundCheckArray() { delete[] arr; }
};

#endif // !__BOUND_CHECK_ARRAY_H__



π AccountHandler.h π
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

	void ShowMenu() const;       // λ©λ΄μΈλ ₯
	void MakeAccount();          // κ³μ’κ°μ€μ μν ν¨μ
	void DepositMoney();		     // μ     κΈ
	void WidthdrawMoney();		   // μΆ     κΈ
	void ShowAllAccInfo() const; // μμ‘μ‘°ν
	~AccountHandler();
protected:
	void MakeNormalAccout();   // λ³΄ν΅μκΈκ³μ’ μμ±
	void MakeCreditAccout();   // μ μ©μ λ’°κ³μ’ μμ±
};

#endif // _ACCOUNT_HANDLER__

