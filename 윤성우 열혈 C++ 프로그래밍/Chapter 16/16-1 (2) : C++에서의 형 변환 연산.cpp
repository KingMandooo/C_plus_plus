
🟢 const_cast : const의 성향을 삭제하라!
    
   --> C++에서는 포인터와 참조자의 const 성향을 제거하는 형 변환을 목적으로, 다음과 같은 형 변환 연산자를 제공한다.
  
       const_cast<T>(expr) 과 같은 형태를 띄고 있다.
  
  

#include <iostream>
using namespace std;

void ShowString(char* str)
{
	cout << str << endl;
}

void ShowAddResult(int& n1, int& n2)
{
	cout << n1 + n2 << endl;
}

int main()
{
	const char* name = "Lee Sung Ju";
	ShowString(const_cast<char*>(name));  // 🎈🎈 const 성향을 제거해준다.
  
	// ShowString(name);                 <-- ❌ 당연히 이렇게하면 name은 const 형이기 때문에 함수의 매개변수와 호환이 안된다.

	const int& num1 = 100;
	const int& num2 = 200;
	ShowAddResult(const_cast<int&>(num1), const_cast<int&>(num2)); // 🎈🎈 const 성향을 제거해준다.
  
	// ShowAddResult(num1, num2));        <-- ❌ 마찬가지
	return 0;
}

    "const_cast 연산자가 존재함으로 인해서, 키워드 const 선언에 '값의 변경을 허용하지 않는다'라는 의미를 부여하기 어려워진 것 같은데요!"
      
     어쨋든 이러한 이유로 const_cast 연산자의 긍정적인 측면이 잘 드러나는 경우에만 제한적으로 사용해야 한다.
      
--------------------------------------------------------------------------------------------
      
🟢 reinterpret_cast : 상관없는 자료형으로의 형 변환 

   * reinterpret 뜻 : 재해석하다

   --> reinterpret_cast 연산자는 전혀 상관이 없는 자료형으로의 형 변환에 사용이 된다.
  
       reinterpret_cast<T>(expr) 과 같은 형태를 띄고 있다.

  
     
class SimpleCar { ... };
class BestFriend { ... };    // 이 두 클래스는 상속으로 관계를 맞은것도 아니니, 서로 전혀 없는 클래스이다.
                             // 그런데 이 클래스를 대상으로 다음과 같은 코드를 작성할 때 사용되는 것이 reinterpret_cast 연산자이다.
int main()
{
  SimpleCar* car = new Car;
  BestFriend* fren = reinterpret_cast<BestFriend*>(car);
}
  
  
    이렇듯 reinterpret_cast 연산자는 포인터를 대상으로 하는, 그리고 포인터와 관련이 있는 모든 유형의 형 변환을 허용한다.
      
    그렇다면 위의 코드를 통해서 만들어진 포인터 변수 fren은 어떻게 동작할까? 이는 아무도 모른다.
    왜냐하면 그 결과는 컴파일 환경에 따라 달라지기 때문이다. 
    이렇듯 위의 경우에는 형 변환이 가능하긴 하지만 의미를 부여할 순 없다.
      
    그러나 reinterpret_cast 연산자 또한 의미 있게 사용할 수 있다.
  
  
int main()
{
	int num = 0x010203;
	char* ptr = reinterpret_cast<char*>(&num);

	for (int i = 0; i < sizeof(num); i++)
		cout << static_cast<int>(*(ptr + i)) << endl;
	return 0;
}
  
/*
출력결과:   3
            2
            1
            0
*/ 
  
--------------------------------------------------------------------------------------------
      
🟢 dynamic_cast 두 번째 이야기 : Polymorphic 클래스 기반의 형 변환
  
  --> 지금까지 상속과 관련된 형 변환에 대한 정리는 다음과 같다.
  
     * 상속관계에 놓여있는 두 클래스 사이에서, 유도 클래스의 포인터 및 참조형 데이터를 기초 클래스의 포인터
       및 참조형 데이터로 형 변환할 경우에는 dynamic_cast 연산자를 사용한다.
  
     * 반대로, 상속관계에 놓여있는 두 클래스 사이에서, 기초 클래스의 포인터 및 참조형 데이터를 유도 클래스의 포인터 및
       참조형 데이터로 형 변환할 경우에는 static_cast 연산자를 사용한다.
  
     
    🎈🎈 하지만!!! "기초 클래스가 'Polymorphic(다형성) 클래스'이다!" 라는 조건이 만족된다면,
         dynamic_cast 연산자도 기초 클래스의 포인터 및 참조형 데이터를 유도 클래스의 포인터 및 참조형으로의 형 변환을 허용한다.
  
  
#include <iostream>
using namespace std;

