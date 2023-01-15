    
      💙 C언어에서의 static
           
          - 전역변수에 선언된 static의 의미
            
              --> 선언된 파일 내에서만 참조를 허용하겟다는 의미
              
          - 함수 내에 선언된 static의 의미
          
              --> 한번만 초기화되고 지역변수와 달리 함수를 빠져나가도 소멸되지 않는다.
        
--------------------------------------------------------------------------------------

🟢 static 멤버변수(클래스 변수)

#include <iostream>
using namespace std;

void Counter()
{
	static int cnt;  // static 변수는 전역변수와 마찬가지로 초기화를 안하면 자동으로 0으로 초기화.
	cout << "Current cnt: " << ++cnt << endl;
}

int main()
{
	for (int i = 0; i < 10; i++)
		Counter();

	return 0;
}

----------------------------------------------------

#include <iostream>
using namespace std;

int simObjCnt = 0;         // 전역변수 선언
int cmxObjCnt = 0;

class SoSimple
{
public:
	SoSimple()
	{
		simObjCnt++;
		cout << simObjCnt << "번째 SoSimple 객체" << endl;
	}
};                           // 🎈🎈 전역변수 simObjCnt와 cmxObjCnt는 객체들이 공유하는 변수다.
                             //       이 둘은 모두 전역변수이기 때문에 어디서든 접근이 가능하므로 문제를 일으킬 수도 있다.
class SoComplex              //       따라서 이를 보완하기 위해 static 키워드를 사용한다.
{
public:
	SoComplex()
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
	}

	SoComplex(SoComplex& copy)
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
	}
};

int main()
{
	SoSimple sim1;
	SoSimple sim2;

	SoComplex com1;
	SoComplex com2 = com1;
	SoComplex();

	return 0;
}


/*
  실행결과: 1번째 SoSimple 객체
            2번째 SoSimple 객체
            1번째 SoComplex 객체
            2번째 SoComplex 객체
            3번째 SoComplex 객체
*/

----------------------------------------------------
  
class SoSimple
{
private:
	static int simObjCnt;
public:
	SoSimple()
	{
		simObjCnt++;
		cout << simObjCnt << "번째 SoSimple 객체" << endl;
	}
};
int SoSimple::simObjCnt = 0;   
 // 🎈🎈 static 멤버 변수는 모든 객체가 공유해야 하므로 프로그램 전체 영역에서 메모리 유지가 되야 한다. 
 //      따라서 반드시 전역 범위에서 정의 및 초기화를 해주어야 한다.

int main()
{
   SoSimple sim1;     // 🎈🎈 sim1, sim2, sim3 객체가 static 변수 simObjCnt를 공유하는 구조가 된다. 
   SoSimple sim2;     //      하지만 그렇다고 해서 객체 내에 simObjCnt가 존재하는 것은 아니다.
   SoSimple sim3;     //      이 변수는 객체 외부에 있다. 다만 객체에게 멤버변수처럼 접근할 수 있는 권한을 줬을 뿐이다.
}

----------------------------------------------------
  
// static 멤버변수는 객체 내에 존재하지 않는다는 사실을 명심하자.  
  
#include <iostream>
using namespace std;

class SoSimple
{
private:
	static int simObjCnt;
public:
	SoSimple()
	{
		simObjCnt++;
		cout << simObjCnt << "번째 SoSimple 객체" << endl;
	}
};
int SoSimple::simObjCnt = 0;  // static 멤버변수 초기화

class SoComplex
{
private:
	static int cmxObjCnt;
public:
	SoComplex()
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
	}

	SoComplex(SoComplex& copy)
	{
		cmxObjCnt++;
		cout << cmxObjCnt << "번째 SoComplex 객체" << endl;
	}
};
int SoComplex::cmxObjCnt = 0;   // static 멤버변수 초기화

int main()
{
	SoSimple sim1;
	SoSimple sim2;

	SoComplex com1;
	SoComplex com2 = com1;
	SoComplex();

	return 0;
}


/*
  실행결과: 1번째 SoSimple 객체
            2번째 SoSimple 객체
            1번째 SoComplex 객체
            2번째 SoComplex 객체
            3번째 SoComplex 객체
*/

----------------------------------------------------
  
