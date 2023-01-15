#include <iostream>
#include <cstring>
using namespace std;

void ShowMenu();       // 메뉴츌력
void MakeAccount();    // 계좌개설을 위한 함수
void DepositMoney();   // 입     금
void WidthdrawMoney(); // 출     금
void ShowAllAccInfo(); // 잔액조회

enum { Make = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

class Account
{
public:
	static int accNum;  // accNum을 static으로 선언

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

	int GetAccID() const { return accID; }  // const 추가

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

	void ShowAccInfo() const    // const 추가
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
int Account::accNum = 0;
Account* accArr[100];

int main()
{
	int choice;

	while (true)
	{
		ShowMenu();
		cout << "선택: ";
		cin >> choice;

		switch (choice)
		{
		case Make:MakeAccount(); break;
		case DEPOSIT:DepositMoney(); break;
		case WITHDRAW:WidthdrawMoney(); break;
		case INQUIRE:ShowAllAccInfo(); break;
		case EXIT: return 0;
		default: cout << "Illegal selection.." << endl; break;
		}
	}

	return 0;
}

void ShowMenu()
{
	cout << "-----Menu-----" << '\n';
	cout << "1. 계좌개설\n";
	cout << "2. 입 금\n";
	cout << "3. 출 금\n";
	cout << "4. 계좌정보 전체 출력\n";
	cout << "5. 프로그램 종료\n\n";
}

void MakeAccount()
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

	accArr[Account::accNum] = new Account(id, money, name);
	Account::accNum++;
	cout << endl;
}

void DepositMoney()
{
	int money, id;

	cout << "[입  금]\n";
	cout << "계좌ID: "; cin >> id;

	for (int i = 0; i < Account::accNum; i++)
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

void WidthdrawMoney()
{
	int id, money;

	cout << "[출  금]\n";
	cout << "계좌ID: "; cin >> id;

	for (int i = 0; i < Account::accNum; i++)
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

void ShowAllAccInfo()
{
	for (int i = 0; i < Account::accNum; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}
