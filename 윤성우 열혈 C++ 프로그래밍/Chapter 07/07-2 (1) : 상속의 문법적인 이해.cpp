#include <iostream>
using namespace std;

class AA
{
private:
	int a;
public:
	AA() // 🎈🎈생성자에서 멤버변수를 초기화하지 않으면 초기화하라고 컴파일러가 경고를 보냄
	{
		cout << "AA 생성자" << endl;
	}
	AA(int a) : a(a)
	{
		cout << "AA() 생성자" << endl;
	}
	~AA()
	{
		cout << "AA 소멸자" << endl;
	}
};

class BB : public AA
{
public:
	BB()
	{
		cout << "BB 생성자" << endl;
	}
	BB(int a) : AA(a)
	{
		cout << "BB() 생성자" << endl;
	}
	~BB()
	{
		cout << "BB 소멸자" << endl;
	}
};

int main()
{
	BB bb1(3);
	BB bb2;       

	return 0;
}


/*
  실행결과: AA() 생성자           // 객체 bb1이 생성되면서 상속받은 AA의 생성자 호출
            BB() 생성자           // 그리고 BB의 생성자 호출
            AA 생성자             // 객체 bb2가 생성되면서 상속받은 AA의 생성자 호출
            BB 생성자             // 그리고 BB의 생성자 호출
            BB 소멸자             // 스택형식으로 쌓였기 때문에 LIFO 순으로 bb2 소멸자 호출
            AA 소멸자             // bb2 안에 저장되어있는 클래스 AA의 멤버도 소멸
            BB 소멸자             // bb1 소멸자 호출
            AA 소멸자             // bb1 안에 저장되어있는 클래스 AA의 멤버 소멸
*/
---------------------------------------------------------------------------

// (컴파일러 준수모드 꺼진 상태)
 
#include <iostream>
#include <cstring>
using namespace std;

class Person
{
private:
	int age;        // 클래스의 외부에서는 prviate 멤버에 접근이 불가능하다. 따라서 UnivStudent의 멤버함수 내에서는 Person의 멤버변수에 직접 접근이 불가능하다. 
	char name[50];
public:
	Person(int myage, char* myname) : age(myage)
	{
		strcpy(name, myname);
	}
	void WhatYourName() const
	{
		cout << "My name is " << name << endl;
	}
	void HowOldAreYou() const
	{
		cout << "I'm " << age << " years old" << endl;
	}
};

class UnivStudent : public Person
{
private:
	char major[50];
public:
	UnivStudent(char* myname, int myage, char* mymajor) : Person(myage, myname) // 🎈🎈 부모 클래스의 생성자를 호출해서 부모 클래스의 멤버를 초기화 !!
	{
		strcpy(major, mymajor);
	}
	void WhoAreYou() const
	{
		WhatYourName();
		HowOldAreYou();
		cout << "my major is " << major << endl << endl;
	}
};

int main()
{
	UnivStudent ustd1("Lee", 22, "Computer eng.");
	ustd1.WhoAreYou();

	UnivStudent ustd2("Yoon", 21, "Electronic eng.");
	ustd2.WhoAreYou();
}
                                             // 🎈🎈 자식 클래스의 생성자는 부모 클래스의 멤버까지 초기화해야 할 의무가 있다.
                                                      
/*                                           // 🎈🎈 자식 클래스의 생성자는, 부모 클래스의 생성자를 호출해서 부모 클래스의 멤버를 초기화하는 것이 좋다.
  출력결과: My name is Lee
            I'm 22 years old
            my major is Computer eng.

            My name is Yoon
            I'm 21 years old
            my major is Electronic eng.
*/
---------------------------------------------------------------------------
  
     Person    <-->    UnivStudent
      
상위 클래스             하위 클래스
기초(base) 클래스       유도(derived) 클래스
슈퍼(super) 클래스      서브(sub) 클래스
부모 클래스             자식 클래스
     
  
  
  
  
    🎈🎈 이 책에서는 '기초 클래스'와 '유도 클래스'라는 C++에서 가장 일반적으로 사용되는 표현을 쓰겠다고 했다.
  
  
---------------------------------------------------------------------------
  
#include <iostream>
#include <cstring>
using namespace std;

class Secret
{                               // ✅ 내가 짜본 코드. 그런데 코드를 짜보다보면 자연스레 유도클래스의 생성자에서 기초클래스의 생성자를 통해 
private:                        //     기초 클래스의 private 멤버변수를 초기화하려는 방향으로 나아가게 된다.
	int num1;
	int num2;
public:
	Secret(int num1, int num2) : num1(num1), num2(num2)
	{

	}
	int Sum()
	{
		return num1 + num2;
	}
};

class Yahoo : public Secret
{
private:
	int sum;
public:
	Yahoo(int num1, int num2) : Secret(num1, num2)
	{
		sum = Sum();
		cout << "Secret 클래스의 멤버들의 합: " << sum << endl;
	}
};

int main()
{
	Yahoo yy(5, 3);  // 8 출력
}
---------------------------------------------------------------------------
  
 👉👉 코드 분석해보기 !!!!!
  
#include <iostream>
using namespace std;

class SoBase
{
private:
	int baseNum;
public:
	SoBase() : baseNum(20)
	{
		cout << "SoBase()" << endl;
	}
	SoBase(int n) : baseNum(n)
	{
		cout << "SoBase(int n)" << endl;
	}
	void ShowBaseDate()
	{
		cout << baseNum << endl;
	}
};

class SoDerived : public SoBase
{
private:
	int derivNum;
public:
	SoDerived() : derivNum(30)
	{
		cout << "SoDerived()" << endl;
	}
	SoDerived(int n) : derivNum(n)
	{
		cout << "SoDerived()" << endl;
	}
	SoDerived(int n1, int n2) : SoBase(n1), derivNum(n2)
	{
		cout << "SoDerived(int n1, int n2)" << endl;
	}
	void ShowDerivData()
	{
		ShowBaseDate();
		cout << derivNum << endl;
	}
};

int main()
{
	cout << "case1... " << endl;
	SoDerived dr1;
	dr1.ShowDerivData();
	cout << "-----------------------" << endl;
	cout << "case2... " << endl;
	SoDerived dr2(12);
	dr2.ShowDerivData();
	cout << "-----------------------" << endl;
	cout << "case3... " << endl;
	SoDerived dr3(23, 24);
	dr3.ShowDerivData();

	return 0;
}
  

                
        👉👉 핵심! // 🎈🎈 유도 클래스의 객체생성 과정에서 기초 클래스의 생성자는 100% 호출된다.. !!
                    //      유도 클래스의 생성자에서 기초 클래스의 생성자 호출을 명시하지 않으면, 기초 클래스의 void 생성자가 호출된다.. !!
  

/*                                          
  출력결과:     case1...
                SoBase()
                SoDerived()
                20
                30
                -----------------------
                case2...
                SoBase()
                SoDerived()
                20
                12
                -----------------------
                case3...
                SoBase(int n)
                SoDerived(int n1, int n2)
                23
                24
        
*/
          
          
          
          ✅ 기초 클래스의 생성자와 유도 클래스의 생성자가 모두 호출된다는 사실은,
              
             "클래스의 멤버는 해당 클래스의 생성자를 통해서 초기화해야 한다." 라는 기본 원칙을 지켜야 함을 알 수가 있다.. !!
          
          
          
          
