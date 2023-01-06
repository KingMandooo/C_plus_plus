
     참조자의 활용에는 함수가 큰 위치를 차지한다 !!
       
🟢 Call-by-reference 와 Call-by-value의 구분
       
int *SimpleFunc(int *ptr)
{
   ...                            이 함수의 정의가 Call-by-value라고 생각되는가, 아니면 Call-by-reference라 생각하는가???
}                                  

                               정답은 '둘 다 될 수 있다' 이다.
                                       

int *SimpleFunc(int *ptr)
{
   return ptr + 1;                 <-- 함수의 연산 주체는 값(value)이다. 다만 그 값이 주소 값 일뿐이다. 
}                                      주소 값에 1을 더한 결과를 반환하는 연산을 한다. (포인터 연산의 결과로 4가 증가)
                                 
        
                                 
int *SimpleFunc(int *ptr)
{
   if(ptr == NULL)                 <-- 반면에 이 함수는 주소 값을 이용해서 함수 외부에 선언된 변수를 '참조(reference)' 했으니, 이는 분명히 
     return NULL;                      Call-by-reference 라고 할 수 있다.
   
   *ptr = 20;  // 함수 외부에 선언된 변수에 접근.
   return ptr
}  


                      본래 C언어에서 말하는 Call-by-reference는 다음의 의미를 지닌다.
                        
                      "주소 값을 전달받아서, 함수 외부에 선언된 변수에 접근하는 형태의 함수호출"
                        
                      이렇듯 주소 값이 전달되었다는 사살이 중요한 게 아니라, 주소 값이 참조의 도구로 사용되었다는 사실이 중요한 것이며,
                      이것이 Call-by-value와 Call-by-reference를 구분하는 기준이 된다.
                        
                      🎈🎈 주소 값이 함수 외부에 선언된 변수에 접근하는 도구로 사용되었다는 사실이 Call-by-reference의 기준이 된다..!!!!
                        
                      C++에서는 두 가지 방식으로 Call-by-reference의 함수정의가 가능하다.
                        
                        - 주소 값을 이용한 Call-by-reference
                        - 참조자를 이용한 Call-by-reference
                        
                        
🟢 참조자를 이용한 Call-by-reference

#include <iostream>
using namespace std;

void Swap(int& num1, int& num2)                  // 참조자는 선언과 동시에 변수로 초기화되어야 한다. 따라서 매개변수로 받는 것이 납득이 안될 수 있다.
{                                                // 하지만 매개변수는 함수가 호출되어야 초기화가 진행되는 변수들이다.
	int temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

int main()
{
	int a = 3;
	int b = 500;

	Swap(a, b);

	cout << a << endl;        // 500 출력
	cout << b << endl;        //   3 출력

	return 0;
}

------------------------------------------------------------------------

🟠 문제 1
  
#include <iostream>
using namespace std;

void plusOne(int& num)
{
	num++;
}

void changeSign(int& num)
{
	num *= -1;
}

int main()
{
	int a = 50;

	plusOne(a);
	cout << a << endl;

	changeSign(a);
	cout << a << endl;

	return 0;
}


🟠 문제 2 
  
  
#include <iostream>
using namespace std;

void Swap(int& num1, int& num2)                 
{                                                
	int temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

int main()
{
	int a = 3;
	int b = 500;

  Swap(a, b);
	// Swap(10, 20);   <-- 이렇게 하면 오류나는 이유: 참조자는 변수에 대해서만 선언이 가능하기 때문이다.

	cout << a << endl;       
	cout << b << endl;        

	return 0;
}


🟠 문제 3 

#include <iostream>
using namespace std;

void SwapPointer(int* (&p1), int* (&p2))
{
	int* temp = p1;
	p1 = p2;
	p2 = temp;
}

void Swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int main()
{
	int num1 = 5;
	int* ptr1 = &num1;
	int num2 = 10;
	int* ptr2 = &num2;

	//Swap(&num1, &num2);      // 만약 이 함수를 사용한다면 ptr1과 ptr2는 여전히 각각 num1과 num2를 가리키고 있는 것이다.

	SwapPointer(ptr1, ptr2);   // 하지만 이 함수는 ptr1과 ptr2가 가리키는 것을 바꾸어준다.

	num1++;

	cout << *ptr1 << endl;    // 10 출력
	cout << *ptr2 << endl;    // 6 출력

	return 0;
}




