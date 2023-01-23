

 "다중상속은 득보다 실이 많은 문법이다. 그러니 절대로 사용하지 말아야 하며, 
  가능하다면 C++의 기본문법에서 제외시켜야 한다!"
   
  "일반적인 경우에서 다중상속은 다양한 문제를 동반한다. 따라서 가급적 사용하지 않아야 함에는
   동의를 한다. 그러나 예외적으로 매우 제한적인 사용까지 부정할 필요는 없다고 본다."
   
---------------------------------------------------------------
   
#include <iostream>
using namespace std;

class BaseOne
{
public:
	void SimpleFuncOne() { cout << "BaseOne" << endl; }
};

class BaseTwo
{
public:
	void SimpleFuncTwo() { cout << "BaseTwo" << endl; }
};

class MultiDerived : public BaseOne, public BaseTwo   // 🎈🎈 다중상속
{
public:
	void ComplexFunc()
	{
		SimpleFuncOne();
		SimpleFuncTwo();
	}
};

int main()
{
	MultiDerived mdr;
	mdr.ComplexFunc();

	return 0;
}
 

/*
  출력결과: BaseOne
            BaseTwo

*/
---------------------------------------------------------------
  
🟢 다중상속의 모호성(Ambiguous)

  
#include <iostream>
using namespace std;

class BaseOne
{
public:
	void SimpleFunc() { cout << "BaseOne" << endl; }
};

class BaseTwo
{
public:
	void SimpleFunc() { cout << "BaseTwo" << endl; }
};

class MultiDerived : public BaseOne, public BaseTwo
{
public:
	void ComplexFunc()
	{
		BaseOne::SimpleFunc();        //🎈🎈 상속으로 인해 이름이 겹치는 두 함수의 모호한 관계를 명시해줬다.
		BaseTwo::SimpleFunc();
	}
};

int main()
{
	MultiDerived mdr;
	mdr.ComplexFunc();

	return 0;
}
  

/*
  출력결과: BaseOne
            BaseTwo

*/
---------------------------------------------------------------
  
🟢 가상 상속(Virtual Inheritance)
  
  
#include <iostream>
using namespace std;

class Base
{
public:
	Base() { cout << "Base Constructor" << endl; }
	void SimpleFunc() { cout << "BaseOne" << endl; }
};

class MiddleDerivedOne : virtual public Base       //🎈🎈 가상상속
{
public:
	MiddleDerivedOne() : Base()
	{
		cout << "MiddleDerivedOne Constructor" << endl;
	}
	void MiddleFuncOne()
	{
		SimpleFunc();
		cout << "MiddleDerivedOne" << endl;
	}
};

class MiddleDerivedTwo : virtual public Base       //🎈🎈 가상상속
{
public:
	MiddleDerivedTwo() : Base()
	{
		cout << "MiddleDerivedTwo Constructor" << endl;
	}
	void MiddleFuncTwo()
	{
		SimpleFunc();
		cout << "MiddleDerivedTwo" << endl;
	}
};

class LastDerived : public MiddleDerivedOne, public MiddleDerivedTwo
{
public:
	LastDerived() : MiddleDerivedOne(), MiddleDerivedTwo()
	{
		cout << "LastDerived Constructor" << endl;         // 🎈🎈 코드를 보면 LastDerived 클래스가 상속하는 MiddleDerivedOne 클래스와
	}                                                    //      MiddleDerivedTwo 클래스 Base 클래스를 상속받고 있다.
	void ComplexFunc()                                   //      즉, LastDerived 클래스는 Base 클래스를 두번이나 상속받는다는 뜻이다.
	{                                                    //      이는 가상 상속을 해주지 않을 경우 LastDerived 클래스의 객체에서 
		MiddleFuncOne();                                   //      SimpleFunc() 함수를 호출할 때 이 함수가 누구로부터 상속받은 Base의 멤버함수인지
		MiddleFuncTwo();                                   //      명시를 해주어야 한다는 뜻이다.
		SimpleFunc();                                      //      MiddleDerivedOne::SimpleFunc() 이런식으로 말이다.
	}
};                                                     //      이를 해결해주기 위한 문법이 '가상 상속'이다 !!
                                                       //      그렇다면 LastDerived 객체 내에 MiddleDerivedOne 클래스와 MiddleDerivedTwo 클래스가
int main()                                             //      동시에 상속하는 Base 클래스의 멤버가 하나씩만 존재하게 된다.
{
	cout << "객체생성 전..." << endl;
	LastDerived ldr;
	cout << "객체생성 후..." << endl;
	ldr.ComplexFunc();

	return 0;
}

  