class SoSimple    // Polymorphic 클래스 !! ShowSimpleInfo()가 가상함수이므로 .. 
{ 
public:
	virtual void ShowSimpleInfo()
	{
		cout << "SoSimple Base Class" << endl;
	}
};

class SoComplex : public SoSimple  
{
public:
	void ShowSimpleInfo()  // 이것 또한 가상함수 !!
	{
		cout << "SoComplex Derived Class" << endl;
	}
};

int main()
{
	SoSimple* simPtr = new SoComplex;
	SoComplex* comPtr = dynamic_cast<SoComplex*>(simPtr);
	comPtr->ShowSimpleInfo();

	return 0;
} 

                     🎈🎈 유도 클래스의 포인터 및 참조형으로의 형 변환에 사용할 수 있는 형 변환 연산자가 두 개라는 사실이
                          헷갈릴 수 있겠지만, 이는 그만큼 섬세한 코드구현이 가능하게 해준다.
  
       
         
         유도 클래스의 포인터 및 참조형으로의 형 변환을 시도할 때, 사용할 수 있는 두 연산자는 다음과 같다.
                      
         * dynamic_cast
         * static_cast
                       
         그렇다면 이 둘에는 어떤 차이가 있을까?
         형 변환을 시도한다는 사실에는 차이가 없지만, 그 결과에는 큰 차이가 있다.
                       
                       
int main()
{
	SoSimple* simPtr = new SoComplex;
	SoComplex* comPtr = dynamic_cast<SoComplex*>(simPtr);
	comPtr->ShowSimpleInfo();

	return 0;
}                    
                       
          위의 main() 에서 dynamic_cast 연산이 성공한 이유는 포인터 변수 simPtr이 실제 가리키는 객체가 SoComplex 객체이기 때문이다.
          즉, 포인터 변수 simPtr이 가리키는 객체를 SoComplex형 포인터 변수 comPtr이 함께 가리켜도 문제되지 않기 때문에 성공한 것이다.
            
          하지만 만약 main()을 이렇게 변경하면 어떻게 될까?
                       
        	SoSimple* simPtr = new simPtr;   <-- 변경된 부분
  
          이 경우에는 simPtr이 가리키는 대상을 comPtr이 가리킬 수 없는 상황이다.
          따라서 이러한 경우에는 형 변환의 결과로 NULL 포인터가 반환된다.
            
          이렇듯 dynamic_cast는 안정적인 형 변환을 보장한다. 
          특히 컴파일 시간이 아닌 실행 시간에(프로그램이 실행중인 동안에) 안전성을 검사하도록 컴파일러가 바이너리 코드를 생성한다는 점에
          주목할 필요가 있다. 물론 이로 인해서 실행속도는 늦어지지만, 그만큼 안정적인 형 변환이 가능한 것이다.
          그리고 이러한 이유로 연산자의 이름이 dynamic으로 시작하는 것이다.
            
          static_cast 연산자는 안전성을 보장하지 않는다. 컴파일러는 무조건 형 변환이 되도록 바이너리 코드를 생성하기 때문에, 
          그로 인해 실행의 결과는 전적으로 프로그래머가 책임져야 한다. 그래서 이러한 특성 때문에(실행중인 동안에 안전성 검사를
          진행하지 않는 특성 때문에) 연산자의 이름이 static으로 시작하는 것이다.
          물론, 실행속도는 빠르다. 실행 시간에 안전성 검사를 별도로 진행하지 않기 때문이다.
            
          "프로그래머가 정의하지 않아도 발생하는 예외도 있다. 이러한 유형의 예외 중 하나로, 형 변환시 발생하는 bad_cast 예외가 있다."
                       
                       
#include <iostream>
using namespace std;

class SoSimple
{
public:
	virtual void ShowSimpleInfo()
	{
		cout << "SoSimple Base Class" << endl;
	}
};

class SoComplex : public SoSimple
{
public:
	void ShowSimpleInfo()
	{
		cout << "SoComplex Derived Class" << endl;
	}
};

int main()
{
	SoSimple simObj;
	SoSimple& ref = simObj;

	try      //🎈🎈 이렇게 참조형 대상으로 dynamic_cast 연산을 진행할 경우에는 bad_cast 예외가 발생할 수 있기 때문에 이에 대한 예외처리를 해야 한다.
	{
		SoComplex& comRef = dynamic_cast<SoComplex&>(ref);
		// ref는 SoSimple 객체이기 때문에 SoComplex 참조형의 형 변환은 안전하지 못하다.
		// 그리고 참조형 대상으로는 NULL을 반환할 수 없기 떄문에 이러한 상황에서는 bad_cast 예외가 발생한다.
    
		comRef.ShowSimpleInfo();
	}
	catch (bad_cast expt)
	{
		cout << expt.what() << endl;
	}
	return 0;
}
                       
       
/*
실행결과 : Bad dynamic_cast!
*/
                       
                       
                       
                       
  
