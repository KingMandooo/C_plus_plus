🟢 배열보다 나은 배열 클래스

	int s[3] = { 0 }; 
	printf("%d", s[-1]);       <--   C와 C++의 기본 배열은 다음과 같은 단점을 지니고 있다.
	printf("%d", s[-2]);
	printf("%d", s[-3]);               🎈🎈 "경계검사를 하지 않는다."
    
                     이러한 단점을 해결하기 위해서 '배열 클래스'라는 것을 디자인을 해본다.
    
                     우선,  객체 arrObject에 오버로딩된 []연산자를 사용하면 어떻게 해석이 될까?
    
                     arrObject[2];   -->    arrObject.operator[](2);

                     이렇게 해석된다.
                       
---------------------------------------------------------------------
                       
#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;
public:
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)       // 🎈🎈 이렇게 하면 배열접근의 안정성을 보장받을 수 있다.
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	~BoundCheckIntArray()
	{
		delete[] arr;
	}
};

int main()
{
	BoundCheckIntArray arr(5);
	for (int i = 0; i < 5; i++)
		arr[i] = (i + 1) * 11;  //  🎈🎈 arr.operator[](i); --> return arr[idx];
	for (int i = 0; i < 6; i++)
		cout << arr[i] << endl; //  🎈🎈 0~4 까지는 출력 5에선 배열 범위 벗어나서 경고문 출력

	return 0;
}

/*
  출력결과:   11
              22
              33
              44
              55
              Array index out of boud exception
*/

---------------------------------------------------

int main()
{
	BoundCheckIntArray arr(5);

	BoundCheckIntArray cpy1(5);   // 대입연산자 호출
	cpy1 = arr;

	BoundCheckIntArray cpy2 = arr;  // 복사생성자 호출

	return 0;
}

              만약 이렇게 위의 코드에 이 코드를 추가한다면 어떻게 될까?
                
              물론 디폴트 복사생성자와 디폴트 대입연산자는 얕은 복사만 함으로 깊은 복사가 진행되도록 
              복사생성자와 대입연산자를 따로 명시적으로 정의해줘야한다고 생각이 들기는 한다.
                
              그러나 그전에 더 중요시되는 원칙이 있다.
                
              🎈🎈 바로 배열은 저장소의 일조이고, 저장소에 저장된 데이터는 '유일성'이 보장되어야 한다는 것이다.
                   즉, 대부분의 경우 저장소의 복사는 불필요하거나 잘못된 일로 간주된다는 것이다.
           
              그렇다면 이를 위해서 우리는 복사생성자와 대입연산자를 아예 호출을 못하게 하는 방법을 사용한다.
                
              빈 상태로 정의된 복사 생성자와 대입 연산자를 private 멤버로 둠으로써 복사와 대입을 원칙적으로 막아놓았다.
                
#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;
	BoundCheckIntArray(const BoundCheckIntArray& copy) {}          // 🎈🎈 복사생성자와 대입연산자를 private에 선언.
	BoundCheckIntArray operator= (const BoundCheckIntArray& ref) {}
public:                             
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	~BoundCheckIntArray()
	{
		delete[] arr;
	}
};

int main()
{
	BoundCheckIntArray arr(5);

	BoundCheckIntArray cpy1(5);   
	cpy1 = arr;                     // ❌❌ 오류발생

	BoundCheckIntArray cpy2 = arr;  // ❌❌ 오류발생

	return 0;
}

------------------------------------------------------------------------
  
🟢 const 함수를 이용한 오버로딩의 활용

#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;
	BoundCheckIntArray(const BoundCheckIntArray& copy) {}
	BoundCheckIntArray operator= (const BoundCheckIntArray& ref) {}
public:
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx) const
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int GetArrLen() const { return arrlen; }
	~BoundCheckIntArray() { delete[] arr; }
};

