
💙 내 코드 💙

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
private:
	int accID;      // 아이디
	int balance;    // 잔액
	char* cusName;  // 고객 이름

public:
	Account(int id, int money, char* name) : accID(id), balance(money)
	{
		int len = strlen(name) + 1;
		cusName = new char[len];
		strcpy(cusName, name);
	}

	bool DepositMoney(int id)
	{
		if (accID == id)
		{
			int money;

			cout << "입금액: "; cin >> money;
			balance += money;

			cout << "입금완료\n\n";
			return true;
		}

		return false;
	}

	bool Widthdraw(int id)
	{
		int money;

		if (accID == id)
		{
			cout << "출금액: "; cin >> money;

			if (balance < money)
			{
				cout << "잔액부족\n";
				return true;
			}
			else
			{
				balance -= money;

				cout << "출금완료\n\n";
				return true;
			}
		}
		
		return false;
	}

	void ShowAccInfo()
	{
		cout << "계좌ID: " << accID << endl;
		cout << "이 름: " << cusName << endl;
		cout << "입금액: " << balance << endl << endl;
	}

	~Account()
	{
		delete[] cusName;
		//delete this;
	}
};

Account* accArr[100];
int accNum = 0;

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

	accArr[accNum] = new Account(id, money, name);  // 동적할당   (생성한 계좌 객체는 해제(delete)를 왜 안해주지..??
	accNum++;
	cout << endl;
}

void DepositMoney()
{
	int id;

	cout << "[입  금]\n";
	cout << "계좌ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->DepositMoney(id))
			return;
	}

	cout << "유효하지 않는 ID 입니다.\n\n";    
}

void WidthdrawMoney()
{
	int id;

	cout << "[출  금]\n";
	cout << "계좌ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->Widthdraw(id))
			return;
	}

	cout << "유효하지 않는 ID 입니다.\n\n";
}

void ShowAllAccInfo()
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}

