      
      (05-1 마지막에 내가 말한 내용)  

      디폴트 복사 생성자는 멤버 대 멤버의 복사를 진행한다. 그리고 이러한 방식의 복사를 가리켜 '얕은 복사(shallow copy)'라 하는데,
      이는 멤버변수가 힙의 메모리 공간을 참조하는 경우에 문제가 된다.
        
-------------------------------------------------------------------------------------------

💙 문제가 있는 코드 (아래 분석) 💙  
        
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

  /*
  void ChangeString()   // 🎈🎈 이를 호출하면 ma1과 man2가 같은 곳을 참조하고 있다는 사실을 알 수 있다.
	{
		*name = 'c';
	}
  */

	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}

	~Person()
	{
		delete[] name;
		cout << "called destructor!" << endl;
	}
};

int main()
{
	Person man1("Sun tae uk", 24);             
	Person man2 = man1;                       

	//man2.ChangeString();    

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();

	return 0;
}


/*
 출력결과:       이름: Sun tae uk
                 나이: 24
                 이름: Sun tae uk
                 나이: 24
                 called destructor!               <-- 🎈🎈 소멸자가 한번만 호출
*/




                            man1의 멤버변수 name에는 "Sun tae uk"의 첫번째 문자의 주소값이 들어간다.
                            그리고 age에는 24가 들어간다. 
                              
                            그런데 이를 Person man2 = man1; 와 같이 man2에 man1의 멤버 값을 복사해준다면
                            man2의 멤버변수 age에는 24가 들어가도 문제가 될 것이 없다.
                              
                            그러나
                            
                            man2의 멤버변수 name에는 주소값이 들어가게 되면 문제가 발생하게 된다.
                            왜냐하면 "Sun tae uk"의 똑같은 주소값이 man2.name과 man1.name에 들어가 있는 것이다.
                              
                            정리하자면,
                            디폴트 복사 생성자는 멤버 대 멤버의 단순 복사를 진행하기 때문에 복사의 결과로 하나의
                            문자열을 두 개의 객체가 동시에 참조하는 꼴을 만들어버린다.
                              
                            이는 delete []name에서 문제가 발생한다.
                              
                            만약 man2가 먼저 소멸되는 경우를 생각해보자. man2는 delete[] name을 하면서 소멸이 될 것이다.
                            이제 man1이 소멸되는 경우 마찬가지로 delete[] name을 해야할 것이다.
                              
                            그러나 man1과 man2가 같은 공간을 참조하고 있기에 man1은 이미 해제된 공간을 해제해야 하는 것이다.
                            이것이 문제의 원인이 된다.
                              
-------------------------------------------------------------------------------------------
                              
     ✅ 이러한 문제를 해결하기 위해 '깊은 복사'를 위한 복사 생성자를 따로 정의해주어야 한다.

#include <iostream>
#include <cstring>
using namespace std;

class Person
{
private:
	char* name;
	int age;

public:
	Person(const char* myname, int myage) : age(myage)
	{
		name = new char[strlen(myname) + 1];
		strcpy(name, myname);
	}

	Person(Person& copy) : age(copy.age)          // '깊은 복사(deep copy)'를 위한 복사 생성자
	{
		name = new char[strlen(copy.name) + 1];    // 🎈🎈 man2.name에 새로 메모리를 할당해준다.
		strcpy(name, copy.name);                   // 🎈🎈 man1.name의 값만 복사해준다.
	}

	void ChangeString()
	{
		*name = 'K';
	}

	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}

	~Person()
	{
		delete[] name;
		cout << "called destructor!" << endl;
	}
};

int main()
{
	Person man1("Sun tae uk", 24);
	
	Person man2 = man1;
  // Person man2(man1);

	man2.ChangeString();

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();

	return 0;
}
                            
                              
/*
 출력결과:  이름: Sun tae uk
            나이: 24
            이름: Kun tae uk
            나이: 24
            called destructor!
            called destructor!
*/               
                              
                              
-------------------------------------------------------------------------------------------
  
🟠 문제 05-1
  
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
	NameCard(const char* N, const char* CN, const char* PN, int r) : rank(r)
	{
		name = new char[strlen(N) + 1];
		strcpy(name, N);

		company_name = new char[strlen(CN) + 1];
		strcpy(company_name, CN);

		phone_number = new char[strlen(PN) + 1];
		strcpy(phone_number, PN);
	}

	NameCard(NameCard& copy) : rank(copy.rank)       // 복사 생성자 만들어주기 !!
	{
		name = new char[strlen(copy.name) + 1];
		strcpy(name, copy.name);

		company_name = new char[strlen(copy.company_name) + 1];
		strcpy(company_name, copy.company_name);

		phone_number = new char[strlen(copy.phone_number) + 1];
		strcpy(phone_number, copy.phone_number);
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
	NameCard copy1 = manClerk;
	NameCard manSENIOR("Hong", "OrangeEng", "010-3333-4444", COMP_POS::SENIOR);
	NameCard copy2 = manSENIOR;

	manClerk.ShowNameCardInfo();
	manSENIOR.ShowNameCardInfo();

	return 0;
}                            
                              
                              
                              
                              
                              
