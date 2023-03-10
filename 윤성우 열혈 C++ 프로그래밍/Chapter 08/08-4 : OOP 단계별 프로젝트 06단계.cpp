π λ΄κ° μμ±ν μ½λ π           
 
#include <iostream>                     β λλ μμμ κ΅¬μ‘°λ₯Ό νμνλ λ°μ μ€ν¨νλ€.. λ ν΄λμ€ λͺ¨λ Accoutλ₯Ό μμν΄μ€¬μΌλκΉ.. 
#include <cstring>
using namespace std;

enum { Make = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

//enum { LEVEL_A = 7, LEVEL_B = 4, LEVEL = 2 };
//
//enum { NORMAL = 1, CREDIT = 2 };

class Account    // ππ Entity ν΄λμ€ : λ°μ΄ν°μ  μ±κ²©μ΄ κ°ν¨
{
private:
	int accID;      // μμ΄λ
	int balance;    // μμ‘
	char* cusName;  // κ³ κ° μ΄λ¦

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

	virtual void Deposit(int money)   // μκΈ
	{
		balance += money;
	}

	int Widthdraw(int money)  // μΆκΈ
	{
		if (balance < money)
			return 0;

		balance -= money;
		return money;
	}

	void ShowAccInfo() const
	{
		cout << "κ³μ’ID: " << accID << endl;
		cout << "μ΄ λ¦: " << cusName << endl;
		cout << "μκΈμ‘: " << balance << endl << endl;
	}

	~Account()
	{
		delete[] cusName;
	}
};
 
class NormalAccount : public Account     // λ³΄ν΅μκΈκ³μ’
{
private:
	int interRate;
public:
	NormalAccount(int id, int money, char* name, int interest)
		: Account(id, money, name), interRate(interest)
	{}

	void Deposit(int money)   // μκΈ
	{
		Account::Deposit(money + (money * interRate / 100)); // interestRate%
	}
};

class HighCreditAccount : public Account // μ μ©μ λ’°κ³μ’
{
private:
	int speicalRate;
	int rank;
public:
	HighCreditAccount(int id, int money, char* name, int interest, int rank)
		: Account(id, money, name), speicalRate(interest), rank(rank)
	{}

	void Deposit(int money)   // μκΈ
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

class AccountHandler    // ππ μ»¨νΈλ‘€ ν΄λμ€ : νλ‘κ·Έλ¨ μ μ²΄μ κΈ°λ₯ λ΄λΉ
{
private:
	Account* accArr[100];   // κ³ κ° λ°μ΄ν° μ λ³΄
	int accNum;
public:
	AccountHandler() : accNum(0) {}

	void ShowMenu() const;       // λ©λ΄μΈλ ₯
	void MakeAccount();          // κ³μ’κ°μ€μ μν ν¨μ
	void DepositMoney();		     // μ     κΈ
	void WidthdrawMoney();		   // μΆ     κΈ
	void ShowAllAccInfo() const; // μμ‘μ‘°ν

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
		cout << "μ ν: ";
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
	cout << "1. κ³μ’κ°μ€\n";
	cout << "2. μ κΈ\n";
	cout << "3. μΆ κΈ\n";
	cout << "4. κ³μ’μ λ³΄ μ μ²΄ μΆλ ₯\n";
	cout << "5. νλ‘κ·Έλ¨ μ’λ£\n\n";
}

void AccountHandler::MakeAccount()
{
	int choice;
	int id, money, interest, rank;
	char name[50];

	cout << "[κ³μ’μ’λ₯μ ν]\n";
	cout << "1.λ³΄ν΅μκΈκ³μ’ 2.μ μ©μ λ’°κ³μ’\nμ ν: ";
	cin >> choice;

	if (choice == 1)
	{
		cout << "κ³μ’ID: ";
		cin >> id;
		cout << "μ΄ λ¦: ";
		cin >> name;
		cout << "μκΈμ‘: ";
		cin >> money;
		cout << "μ΄μμ¨: ";
		cin >> interest;

		accArr[accNum++] = new NormalAccount(id, money, name, interest);
	}
	else
	{
		cout << "κ³μ’ID: ";
		cin >> id;
		cout << "μ΄ λ¦: ";
		cin >> name;
		cout << "μκΈμ‘: ";
		cin >> money;
		cout << "μ΄μμ¨: ";
		cin >> interest;
		cout << "μ μ©λ±κΈ(1toA, 2toB, 3toC): ";
		cin >> rank;

		accArr[accNum++] = new HighCreditAccount(id, money, name, interest, rank);
	}
	
	cout << endl;
}

void AccountHandler::DepositMoney()
{
	int money, id;

	cout << "[μ  κΈ]\n";
	cout << "κ³μ’ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "μκΈμ‘: "; cin >> money;
			accArr[i]->Deposit(money);
			cout << "μκΈμλ£" << endl << endl;
			return;
		}
	}

	cout << "μ ν¨νμ§ μλ ID μλλ€.\n\n";
}

void AccountHandler::WidthdrawMoney()
{
	int id, money;

	cout << "[μΆ  κΈ]\n";
	cout << "κ³μ’ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "μΆκΈμ‘: "; cin >> money;
			if (accArr[i]->Widthdraw(money) == 0)
				cout << "μμ‘λΆμ‘±\n";
			else
				cout << "μΆκΈμλ£\n\n";

			return;
		}
	}

	cout << "μ ν¨νμ§ μλ ID μλλ€.\n\n";
}