#include <iostream>
using namespace std;

class SoSimple
{
public:                // 🎈🎈 이렇게 static 멤버변수를 public으로 선언하면 당연히 외부에서 접근이 가능하다.
	static int simObjCnt; 
public:
	SoSimple()
	{
		simObjCnt++;
	}
};
int SoSimple::simObjCnt = 0;

int main()
{
	SoSimple sim1;
	SoSimple sim2;

	cout << sim1.simObjCnt << endl;  // 이런식으로 접근하지말자 멤버변수와 헷갈린다.
	cout << sim2.simObjCnt << endl;
	cout << SoSimple::simObjCnt << endl;   // 🎈🎈 이렇게 클래스의 이름을 이용해서 접근해야 좋다.
  
  ✅ 순간 ::(범위 확인 연산자)가 쓰이는 범위가 어떻게 되는지 궁금해서 찾아봤다. (꼭 한번 봐바)
    
     --> https://learn.microsoft.com/ko-kr/cpp/cpp/scope-resolution-operator?view=msvc-170

	return 0;
}

--------------------------------------------------------------------------------------
  
🟢 static 멤버함수

- 선언된 클래스의 모든 객체가 공유한다.
  
- public으로 선언이 되면, 클래스의 이름을 이용해서 호출이 가능하다.
  
- 객체의 멤버로 존재하는 것이 아니다.  👈👈 이게 중요해
  
  
 // ❌ 잘못된 코드 
class SoSimple
{
private:        // public으로 선언해도 오류발생은 마찬가지.
	int num1;
	static int num2;
public:
	SoSimple(int n) : num1(n) {}

	static void Adder(int n)
	{
		num1 += n;             // 🎈🎈 여기서 오류발생
		num2 += n;            
	}                        // --> static 멤버함수는 사실 객체의 멤버로 존재하는 것이 아니다. (아래는 오류발생이유)
};                           
                                1. "객체의 멤버가 아닌데, 어떻게 멤버변수에 접근을 하겠는가?"
                                2. "객체생성 이전에도 호출이 가능하다. 그런데 어떻게 멤버변수에 접근이 가능하겠는가?"
                                3. "멤버변수에 접근을 한다고 치자. 그렇다면 어떤 객체의 멤버변수에 접근을 해야겠는가?"
                
                     이 모든게 그냥 static 멤버는 개체의 멤버로 존재하지 않는다는 것을 이해하면 납득이 된다.
  
                     🎈🎈 "static 멤버함수 내에서는 static 멤버변수와 static 멤버함수만 호출이 가능하다."
                                  
--------------------------------------------------------------------------------------
  
🟢 const static 멤버

  --> const static 멤버변수는, 클래스가 정의될 때 지정된 값이 유지되는 상수이기 때문에, 
      아래의 예제처럼 초기화가 가능하다.

#include <iostream>
using namespace std;

class CountryArea
{
public:
	const static int RUSSIA = 1707540;
	const static  int CANADA = 998467;
	const static int CHINA = 957290;
	const static int SOUTH_KOREA = 9922;
};

int main()
{
	cout << "러시아: " << CountryArea::RUSSIA << endl;
	cout << "캐나다: " << CountryArea::CANADA << endl;
	cout << "중국: " << CountryArea::CHINA << endl;
	cout << "한국: " << CountryArea::SOUTH_KOREA << endl;

	return 0;
}

--------------------------------------------------------------------------------------
   
🟢 키워드 mutable     (*mutable 뜻: 변하기 쉬운)
  
   --> 🎈🎈 const 함수 내에서의 값의 변경을 예외적으로 허용한다.
  
  
#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num1;
	mutable int num2;
public:
	SoSimple(int n1, int n2) : num1(n1), num2(n2) {}

	void ShowSimpleData() const
	{
		cout << num1 << ", " << num2 << endl;
	}

	void CopyToNum2() const  // 이 함수 내에서 num1을 변경하는 일이 발생하지 않는다. 
	{
		num2 = num1;    // 🎈🎈 이렇게 num2를 변경가능.
	}
};                  

int main()
{
	SoSimple sm(1, 2);
	sm.ShowSimpleData();
	sm.CopyToNum2();
	sm.ShowSimpleData();

	return 0;
}
