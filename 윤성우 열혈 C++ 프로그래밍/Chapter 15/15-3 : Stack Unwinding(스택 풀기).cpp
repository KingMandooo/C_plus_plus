
#include <iostream>
using namespace std;

void Divide(int num1, int num2)
{
	if (num2 == 0)
	{
		throw num2;
	}
	cout << "두 수의 나눗셈: " << num1 / num2 << endl;
}

int main()
{
	int num1, num2;
	cout << "두 개의 숫자 입력: ";
	cin >> num1 >> num2;

	try
	{
		Divide(num1, num2);                 //🎈🎈 1. Divide 함수를 호출한다. --> 2. Divide 함수에서 예외처리를 하게 된다면 그 값이 Divide 함수에게 돌아온다.
		cout << "나눗셈 끝" << endl;
	}                                     //   ✅ Divide()에 try-catch 문이 없으므로 예외 데이터를 Divide()가 호출 된 시점으로 보내줬다.
	catch (int expn)
	{
		cout << expn << " 으로는 나눌 수 없습니다." << endl;
	}

	return 0;
}

                 🎈🎈 "호출 된 함수 안에서 예외가 처리되지 않으면, 함수를 호출한 영역으로 예외 데이터가 전달된다."

-------------------------------------------------------------------------------------------------------------------------
                   
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int StoI(char* str)
{
	int len = strlen(str);
	int num = 0;

	for (int i = 0; i < len; i++)
	{
		if (str[i] < '0' || str[i] >'9')
			throw str[i];       //  <-- 이 부분
    
                          //✅ "함수 내에서 함수를 호출한 영역으로 예외 데이터를 전달하면, 해당 함수는 더 이상 실행되지 않고 종료가 된다."
    
                               // 👆👆 위의 개념이 중요하다.
    
		num += (int)(pow((double)10, (len - 1) - i) * (str[i] + (7 - '7')));  // 문자열을 정수로 바꿔주는 코드
	}
	return num;
}

int main()             
{
	char str1[100];
	char str2[100];

	while (true)
	{
		cout << "두 개의 숫자 입력: ";
		cin >> str1 >> str2;

		try
		{
			cout << str1 << " + " << str2 << " = " << StoI(str1) + StoI(str2) << endl;
			break;
		}
		catch (char ch)
		{
			cout << "문자 " << ch << "가 입력되었습니다." << endl;
			cout << "재입력 진행합니다." << endl << endl;
		}
	}
	cout << "프로그램을 종료합니다." << endl;
	return 0;
}                 
                   
-------------------------------------------------------------------------------------------------------------------------
                   
🟢 스택 풀기(Stack Unwinding)
  
 --> 예외가 처리되지 않아서, 함수를 호출한 영역으로 예외 데이터가 전달되는 현상을 가리켜 '스택 풀기'라고 한다.
                   
                   
#include <iostream>
using namespace std;

void SimpleFuncOne();
void SimpleFuncTwo();
void SimpleFuncThree();

int main()
{
	try
	{
		SimpleFuncOne();
	}
	catch (int expn)
	{
		cout << "예외코드: " << expn << endl;
	}
	return 0;
}

void SimpleFuncOne()
{
	cout << "SimpleFuncOne()" << endl;
	SimpleFuncTwo();
}
void SimpleFuncTwo()
{
	cout << "SimpleFuncTwo()" << endl;
	SimpleFuncThree();
}
void SimpleFuncThree()
{
	cout << "SimpleFuncThree()" << endl;
	throw - 1;                            //🎈🎈 throw -1; --> SimpleFuncThree(); --> SimpleFuncTwo(); --> SimpleFuncOne(); 이런식으로 예외 데이터가 전달된다.
}                   
                   
                   ✅ Q. 왜 스택 풀기라고 부를까?
                      
                   ✅ A. SimpleFuncOne(); --> SimpleFuncTwo(); --> SimpleFuncThree(); --> throw -1; 
                          --> SimpleFuncThree(); --> SimpleFuncTwo(); --> SimpleFuncOne();
                   
                          이렇게 함수에 들어가고 예외 데이터를 만나서 함수가 풀리는 과정이 스택과 같은 형식을 띄기 때문이다.
                   
                   
                   🎈🎈 "예외가 처리되지 않아서, 예외 데이터가 main 함수에까지 도달했는데, main 함수에서조차 예외를 처리하지 않으면,
                         terminate 함수(프로그램을 종료시키는 함수)가 호출되면서 프로그램이 종료되어 버린다."
                            
                         --> 이 말은 예외 데이터를 발생시켰으면, 예외를 처리해줄 try-catch문이 반드시 필요하다는 것이다.
                           
                           
                          🟠 terminate 함수는 C++ 예외 처리와 함께 사용되며 다음과 같은 경우에 호출됩니다.

                           * throw된 C++ 예외에 대해 일치하는 catch 처리기를 찾을 수 없습니다.

                           * 스택 해제 중에 소멸자 함수가 예외를 throw한 경우

                           * 스택이 예외를 throw한 후에 손상된 경우
                           
                            출처: https://learn.microsoft.com/ko-kr/cpp/c-runtime-library/reference/terminate-crt?view=msvc-170
                   
 -------------------------------------------------------------------------------------------------------------------------
                  
