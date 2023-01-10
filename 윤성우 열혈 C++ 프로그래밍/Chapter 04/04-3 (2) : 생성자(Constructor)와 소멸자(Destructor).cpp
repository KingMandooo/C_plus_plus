🟢 소멸자의 이해와 활용

  객체소멸시 반드시 호출되는 것은 소멸자이다.
  
  - 클래스의 이름 앞에 '~'가 붙은 형태의 이름을 갖는다.
  - 반환형이 선언되어 있지 않으며, 실제로 반환하지 않는다.
  - 매개변수 void형으로 선언되어야 하기 때문에 오버로딩도, 디폴트 값 설정도 불가능하다.
  
class AAA
{
  // Empty
};

            이 두개는 같다.

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
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}

	~Person()                               // 🎈🎈 소멸자 !!
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
  출력결과:  이름: Sun tae uk
              나이: 24
              이름: Kang dong one
              나이: 50
              call destructor!                  
              call destructor!

*/


--------------------------------------------------------
	
🟠 문제 04-3(1)
	
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x, int y) : xpos(x), ypos(y) {}     // Point 생성자

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
	Circle(int x, int y, int r) : point(x, y), radius(r) {}   // Circle 생성자

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
	Ring(int x1, int y1, int r1, int x2, int y2, int r2) : c1(x1, y1, r1), c2(x2, y2, r2) {}  // Ring 생성자

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




🟠 문제 04-3(2)

#include <iostream>
#include <cstring>
using namespace std;

//enum COMP_POS { CLERK, SENIOR, ASSIST, MANAGER };    난 이렇게 했는디

namespace COMP_POS
{
	enum { CLERK, SENIOR, ASSIST, MANAGER };

	void ShowPositionInfo(int pos)
	{
		switch (pos)
		{
		case CLERK: 
			cout << "사원" << endl << endl;
			break;
		case SENIOR:
			cout << "주임" << endl << endl;
			break;
		case ASSIST:
			cout << "대리" << endl << endl;
			break;
		case MANAGER:
			cout << "과장" << endl << endl;
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
		cout << "이름: " << name << endl;
		cout << "회사: " << company_name << endl;
		cout << "전화번호: " << phone_number << endl;
		cout << "직급: ";
		COMP_POS::ShowPositionInfo(rank);
	}

	~NameCard()               // 소멸자를 사용해서 동적할당한 메모리를 알아서 해제해주는 거 잊지말기
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
