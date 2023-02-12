
💙 BoundCheckArray.h 💙
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

