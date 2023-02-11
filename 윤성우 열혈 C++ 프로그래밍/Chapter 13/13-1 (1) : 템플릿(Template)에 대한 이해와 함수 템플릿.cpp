  
   "모형을 만들어 낸다. 모형의 틀은 결정되어 있지만, 모형의 색은 결정되어 있지 않아서 결정해야 한다."
     
     이는 모형자의 특징이다. 자를 대고 모형은 그리지만 그 속을 어떤 색으로 채울지는 우리가 결정해야 한다.
     
   "함수 템플릿은 함수를 만들어 낸다. 함수의 기능은 결정되어 있지만, 자료형은 결정되어 있지 않아서 결정해야 한다."
     
     함수 템플릿은 이렇듯, 모형자와 비슷한 특징을 가진다.
     
     🎈🎈 즉, 함수 템플릿은 다양한 자료형의 함수를 만드는 도구가 된다.
     
     
template <typename T>    // T는 자료형을 결정짓지 않겠다는 의미로 사용된다. 즉, 함수를 만들어 내는 템플릿을 정의하기 위해 사용된다.
T Add(T num1, T num2) 
{
     return num1 + num2;       
} 

                ✅ template <typename T> 대신에 template <class T> 를 사용해도 된다.
                   그리고 T라는 문자를 대신해서 다른 문자를 사용해도 된다.
                  
-------------------------------------------------------------------------
                  
#include <iostream>
using namespace std;

template <class T>
T Add(T num1, T num2)
{
	return num1 + num2;
}

int main()
{
	cout << Add<int>(3, 5) << endl;                // 8
	cout << Add<double>(1.7, 4.8) << endl;	       // 6.5
	cout << Add<int>(66, 2) << endl;               // 68
	cout << Add<double>(5.7, 1.2) << endl;         // 6.9

	return 0;
}

                     위의 코드를 보면 Add<int>(3, 5)와 Add<double>(1.7, 4.8)라는 문장이 있다.
                     이는 "T를 int와 double로 해서 만들어진 Add 함수를 호출한다."라는 뜻이다.
                     따라서 컴파일러는 저러한 문장을 보면 아래와 같은 함수를 만들어낸다.
                       
                     int Add<int>(int num1, int num2)
                     {
                        return num1 + num2;
                     }

                     double Add<double>(double num1, double num2)
                     {
                        return num1 + num2;
                     }
                     
                     🎈🎈 그렇다고 매번 문장마다 함수를 새로 만드는 것은 아니다.
                          한번 함수가 만들어지면, 그 다음에는 만들어진 함수를 호출한 뿐 새로운 함수를 만들지는 않는다.
                       
                       
                       그리고 함수를 호출할 때, 매번 
                       
                       	cout << Add<int>(3, 5) << endl;
	                      cout << Add<double>(1.7, 4.8) << endl;	 이런 식으로 호출할 필요는 없다.
                          
                        cout << Add(3, 5) << endl;
                        cout << Add(1.7, 4.8) << endl;	  이렇게 일반함수를 호출하듯이 호출할 수도 있다.
                        
                        왜냐하면, 전달되는 인자의 자료형을 참조하여 호출될 함수의 유형을 컴파일러가 결정하기 때문이다.
                          
-------------------------------------------------------------------------

🟢 함수 템플릿과 템플릿 함수

template <class T>            // 🎈🎈 이러한 유형을 '함수 템플릿(funtion template)'이라 한다.
T Add(T num1, T num2)
{
	return num1 + num2;
}


int Add<int>(int num1, int num2)  // 🎈🎈 이러한 유형을 템플릿 함수(template function)'이라 한다.
{
  return num1 + num2;
}

         
   둘을 헷갈릴 수도 있겠다.  그러나 이리 생각하면 헷갈리지 않는다.
     
   그냥 함수 템플릿은 템플릿을 의미하고, 
   템플릿 함수는 함수를 의미한다고 생각하면 된다.      
     
   '다산 정약용' 은 이 사람이 정약용이지 다산이지는 않는다. 다산은 그저 정약용을 꾸며줄 뿐이다.
   이처럼 함수 템플릿은 템플릿이지 함수가 아니다. 그저 함수는 템플릿을 꾸며줄 뿐이다.
     
   ✅ 함수 템플릿은 "함수를 만드는데 사용되는 템플릿",
      템플릿 함수는 "템플릿을 기반으로 만들어진 함수"  라고 생각하면 된다..!!
 
        
        🎈🎈 '템플릿 함수'는 컴파일러에 의해서 생성된 함수이기 때문에 '생성된 함수(Generated Function)'으로도 불린다.
              나중에 나올 '템플릿 클래스' 역시 '생성된 클래스(Generated Class)'라고도 불린다.

-------------------------------------------------------------------------

#include <iostream>
using namespace std;

template <class T>
T Add(T num1, T num2)
{
	return num1 + num2;
}

int Add(int num1, int num2)         // 🎈🎈 이렇게 함수 템플릿을 정의한 상황에서 일반함수까지 정의하는 것은 바람직하지는 않지만 가능하다.
{
	return num1 + num2;
}

double Add(double num1, double num2)
{
	return num1 + num2;
}

int main()
{
	cout << Add(3, 5) << endl;                     // Add() 호출
	cout << Add(1.7, 4.8) << endl;	
	cout << Add<int>(66, 2) << endl;               // Add<int>() 호출
	cout << Add<double>(5.7, 1.2) << endl;

	return 0;
}

-------------------------------------------------------------------------

🟢 둘 이상의 형(Type)에 대해 템플릿 선언하기
  
#include <iostream>
using namespace std;

template <class T1, class T2>                   
void ShowData(double num)
{
	cout << (T1)num << ", " << T2(num) << endl;   // 🎈🎈 이 문장을 보면 (T1)num과 T2(num)의 형변환을 다르게 한 것이 보인다.
}                                               //      이는 C++에서는 둘다 똑같은 의미를 가진다.
                                                //      a = (int)5.51;
                                                //      a =  int(5.51);   똑같다.
int main()
{
	ShowData<char, int>(65);           // A, 65    출력
	ShowData<int, char>(97);           // 97, a    출력
	ShowData<double, int>(3.14);       // 3.14, 3  출력

	return 0;
}

-------------------------------------------------------------------------

🟠 13-1 문제1
  
#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)
	{}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
};

template <typename T1, typename T2>
void SwapData(T1& p1, T2& p2)
{
	T1 temp = p1;
	p1 = p2;
	p2 = temp;
}

int main()
{
	Point p1(3, 5);
	Point p2(10, 200);

	SwapData(p1, p2);
	p1.ShowPosition();
	p2.ShowPosition();

	return 0;
}
  
  
🟠 13-1 문제2

#include <iostream>
using namespace std;

template <class T>
T SumArray(T arr[], int len)
{
	T sum = (T)0;
	for (int i = 0; i < len; i++)
		sum += arr[i];
	return sum;
}

int main()
{
	int arr1[5] = { 1, 2, 3, 4, 5 };
	double arr2[3] = { 1.1, 2.2, 3.3 };

	cout << SumArray(arr1, sizeof(arr1) / sizeof(int)) << endl;
	cout << SumArray(arr2, sizeof(arr2) / sizeof(double)) << endl;
	
	return 0;
}
