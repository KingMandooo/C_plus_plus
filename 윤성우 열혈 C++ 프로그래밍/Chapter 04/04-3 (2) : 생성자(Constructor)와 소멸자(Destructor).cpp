π’ μλ©Έμμ μ΄ν΄μ νμ©

  κ°μ²΄μλ©Έμ λ°λμ νΈμΆλλ κ²μ μλ©Έμμ΄λ€.
  
  - ν΄λμ€μ μ΄λ¦ μμ '~'κ° λΆμ ννμ μ΄λ¦μ κ°λλ€.
  - λ°ννμ΄ μ μΈλμ΄ μμ§ μμΌλ©°, μ€μ λ‘ λ°ννμ§ μλλ€.
  - λ§€κ°λ³μ voidνμΌλ‘ μ μΈλμ΄μΌ νκΈ° λλ¬Έμ μ€λ²λ‘λ©λ, λν΄νΈ κ° μ€μ λ λΆκ°λ₯νλ€.
  
class AAA
{
  // Empty
};

            μ΄ λκ°λ κ°λ€.

class AAA
{
public:
    AAA(){}
    ~AAA(){}
};


--------------------------------

#include <iostream>
#include <cstring>
using namespace std;


class Person
{
private:
	char* name;
	int age;
public:
	Person(const char* myname, int myage)  
	{
		int len = strlen(myname) + 1;
		name = new char[len];
		strcpy(name, myname);
		age = myage;
	}

	void ShowPersonInfo() const
	{
		cout << "μ΄λ¦: " << name << endl;
		cout << "λμ΄: " << age << endl;
	}

	~Person()                               // ππ μλ©Έμ !!
	{
		delete[]name;
		cout << "call destructor!" << endl;
	}
};

int main()
{
	Person man1("Sun tae uk", 24);
	Person man2("Kang dong one", 50);
	man1.ShowPersonInfo();
	man2.ShowPersonInfo();

	return 0;
}

/*
  μΆλ ₯κ²°κ³Ό:  μ΄λ¦: Sun tae uk
              λμ΄: 24
              μ΄λ¦: Kang dong one
              λμ΄: 50
              call destructor!                  
              call destructor!

*/


--------------------------------------------------------
	
π  λ¬Έμ  04-3(1)
	
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x, int y) : xpos(x), ypos(y) {}     // Point μμ±μ

	void ShowPointInfo() const
	{
		cout << "[" << xpos << ", " << ypos << "]" << endl;
	}
};

class Circle
{
private:
	Point point;
	int radius;
public:
	Circle(int x, int y, int r) : point(x, y), radius(r) {}   // Circle μμ±μ

	void ShowCircleInfo() const
	{
		cout << "radius: " << radius << endl;
		point.ShowPointInfo();
	}
};

class Ring
{
private:
	Circle c1;
	Circle c2;
public:
	Ring(int x1, int y1, int r1, int x2, int y2, int r2) : c1(x1, y1, r1), c2(x2, y2, r2) {}  // Ring μμ±μ

	void ShowRingInfo() const
	{
		cout << "Innder Circle Info..." << endl;
		c1.ShowCircleInfo();

		cout << "Outter Circle Info..." << endl;
		c2.ShowCircleInfo();
	}
};

int main()
{
	Ring* ring = new Ring(1, 1, 4, 2, 2, 9);
	ring->ShowRingInfo();

	delete ring;

	return 0;
}




π  λ¬Έμ  04-3(2)

#include <iostream>
#include <cstring>
using namespace std;

//enum COMP_POS { CLERK, SENIOR, ASSIST, MANAGER };    λ μ΄λ κ² νλλ

namespace COMP_POS
{
	enum { CLERK, SENIOR, ASSIST, MANAGER };

	void ShowPositionInfo(int pos)
	{
		switch (pos)
		{
		case CLERK: 
			cout << "μ¬μ" << endl << endl;
			break;
		case SENIOR:
			cout << "μ£Όμ" << endl << endl;
			break;
		case ASSIST:
			cout << "λλ¦¬" << endl << endl;
			break;
		case MANAGER:
			cout << "κ³Όμ₯" << endl << endl;
			break;
		}
	}
}

class NameCard
{
private:
	char* name;
	char* company_name;
	char* phone_number;
	int rank;

public:
	NameCard(const char *N, const char*CN, const char*PN, int r) : rank(r)
	{
		int len = strlen(N) + 1;
		name = new char[len];     
		strcpy(name, N);

		len = strlen(CN) + 1;
		company_name = new char[len];
		strcpy(company_name, CN);

		len = strlen(PN) + 1;
		phone_number = new char[len];
		strcpy(phone_number, PN);
	}

	void ShowNameCardInfo()
	{
		cout << "μ΄λ¦: " << name << endl;
		cout << "νμ¬: " << company_name << endl;
		cout << "μ νλ²νΈ: " << phone_number << endl;
		cout << "μ§κΈ: ";
		COMP_POS::ShowPositionInfo(rank);
	}

	~NameCard()               // μλ©Έμλ₯Ό μ¬μ©ν΄μ λμ ν λΉν λ©λͺ¨λ¦¬λ₯Ό μμμ ν΄μ ν΄μ£Όλ κ±° μμ§λ§κΈ°
	{
		delete[] name;
		delete[] company_name;
		delete[] phone_number;
	}
};

int main()
{
	NameCard manClerk("Lee", "ABCEng", "010-1111-2222", COMP_POS::CLERK);
	NameCard manSENIOR("Hong", "OrangeEng", "010-3333-4444", COMP_POS::SENIOR);
	NameCard manAssist("Kim", "SoGoodComp", "010-5555-6666", COMP_POS::ASSIST);
	manClerk.ShowNameCardInfo();
	manSENIOR.ShowNameCardInfo();
	manAssist.ShowNameCardInfo();

	return 0;
}