🟢 자료형이 일치하지 않아도 예외 데이터는 전달됩니다.
   
int SimpleFunc()
{
	try
	{
		throw - 1;
	}
	catch (double expn)   //🎈🎈 예외 데이터의 자료형과 catch의 매개변수 형이 일치하지 않아 catch문이 실행되지 않는다.
	{                     //     따라서 SimpleFunc()를 호출한 영역으로 예외 데이터가 전달된다.
		cout << "예외코드: " << expn << endl;
	}
}
   
-------------------------------------------------------------------------------------------------------------------------
  
🟢 하나의 try 블록과 다수의 catch 블록

--> 아래의 코드와 같이 하나의 try문의 예외처리를 다양하게 할 수 있다.

#include <iostream>
using namespace std;

template <class T>
void SimpleFunc(T num);

int main()
{
	int num1;
	cin >> num1;
	SimpleFunc(num1);

	double num2;
	cin >> num2;
	SimpleFunc(num2);

	return 0;
}

template <class T>
void SimpleFunc(T num)
{
	try
	{
		throw num;
	}
	catch (int expn)
	{
		cout << "int 예외코드: " << expn << endl;
	}
	catch (double expn)
	{
		cout << "double 예외코드: " << expn << endl;
	}
}

/*
실행결과 :  10
            int 예외코드: 10
            3.14
            double 예외코드: 3.14
*/

-------------------------------------------------------------------------------------------------------------------------
  
🟢 전달되는 예외의 명시

int SimpleFunc(int num) throw (int, char);  
 
  --> 정의된 특성 함수의 호출을 위해서는 함수의 이름, 매개변수 선언, 반환형 정보에 더해서, 함수 내에서 전달 될 수 있는 예외의
      종류(예외 데이터의 자료형)과 그 상황도 알아야 한다. 그래야 해당 함수의 호출문장을 감싸는 적절한 try~catch문을 구성할 수 있다.
    
      (그니까 함수의 정의 옆에 throw 키워드를 사용해서 예외상황에서 반환되는 자료형을 명시해주어야 가독성과 좋은 코드를 짤 수 있다.
       함수 안에서 throw 키워드는 즉시, 현재의 함수를 종료하고 함수가 호출된 시점으로 예외 데이터를 보내기 때문에 try문에서 
       호출한 함수가 어떤 자료형의 예외 데이터를 보내는지 알 수 있으면 catch문을 잘 구현해낼 수 있다.)
    
      위의 throw 선언은 SimpleFnuc() 내에서 예외상황의 발생으로 인해, int형 예외 데이터와 char형 예외 데이터가 전달될 수 있음을 알리는 것이다.
      따라서 위의 원형 선언을 보고 난 뒤에는
      
	try
	{
		SimpleFunc(20);         
	}
	catch (int expn)
	{
		cout << "int 예외코드: " << expn << endl;
	}
	catch (char expn)
	{
		cout << "char 예외코드: " << expn << endl;
	} 
    
      이와 같이 int형과 char형에 대한 예외 코드를 짤 수가 있다.
      
        
        
          ✅ Q. 왜 때문에 다른 자료형의 예외가 전달될 경우 프로그램이 종료가 되는 것일까?
        
          ✅ A. 함수의 선언에 명시되지 않은 예외가 전달 될 경우 unexpected라는 이름의 함수가 호출이 되며,
                 이 함수의 기본 기능은 '프로그램의 종료(terminate 함수의 호출)'이다. 때문에 명시되지 않은
                 예외가 전달될 경우 프로그램이 종료되는 것이다.
                   
                   
💙 정리 💙
예외를 처리할 수 없는 함수 내에서 함수를 호출한 영역으로 예외 데이터를 전달하면, 해당 함수는 더 이상 실행되지 않고 종료가 된다.
그리고 만약 예외 데이터를 전달 받은 함수 또한 예외를 처리할 수 없으면 또 다시 해당 함수를 호출한 영역으로 예외 데이터를 전달한다.
이를 스택풀기라고 한다.

이렇게 예외 데이터를 전달하는 함수가 어떠한 자료형의 예외 데이터를 전달해주는지 명시할 수 있고,
이를 다양한 방식으로 처리할 수 있도록 try문에 여러 catch문을 달아 놓을 수 있다.
                   
