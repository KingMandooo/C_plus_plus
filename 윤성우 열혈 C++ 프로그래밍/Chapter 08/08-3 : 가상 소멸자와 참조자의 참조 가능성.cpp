
         이 코드에는 문제점이있다.  

#include <iostream>
using namespace std;

class First
{
private:
	char* strOne;
public:
	First(char* str)
	{
		strOne = new char[strlen(str) + 1];
	}
	~First()
	{
		cout << "~First()" << endl;
		delete[] strOne;                         // 🎈🎈 출력결과를 보면 First 클래스의 소멸자만 호출되었다.
	}                                          //      그렇게 되면 Second 객체에 저장된 strTwo 값을 해제시켜주지 못하여
};                                           //      메모리 누수가 발생하게 된다.

class Second : public First
{
private:
	char* strTwo;
public:
	Second(char* str1, char* str2) : First(str1)
	{
		strTwo = new char[strlen(str2) + 1];
	}
	~Second()
	{
		cout << "~Second() " << endl;
		delete[] strTwo;
	}
};

int main()
{
	First* ptr = new Second("simple", "complex");
	delete ptr;

	return 0;
}


/* 
  출력결과:   ~First()
*/

--------------------------------------------------------------------------
  
  ✅ 위에서와 같은 문제를 해결해주기 위하여 사용하는 것이 가상 소멸자이다 !!!
  
     🎈🎈 가상 소멸자가 호출되면, 상속의 계층구조상 맨 아래에 존재하는 유도 클래스의 소멸자가 대신 호출되면서,
          기초 클래스의 소멸자가 순차적으로 호출된다.
            
  
#include <iostream>
using namespace std;

class First
{
private:
	char* strOne;
public:
	First(char* str)
	{
		strOne = new char[strlen(str) + 1];
	}
	virtual ~First()
	{
		cout << "~First()" << endl;
		delete[] strOne;
	}
};

class Second : public First
{
private:
	char* strTwo;
public:
	Second(char* str1, char* str2) : First(str1)
	{
		strTwo = new char[strlen(str2) + 1];
	}
	~Second()
	{
		cout << "~Second() " << endl;
		delete[] strTwo;
	}
};

int main()
{
	First* ptr = new Second("simple", "complex");
	delete ptr;

	return 0;
}


/* 
  출력결과:  ~Second()       <-- 🎈🎈 위에서 말했다싶이 예상과는 다르게 Second 클래스의 소멸자가 먼저 호출됐다.
             ~First()                 virtual 소멸자의 특징이다. 
*/

--------------------------------------------------------------------------

🟢 참조자의 참조 가능성
      
    -->  포인터의 개념이 참조자에게도 동일하게 적용된다. 실행결과를 보면 쉽게 파악할 수 있다.
  
  
#include <iostream>
using namespace std;

class First
{
public:
	void FirstFunc()
	{
		cout << "FirstFunc()" << endl;
	}
	virtual void SimpleFunc()
	{
		cout << "First's SimpleFunc()" << endl;
	}
};

class Second : public First
{
public:
	void SecondFunc()
	{
		cout << "SecondFunc()" << endl;
	}
	virtual void SimpleFunc()
	{
		cout << "Second's SimpleFunc()" << endl;
	}
};

class Third : public Second
{
public:
	void ThirdFunc()
	{
		cout << "ThirdFunc()" << endl;
	}
	virtual void SimpleFunc()
	{
		cout << "Third's SimpleFunc()" << endl;
	}
};

int main()
{
	Third obj;
	
	Third& ptr3 = obj;
	ptr3.FirstFunc();
	ptr3.SecondFunc();
	ptr3.ThirdFunc();
	ptr3.SimpleFunc();

	Second& ptr2 = obj;
	ptr2.FirstFunc();
	ptr2.SecondFunc();
	ptr2.SimpleFunc();

	First& ptr1 = obj;
	ptr1.FirstFunc();
	ptr1.SimpleFunc();

	return 0;
}

/* 
  출력결과:   FirstFunc()
              SecondFunc()
              ThirdFunc()
              Third's SimpleFunc()
              FirstFunc()
              SecondFunc()
              Third's SimpleFunc()
              FirstFunc()
              Third's SimpleFunc()

*/


            🎈🎈  void GoodFunction(const First& ref) { ... }   와 같이 정의된 함수를 보면
            
                  "음, First 객체 또는 First를 직접 혹은 간접적으로 상속하는 클래스의 객체가 인자의 대상이 되는구나!"
                  
                  이러한 사실을 고려하여 함수를 정의할 수 있어야 한다.           
            
            
