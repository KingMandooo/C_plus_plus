✔ 기능 1. 계좌개설
✔ 기능 2. 입    금
✔ 기능 3. 출    금
✔ 기능 4. 전체고객 잔액조회

---------------------------------------------------

#include <iostream>

using namespace std;

void ShowMenu();       // 메뉴츌력
void MakeAccount();    // 계좌개설을 위한 함수
void DepositMoney();   // 입     금
void WidthdrawMoney(); // 출     금
void ShowAllAccInfo(); // 잔액조회

enum {Make = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT};

typedef struct
{
	int accID;
	int balance;
	char cusName[20];
}Account;

Account accArr[100];
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
	cout << "[계좌개설]\n";

	cout << "계좌ID: "; 
	cin >> accArr[accNum].accID;

	cout << "이 름: "; 
	cin >> accArr[accNum].cusName;

	cout << "입금액: "; 
	cin >> accArr[accNum].balance;

	cout << endl;

	accNum++;
}

void DepositMoney()
{
	int ID, money;

	cout << "[입  금]\n";
	cout << "계좌ID: "; cin >> ID;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i].accID == ID)
		{
			cout << "입금액: "; cin >> money;
			accArr[i].balance += money;

			cout << "입금완료\n\n";
			return;
		}
	}

	cout << "유효하지 않는 ID 입니다.\n\n";    // 나이스한 방법?!
}

void WidthdrawMoney()
{
	int ID, money;

	cout << "[출  금]\n";
	cout << "계좌ID: "; cin >> ID;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i].accID == ID)
		{
			cout << "출금액: "; cin >> money;

			if (accArr[i].balance < money)
			{
				cout << "잔액부족\n";
				return;
			}
			else 
			{
				accArr[i].balance -= money;

				cout << "출금완료\n\n";
				return;
			}
		}
	}

	cout << "유효하지 않는 ID 입니다.\n\n";    
}

void ShowAllAccInfo()
{
	for (int i = 0; i < accNum; i++)
	{
		cout << "계좌ID: " << accArr[i].accID << endl;
		cout << "이 름: " << accArr[i].cusName << endl;
		cout << "입금액: " << accArr[i].balance << endl << endl;
	}
}
