💙 내가 작성한 코드 💙           
 
#include <iostream>                     ✅ 나는 상속의 구조를 파악하는 데에 실패했다.. 두 클래스 모두 Accout를 상속해줬으니까.. 
#include <cstring>
using namespace std;

enum { Make = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

//enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL = 2 };
//
//enum { NORMAL = 1, CREDIT = 2 };

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

	virtual void Deposit(int money)   // 입금
	{
		balance += money;
	}

	int Widthdraw(int money)  // 출금
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
 
class NormalAccount : public Account     // 보통예금계좌
{
private:
	int interRate;
public:
	NormalAccount(int id, int money, char* name, int interest)
		: Account(id, money, name), interRate(interest)
	{}

	void Deposit(int money)   // 입금
	{
		Account::Deposit(money + (money * interRate / 100)); // interestRate%
	}
};

class HighCreditAccount : public Account // 신용신뢰계좌
{
private:
	int speicalRate;
	int rank;
public:
	HighCreditAccount(int id, int money, char* name, int interest, int rank)
		: Account(id, money, name), speicalRate(interest), rank(rank)
	{}

	void Deposit(int money)   // 입금
	{
		switch (rank) 
		{
		case 1:                   // 7%
			Account::Deposit(money + (money * (speicalRate + 7) / 100));
			break;
		case 2:                   // 4%
			Account::Deposit(money + (money * (speicalRate + 4) / 100));
			break; 
		case 3:                   // 2%
			Account::Deposit(money + (money * (speicalRate + 2) / 100));
			break;
		}
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
	int choice;
	int id, money, interest, rank;
	char name[50];

	cout << "[계좌종류선택]\n";
	cout << "1.보통예금계좌 2.신용신뢰계좌\n선택: ";
	cin >> choice;

	if (choice == 1)
	{
		cout << "계좌ID: ";
		cin >> id;
		cout << "이 름: ";
		cin >> name;
		cout << "입금액: ";
		cin >> money;
		cout << "이자율: ";
		cin >> interest;

		accArr[accNum++] = new NormalAccount(id, money, name, interest);
	}
	else
	{
		cout << "계좌ID: ";
		cin >> id;
		cout << "이 름: ";
		cin >> name;
		cout << "입금액: ";
		cin >> money;
		cout << "이자율: ";
		cin >> interest;
		cout << "신용등급(1toA, 2toB, 3toC): ";
		cin >> rank;

		accArr[accNum++] = new HighCreditAccount(id, money, name, interest, rank);
	}
	
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
------------------------------------------------------------------------------------------------------------------------------
	
💙 성우형이 작성한 코드 💙
	
#include <iostream>
#include <cstring>
using namespace std;
const int NAME_LEN = 20;

enum { Make = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL_C = 2 };

enum { NORMAL = 1, CREDIT = 2 };

class Account    
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

	virtual void Deposit(int money)   // 입금
	{
		balance += money;
	}

	int Widthdraw(int money)  // 출금
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
 
class NormalAccount : public Account     // 보통예금계좌
{
private:
	int interRate;
public:
	NormalAccount(int id, int money, char* name, int interest)
		: Account(id, money, name), interRate(interest)
	{}

	virtual void Deposit(int money)   
	{
		Account::Deposit(money); // 원금추가
		Account::Deposit((money * (interRate / 100.0))); // 이자추가
	}
};

class HighCreditAccount : public NormalAccount // 신용신뢰계좌
{
private:
	int speicalRate;
public:
	HighCreditAccount(int id, int money, char* name, int interest, int rank)
		: NormalAccount(id, money, name, interest), speicalRate(rank)
	{}

	virtual void Deposit(int money)  
	{
		NormalAccount::Deposit(money);   // 원금과 이자추가
		Account::Deposit((money * (speicalRate / 100.0))); // 특별이자추가
	}
};

class AccountHandler    
{
private:
	Account* accArr[100];  
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
protected:
	void MakeNormalAccout();   // 보통예금계좌 생성
	void MakeCreditAccout();   // 신용신뢰계좌 생성
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
	int sel;
	cout << "[계좌종류선택]" << endl;
	cout << "1.보통예금계좌 ";
	cout << "2.신용신뢰계좌 " << endl;
	cout << "선택:  ";
	cin >> sel;

	if (sel == NORMAL)
		MakeNormalAccout();
	else
		MakeCreditAccout();
}

void AccountHandler::MakeNormalAccout()
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << "이자율: "; cin >> interRate;
	cout << endl;

	accArr[accNum++] = new NormalAccount(id, balance, name, interRate);
}

void AccountHandler::MakeCreditAccout()
{
	int id;
	char name[NAME_LEN];
	int balance;
	int interRate;
	int creditLevel;

	cout << "[보통예금계좌 개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이 름: "; cin >> name;
	cout << "입금액: "; cin >> balance;
	cout << "이자율: "; cin >> interRate;
	cout << "신용등급(1toA, 2toB, 3toC): "; cin >> creditLevel;
	cout << endl;

	switch (creditLevel)
	{
	case 1:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_A);
		break;
	case 2:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_B);
		break;
	case 3:
		accArr[accNum++] = new HighCreditAccount(id, balance, name, interRate, LEVEL_C);
		break;
	}
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
