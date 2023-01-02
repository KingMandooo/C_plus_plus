C언어에서는 아래와 같이 동일한 이름의 함수가 정의되는 것을 허용하지 않는다.

int myFunc(int a)
{
  num ++;
  return num;
}

int myFunc(int a, int b)
{
  return a + b;
}

✅ 그 이유는 C언어에서는 함수의 이름만을 이용하여 호출 대상을 찾기 때문이다.
    반면에, C++은 '함수의 이름'과 '매개변수의 선언', 두 가지 정보를 동시에 활용하여 호출 대상을 찾는다.
    따라서 C++은 위와 같이 동일한 함수의 이름이 있어도 매개변수가 다르다면 별 무리가 되지 않는다.
  
    "매개변수의 자료형 또는 개수가 다르다"   <-- 이것을 만족해야함.
  

🎈🎈 잘못된 함수 오버로딩 예시 : void myFunc(int n) {},  int myFunc(int n) {}
                                 
                      --> 왜냐하면 두 함수의 이름과 매개변수가 같기 때문이다. 반환형은 함수를 구분하는 기준이 아니다.
    
                        
--------------------------------

#include <iostream>

void myFunc(void)
{
	std::cout << "myFunc(void) called by me" << std::endl;
}

void myFunc(int a, int b)
{
	std::cout << "myFunc(int a, int b) called by me" << std::endl;
}

void myFunc(char c)
{
	std::cout << "myFunc(char c) called by me" << std::endl;
}


int main()
{
	myFunc();
	myFunc('A');
	myFunc(6, 4);

	return 0;
}

/*
  출력결과: myFunc(void) called by me
            myFunc(char c) called by me
            myFunc(int a, int b) called by me
*/

---------------------------------------------------------------------
 
🟠 문제1

#include <iostream>

void swap(int* a, int* b);
void swap(char* a, char* b);
void swap(double* a, double* b);

int main()
{
	int num1 = 20, num2 = 500;
	std::cout << "바뀌기 전 : num1 = " << num1 << " num2 = " << num2 << std::endl;
	swap(&num1, &num2);
	std::cout << "바뀐 후 : num1 = " << num1 << " num2 = " << num2 << std::endl << '\n';

	char c1 = 'S', c2 = 'U';
	std::cout << "바뀌기 전 : c1 = " << c1 << " c2 = " << c2 << std::endl;
	swap(&c1, &c2);
	std::cout << "바뀐 후 : c1 = " << c1 << " c2 = " << c2 << std::endl << '\n';

	double d1 = 3.14, d2 = 171.3;
	std::cout << "바뀌기 전 : d1 = " << d1 << " d2 = " << d2 << std::endl;
	swap(&d1, &d2);
	std::cout << "바뀐 후 : d1 = " << d1 << " d2 = " << d2 << std::endl << '\n';
}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = *a;
}

void swap(double* a, double* b)
{
	double temp = *a;
	*a = *b;
	*b = *a;
}




/*
  출력결과: 바뀌기 전 : num1 = 20 num2 = 500
            바뀐 후 : num1 = 500 num2 = 20

            바뀌기 전 : c1 = S c2 = U
            바뀐 후 : c1 = U c2 = U

            바뀌기 전 : d1 = 3.14 d2 = 171.3
            바뀐 후 : d1 = 171.3 d2 = 171.3

*/