void AccountHandler::ShowAllAccInfo() const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}
------------------------------------------------------------------------------------------------------------------------------
	
π μ±μ°νμ΄ μμ±ν μ½λ π
	
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
	int accID;      // μμ΄λ
	int balance;    // μμ‘
	char* cusName;  // κ³ κ° μ΄λ¦

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

	virtual void Deposit(int money)   // μκΈ
	{
		balance += money;
	}

	int Widthdraw(int money)  // μΆκΈ
	{
		if (balance < money)
			return 0;

		balance -= money;
		return money;
	}

	void ShowAccInfo() const
	{
		cout << "κ³μ’ID: " << accID << endl;
		cout << "μ΄ λ¦: " << cusName << endl;
		cout << "μκΈμ‘: " << balance << endl << endl;
	}

	~Account()
	{
		delete[] cusName;
	}
};
 
class NormalAccount : public Account     // λ³΄ν΅μκΈκ³μ’
{
private:
	int interRate;
public:
	NormalAccount(int id, int money, char* name, int interest)
		: Account(id, money, name), interRate(interest)
	{}

	virtual void Deposit(int money)   
	{
		Account::Deposit(money); // μκΈμΆκ°
		Account::Deposit((money * (interRate / 100.0))); // μ΄μμΆκ°
	}
};

class HighCreditAccount : public NormalAccount // μ μ©μ λ’°κ³μ’
{
private:
	int speicalRate;
public:
	HighCreditAccount(int id, int money, char* name, int interest, int rank)
		: NormalAccount(id, money, name, interest), speicalRate(rank)
	{}

	virtual void Deposit(int money)  
	{
		NormalAccount::Deposit(money);   // μκΈκ³Ό μ΄μμΆκ°
		Account::Deposit((money * (speicalRate / 100.0))); // νΉλ³μ΄μμΆκ°
	}
};

class AccountHandler    
{
private:
	Account* accArr[100];  
	int accNum;
public:
	AccountHandler() : accNum(0) {}

	void ShowMenu() const;       // λ©λ΄μΈλ ₯
	void MakeAccount();          // κ³μ’κ°μ€μ μν ν¨μ
	void DepositMoney();		     // μ     κΈ
	void WidthdrawMoney();		   // μΆ     κΈ
	void ShowAllAccInfo() const; // μμ‘μ‘°ν

	~AccountHandler()
	{
		for (int i = 0; i < accNum; i++)
			delete accArr[i];
	}
protected:
	void MakeNormalAccout();   // λ³΄ν΅μκΈκ³μ’ μμ±
	void MakeCreditAccout();   // μ μ©μ λ’°κ³μ’ μμ±
};

int main()
{
	AccountHandler manager;
	int choice;

	while (true)
	{
		manager.ShowMenu();
		cout << "μ ν: ";
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
	cout << "1. κ³μ’κ°μ€\n";
	cout << "2. μ κΈ\n";
	cout << "3. μΆ κΈ\n";
	cout << "4. κ³μ’μ λ³΄ μ μ²΄ μΆλ ₯\n";
	cout << "5. νλ‘κ·Έλ¨ μ’λ£\n\n";
}

void AccountHandler::MakeAccount()
{
	int sel;
	cout << "[κ³μ’μ’λ₯μ ν]" << endl;
	cout << "1.λ³΄ν΅μκΈκ³μ’ ";
	cout << "2.μ μ©μ λ’°κ³μ’ " << endl;
	cout << "μ ν:  ";
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

	cout << "[λ³΄ν΅μκΈκ³μ’ κ°μ€]" << endl;
	cout << "κ³μ’ID: "; cin >> id;
	cout << "μ΄ λ¦: "; cin >> name;
	cout << "μκΈμ‘: "; cin >> balance;
	cout << "μ΄μμ¨: "; cin >> interRate;
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

	cout << "[λ³΄ν΅μκΈκ³μ’ κ°μ€]" << endl;
	cout << "κ³μ’ID: "; cin >> id;
	cout << "μ΄ λ¦: "; cin >> name;
	cout << "μκΈμ‘: "; cin >> balance;
	cout << "μ΄μμ¨: "; cin >> interRate;
	cout << "μ μ©λ±κΈ(1toA, 2toB, 3toC): "; cin >> creditLevel;
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

	cout << "[μ  κΈ]\n";
	cout << "κ³μ’ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "μκΈμ‘: "; cin >> money;
			accArr[i]->Deposit(money);
			cout << "μκΈμλ£" << endl << endl;
			return;
		}
	}

	cout << "μ ν¨νμ§ μλ ID μλλ€.\n\n";
}

void AccountHandler::WidthdrawMoney()
{
	int id, money;

	cout << "[μΆ  κΈ]\n";
	cout << "κ³μ’ID: "; cin >> id;

	for (int i = 0; i < accNum; i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			cout << "μΆκΈμ‘: "; cin >> money;
			if (accArr[i]->Widthdraw(money) == 0)
				cout << "μμ‘λΆμ‘±\n";
			else
				cout << "μΆκΈμλ£\n\n";

			return;
		}
	}

	cout << "μ ν¨νμ§ μλ ID μλλ€.\n\n";
}

void AccountHandler::ShowAllAccInfo() const
{
	for (int i = 0; i < accNum; i++)
	{
		accArr[i]->ShowAccInfo();
	}
}
