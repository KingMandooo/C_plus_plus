
  ✅ 객체지향에서는 '전역'이라는 개념이 존재하지 않는다.
      비록 C++에서는 전역함수와 전역변수의 선언을 하용하고 있지만, 이는 객체지향 프로그래밍을
      위한 것은 아니니 가급적 사용하지 않는 것이 좋다.
    
-------------------------------------------------------------------------------

#include <iostream>
#include <cstring>
using namespace std;

enum { Make = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

class Account    // 🎈🎈 Entity 클래스 : 데이터적 성격이 강함
{ 
private:
	int accID;      // 아이디
	int balance;    // 잔액
	char* cusName;  // 고객 이름

public:
	Account(int id, int money, char* name) : accID(id), balance(money)
	{
		cusName = new char[strlen(name) + 1];
		strcpy(cusName, name);
	}

	Account(Account& copy) : accID(copy.accID), balance(copy.balance)
	{
		cusName = new char[strlen(copy.cusName) + 1];
		strcpy(cusName, copy.cusName);
	}

	int GetAccID() const { return accID; }  

	void Deposit(int money)
	{
		balance += money;
	}

	int Widthdraw(int money)
	{
		if (balance < money)
			return 0;

		balance -= money;
		return money;
	}

	void ShowAccInfo() const   
	{
		cout << "계좌ID: " << accID << endl;
		cout << "이 름: " << cusName << endl;
		cout << "입금액: " << balance << endl << endl;
	}

	~Account()
	{
		delete[] cusName;
	}
};

class AccountHandler    // 🎈🎈 컨트롤 클래스 : 프로그램 전체의 기능 담당
{
private:
	Account* accArr[100];   // 고객 데이터 정보
	int accNum;  
public:
	AccountHandler() : accNum(0) {}

	void ShowMenu() const;       // 메뉴츌력
	void MakeAccount();          // 계좌개설을 위한 함수
	void DepositMoney();		     // 입     금
	void WidthdrawMoney();		   // 출     금
	void ShowAllAccInfo() const; // 잔액조회

	~AccountHandler() 
	{
		for (int i = 0; i < accNum; i++)
			delete accArr[i];
	}
};

int main()
{
	AccountHandler manager;
	int choice;

	while (true)
	{
		manager.ShowMenu();
		cout << "선택: ";
		cin >> choice;

		switch (choice)
		{
		case Make:
			manager.MakeAccount(); 
			break;
		case DEPOSIT:
			manager.DepositMoney(); 
			break;
		case WITHDRAW:
			manager.WidthdrawMoney(); 
			break;
		case INQUIRE:
			manager.ShowAllAccInfo();
			break;
		case EXIT: 
			return 0;
		default:
			cout << "Illegal selection.." << endl; 
			break;
		}
	}

	return 0;
}

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
	int id, money;
	char name[50];

	cout << "[계좌개설]\n";
	cout << "계좌ID: ";
	cin >> id;
	cout << "이 름: ";
	cin >> name;
	cout << "입금액: ";
	cin >> money;

	accArr[accNum] = new Account(id, money, name);
	accNum++;
	cout << endl;
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
