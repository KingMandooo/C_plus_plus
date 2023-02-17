
 지금까지는 기본 자료형 데이터만을 예외 데이터로 사용했는데, 클래스의 객체도 예외 데이터가 될 수 있고
 또 이것이 보다 일반적인 방법이다.
   
-----------------------------------------------------------------------

🟢 예외 클래스와 예외객체

--> 예외발생을 알리는데 사용되는 객체를 가리켜 '예외객체'라 하며, 예외객체의 생성을 위해 정의된 클래스를 '예외 클래스'라 한다.
   
  
👇👇👇 아래코드가 복잡해 보여도 읽다보면 그닥 어려운 코드는 아니다.
   
#include <iostream>
#include <cstring>
using namespace std;

class DepositException // 입금
{
private:
	int reqDep;
public:
	DepositException(int money) : reqDep(money) {}
	void ShowExceptionReason()
	{
		cout << "[예외 메시지: " << reqDep << "는 입금불가]" << endl;
	}
};

class WithdrawException // 인출
{
private:
	int balance;
public:
	WithdrawException(int money) : balance(money) {}
	void ShowExceptionReason()
	{
		cout << "[예외 메시지: 잔액 " << balance << ", 잔액부족]" << endl;
	}
};

class Account
{
private:
	char accNum[50];
	int balance;
public:
	Account(const char* acc, int money) : balance(money)
	{
		strcpy(accNum, acc);
	}
	void Deposit(int money) throw (DepositException)
	{
		if (money < 0)
		{
			DepositException expn(money);
			throw expn;
		}
		balance += money;
	}
	void Withdraw(int money) throw (WithdrawException)
	{
		if (money > balance)
			throw WithdrawException(balance);
		balance -= money;
	}
	void ShowMyMoney()
	{
		cout << "잔고: " << balance << endl << endl;
	}
};

int main()
{
	Account myAcc("56789-827120", 5000);

	try
	{
		myAcc.Deposit(2000);
		myAcc.Deposit(-300);
	}
	catch (DepositException& expn)
	{
		expn.ShowExceptionReason();
	}
	myAcc.ShowMyMoney();

	try
	{
		myAcc.Withdraw(3500);
		myAcc.Withdraw(4500);
	}
	catch (WithdrawException& expn)
	{
		expn.ShowExceptionReason();
	}
	myAcc.ShowMyMoney();

	return 0;
}


/*
출력결과: [예외 메시지: -300는 입금불가]
          잔고: 7000

          [예외 메시지: 잔액 3500, 잔액부족]
          잔고: 3500
*/

-----------------------------------------------------------------------
  
🟢 상속관계에 있는 예외 클래스
  
👇👇👇 아래코드가 복잡해 보여도 읽다보면 그닥 어려운 코드는 아니다. (결과는 위의 코드와 동일)
   
#include <iostream>
#include <cstring>
using namespace std;

class AccountException
{
public:
	virtual void ShowExceptionReason() = 0;
};

class DepositException : public AccountException
{
private:
	int reqDep;
public:
	DepositException(int money) : reqDep(money) {}
	void ShowExceptionReason()
	{
		cout << "[예외 메시지: " << reqDep << "는 입금불가]" << endl;
	}
};

class WithdrawException : public AccountException
{
private:
	int balance;
public:
	WithdrawException(int money) : balance(money) {}
	void ShowExceptionReason()
	{
		cout << "[예외 메시지: 잔액 " << balance << ", 잔액부족]" << endl;
	}
};

class Account
{
private:
	char accNum[50];
	int balance;
public:
	Account(const char* acc, int money) : balance(money)
	{
		strcpy(accNum, acc);
	}
	void Deposit(int money) throw (AccountException)
	{
		if (money < 0)
		{
			DepositException expn(money);
			throw expn;
		}
		balance += money;
	}
	void Withdraw(int money) throw (AccountException)
	{
		if (money > balance)
			throw WithdrawException(balance);
		balance -= money;
	}
	void ShowMyMoney()
	{
		cout << "잔고: " << balance << endl << endl;
	}
};

int main()
{
	Account myAcc("56789-827120", 5000);

	try
	{
		myAcc.Deposit(2000);
		myAcc.Deposit(-300);
	}
	catch (AccountException& expn)   //🎈🎈 이렇게 상속관계를 묶으면 예외처리를 하나의 클래스로 단순화 시킬 수 있다.
	{
		expn.ShowExceptionReason();
	}
	myAcc.ShowMyMoney();

	try
	{
		myAcc.Withdraw(3500);
		myAcc.Withdraw(4500);
	}
	catch (AccountException& expn)
	{
		expn.ShowExceptionReason();
	}
	myAcc.ShowMyMoney();

	return 0;
}

-----------------------------------------------------------------------
  
🟢 예외의 전달방식에 따른 주의사항

try
{
  예외발생!!
}
catch(type1 param)   <-- 1차: 이 예외에 타당한 catch 블록인가?? 아니라면 다음 catch 블록
{

}
catch(type2 param)   <-- 2차: 이 예외에 타당한 catch 블록인가?? 아니라면 다음 catch 블록
{

}
catch(type3 param)   <-- 3차: 이 예외에 타당한 catch 블록인가?? 아니라면 다음 catch 블록
{

}

                   🎈🎈try 블록의 뒤를 이어서 등장하는 catch 블록이 둘 이상인 경우,
                        적절한 catch 블록을 찾는 과정은 다음과 같다.
                  
                        따라서 아래와 같이 코드를 짜면 예기치 못한 상황이 발생한다.
                          
                        아래의 코드를 짠 프로그래머는
                        BBB 예외객체는 catch(BBB& expn) 블록에 의해 처리가 되고, CCC 예외객체는 catch(CCC& expn) 블록에 의해서
                        처리가 되기를 바라고 있다.
                        
                        그러나 아래 코드는 서로 상속관계를 띄고 있기 때문에, CCC객체가 catch(AAA& expn)에 전달이 되어버리게 된다.
                          
  
#include <iostream>
using namespace std;

class AAA
{
public:
	void ShowYou() { cout << "AAA exception" << endl; }
};

class BBB : public AAA
{
public:
	void ShowYou() { cout << "BBB exception" << endl; }
};

class CCC : public BBB
{
public:
	void ShowYou() { cout << "CCC exception" << endl; }
};

void ExceptionGenerator(int expn)
{
	if (expn == 1)
		throw AAA();
	else if (expn == 2)
		throw BBB();
	else
		throw CCC();
}

int main()
{
	try
	{
		ExceptionGenerator(3);    //🎈🎈 여기서 throw를 하기 때문에 당연히 아래의 나머지 try 안의 코드들은 실행되지 않는다.
		ExceptionGenerator(2);
		ExceptionGenerator(1);
	}
	catch (AAA& expn)             //🎈🎈 AAA& expn = CCC();  올바른 문장이기 때문에 여기서 문제가 발생한다.
	{                             //      AAA는 CCC의 기초 클래스
		cout << "catch(AAA& expn)" << endl;
		expn.ShowYou();
	}
	catch (BBB& expn)
	{
		cout << "catch(BBB& expn)" << endl;
		expn.ShowYou();
	}
	catch (CCC& expn)
	{
		cout << "catch(CCC& expn)" << endl;
		expn.ShowYou();
	}

	return 0;
}


/*
실행결과 : catch(AAA& expn)
           AAA exception
*/