void ShowAllData(const BoundCheckIntArray& ref)
{
	int len = ref.GetArrLen();
	for (int idx = 0; idx < len; idx++)
		cout << ref[idx] << endl;
                                  // ref는 const 객체이기 떄문에 const 함수만 호출이가능하다.
                                  // 그러나 ref.operator[](idx); 함수는 const 함수가 아니다.
                                  // 따라서 호출할 함수가 없기 때문에 오류가 발생한다.
}

int main()                        // 🎈🎈 그러나, const를 추가해도 배열을 멤버로 선언하는 경우에는 저장 자체가 불가능해지기 때문에 
{                                 //      좋은 방법이라고 할 수 없다.  👈👈 뭔 말이지????????
	BoundCheckIntArray arr(5);                                      // https://www.acmicpc.net/board/view/78189
	for (int i = 0; i < 5; i++)
		arr[i] = (i + 1) * 11;                                // ✅ 위의 궁금증에 대한 답은 아래에 내가 코드로 설명을 해놨다!!!!!!!
 
	ShowAllData(arr);

	return 0;
}

-------------------          🎈🎈 그래서 const 또한 함수 오버로딩이 된다는 것을 이용하여 똑같은 정의의 const함수를 선언해준다.
  
#include <iostream>
using namespace std;

class BoundCheckIntArray
{
private:
	int* arr;
	int arrlen;
	BoundCheckIntArray(const BoundCheckIntArray& copy) {}
	BoundCheckIntArray operator= (const BoundCheckIntArray& ref) {}
public:
	BoundCheckIntArray(int len) : arrlen(len)
	{
		arr = new int[len];
	}
	int& operator[] (int idx)
	{
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int& operator[] (int idx) const      // 🎈🎈 const 함수 선언
	{                                    //      이렇게 const 기반 오버로딩이 유용하다는 사실!!
		if (idx < 0 || idx >= arrlen)
		{
			cout << "Array index out of boud exception" << endl;
			exit(1);
		}
		return arr[idx];
	}
	int GetArrLen() const { return arrlen; }
	~BoundCheckIntArray() { delete[] arr; }
};

void ShowAllData(const BoundCheckIntArray& ref)
{
	int len = ref.GetArrLen();
	for (int idx = 0; idx < len; idx++)
		cout << ref[idx] << endl;
}

int main()
{
	BoundCheckIntArray arr(5);
	for (int i = 0; i < 5; i++)
		arr[i] = (i + 1) * 11;

	ShowAllData(arr);

	return 0;
}

--------------------------------------------------------

 ✅ 도대체 const 참조형 함수에서 멤버변수가 반환이 안되는지 이해가 안됐는데, 이제 이해됐다.
	
class StudyHard
{
private:
	int v;
public:
	int& aa() const
	{
		cout << v << endl;
		return v;  // const 함수내에서는 멤버변수 v 또한 const 형임.

		// 반환형이 참조형이면.
		// const int num1 = 3;
		// int& num2 = num1;      <---  이렇게하면 컴파일 에러가 발생한다.

		// 따라서 에러를 없애주기 위해서는
		// const int& num2 = num1;  <---  이렇게 선언해줘야 한다.

		// 자! 이제 다시 함수로 돌아와서 코드를 자세히 봐보면
		// 현재 int& aa() 의 반환값은 일반 참조형이다.
		// 그런데 이 함수는 const 함수이므로 함수 내의 멤버는 const형으로 바뀐다. (현재 멤버변수 v가 const형)
		// 그런데 만약 이 반환값을 받을 참조형이 
		// 예를 들어 int& b = aa(); 라면
		// const의 기본원리가 파괴되는 현상이 일어난다. (aa의 반환값이 const 이기 때문에..)
		
		// 그니까 애초에 C++ 이러한 모순을 막기 위해서 컴파일 오류를 발생하는 것이다.
		// 만약 const v를 반환하고 싶다면,
		// int& aa() 앞에 const를 붙여서 const int& 형을 반환해야할 것이다.
		
		// const int& aa() { ... } <-- 이렇게 말이다.
	}
};
