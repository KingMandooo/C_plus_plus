🟢 함수 템플릿과 static 지역변수

  👉👉 충분히 코드만 보더라도 이해가 가능하다.

#include <iostream>
using namespace std;

template <class T>         // 함수 템플릿
void ShowStaticValue()    
{
	static T num = 0;       
	num += 1;
	cout << num << " ";
}

int main()
{
	ShowStaticValue<int>();   // 1 출력
	ShowStaticValue<int>();   // 2 출력
	ShowStaticValue<int>();   // 3 출력

	cout << endl;

	ShowStaticValue<long>();   // 1 출력
	ShowStaticValue<long>();   // 2 출력
	ShowStaticValue<long>();   // 3 출력
	
	return 0;
}

---------------------------------------------------------
  
🟢 클래스 템플릿과 static 멤버변수

  👉👉 충분히 코드만 보더라도 이해가 가능하다.

#include <iostream>
using namespace std;

template <class T>
class StaticValue
{
private:
	static T mem;
public:
	void AddMen(T num) { mem += num; }
	void ShowStaticValue() { cout << mem; }
};

template <class T>
T StaticValue<T>::mem = 0;

int main()
{
	StaticValue<int> obj1;
	StaticValue<int> obj2;
	obj1.AddMen(50);         
	obj2.AddMen(900);
	obj1.ShowStaticValue();      // 950 출력

	cout << endl;

	StaticValue<long> obj3;
	StaticValue<long> obj4;
	obj3.AddMen(300);
	obj4.ShowStaticValue();      // 300 출력
	
	return 0;
}

---------------------------------------------------------
  
   🎈🎈 정의 부분에 T가 존재하면 T에 대한 설명을 위해서 <class T>의 형태로 덧붙이면 되고,
        T가 존재하지 않으면 <>의 형태로 간단하게 선언하면 된다.
          
        사실 난 당연히 이렇다고 생각하고 있었다.
          
          
          
    🎈🎈 템플릿 static 멤버변수 또한 특수화가 필요한 경우가 있을 것이다.
          
          template <class T>
          T StaticValue<T>::mem = 0;

          이 경우에 자료형이 double일 경우의 템플릿은 
          
          template<>
          long StaticValue<long>::mem = 5;
   
          이렇게 정의해주면 된다.
     
          이제 main() 에서 StaticValue<long> obj3; 
          이렇게 선언을 해주면 static 변수인 mem이 5로 초기화가 되어있을 것이다.
   
     
     
