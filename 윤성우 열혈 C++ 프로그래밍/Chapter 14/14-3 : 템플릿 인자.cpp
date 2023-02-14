
  템플릿을 정의할 때 결정되지 않은 자료형을 의미하는 용도로 사용되는 T 또는 T1, T2와 같은 문자를 가리켜 '템플릿 매개변수'라 한다.
  그리고 템플릿 매개변수에 전달되는 자료형 정보를 가리켜 '템플릿 인자'라 한다.
    
  template <class T>     // 여기서 T가 '템플릿 매개변수'
  class Simple { ... };

  int main()
  {
    Simple<int> aa;  // 여기서 int가 '템플릿 인자'
  }

----------------------------------------------------------------------------
  
  
#include <iostream>
using namespace std;

template <class T, int len>         //🎈🎈 템플릿 매개변수에도 변수가 올 수 있다.
class SimpleArray
{
private:
	T arr[len];
public:
	T& operator[] (int idx) { return arr[idx]; }
	SimpleArray<T, len>& operator= (const SimpleArray<T, len>& ref)
	{
		for (int i = 0; i < len; i++)
			arr[i] = ref.arr[i];
		return *this;
	}
};

int main()
{
	SimpleArray<int, 5> i5arr1;
	for (int i = 0; i < 5; i++)
		i5arr1[i] = i * 10;

	SimpleArray<int, 5> i5arr2;
	i5arr2 = i5arr1;
	for (int i = 0; i < 5; i++)
		cout << i5arr2[i] << ", ";
	cout << endl;

	SimpleArray<int, 7> i7arr1;
	for (int i = 0; i < 7; i++)
		i7arr1[i] = i * 10;

	SimpleArray<int, 7> i7arr2;
	i7arr2 = i7arr1;
	for (int i = 0; i < 7; i++)
		cout << i7arr2[i] << ", ";
	cout << endl;
  
  // i5arr1 = i7arr1;   <-- ✅ 이런식으로 서로 다른 형(type) 끼리는 서로 대입이 허용되지 않는다.
  //                            SimpleArray<int, 5>  !=   SimpleArray<int, 7>
	return 0;
}

      🎈🎈 위와 같은 방식으로 배열의 길이를 결정하지 않고, 만약 생성자를 통해서 배열의 길이를 결정하게 했다면,
           길이가 같은 배열에 대해서만 대입을 허용하기 위해서 추가적인 코드의 삽입이 불가피하며,
           이러한 추가적인 코드는 대입 및 복사의 과정에서 CPU가 수행해야 할 일을 늘리는 결과로 이어진다.
             
             
             
template <class T = int, int len = 100>         //🎈🎈 이렇게 템플릿 매개변수는 디폴트 값 지정도 가능하다.
class SimpleArray
{
private:
	T arr[len];
public:
	T& operator[] (int idx) { return arr[idx]; }
	SimpleArray<T, len>& operator= (const SimpleArray<T, len>& ref)
	{
		for (int i = 0; i < len; i++)
			arr[i] = ref.arr[i];
		return *this;
	}
};

int main()
{
  SimpleArray<> arr;   //🎈🎈 이런식으로 <> 안을 비워둘 수가 있다. 단, 기호는 반드시 추가돼야 한다.
}
