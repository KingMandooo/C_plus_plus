
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

char* MakeStrAdr(int len)
{
	char* str = (char*)malloc(sizeof(char) * len);    // malloc()을 사용하여 20크기의 문자열 배열 공간 할당
	return str;
}

int main()
{
	char* str = MakeStrAdr(20);
	strcpy(str, "I am so happy~");
	cout << str << endl;
	free(str);                      // str에 할당된 메모리 해제
}

--------------------------------------
    
     위 처럼 C언어에서의 동적할당에는 두 가지 불편사항이 있다.
      
    ✔ 할당할 대상의 정보를 무조건 바이트 크기단위로 전달해야 한다.
    ✔ 반환형이 void형 포인터이기 때문에 적절한 형 변환을 거쳐야 한다.
      
      
      
      그러나 C++ 에서 제공하는 new 와 delete를 사용하면 불편한 점이 사라진다.
       
      new는 malloc을 대신하고, delete는 free를 대신한다.
       
      
      - int형 변수의 할당 & 해제             :     int* ptr1 = new int;                /     delete ptr1;
      - double형 변수의 할당 & 해제          :     double* ptr2 = new double;          /     delete ptr2;   
      - 길이가 3인 int형 배열 할당 & 해제    :     int* arr1 = new int[3];             /     delete []arr1;  
      - 길이가 7인 double형 배열 할당 & 해제 :     double* arr2 = new double [7];      /     delete []arr2;


✅ new와 delete 를 사용하여 고친 코드

#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

char* MakeStrAdr(int len)
{
	//char* str = (char*)malloc(sizeof(char) * len);
	char* str = new char[len];
	return str;
}

int main()
{
	char* str = MakeStrAdr(20);
	strcpy(str, "I am so happy~");
	cout << str << endl;
	//free(str);
	delete[] str;
}



🟢 객체의 생성에서는 반드시 new & delete
  
#include <iostream>
#include <stdlib.h>
using namespace std;

class Simple
{
public:
	Simple()
	{
		cout << "I'm simple constructor!" << endl;
	}
};

int main()
{
	cout << "case 1: ";
	Simple* sp1 = new Simple;   // new를 사용하여 sp1 객체 생성

	cout << "case 2: ";
	Simple* sp2 = (Simple*)malloc(sizeof(Simple) * 1);   // malloc을 사용하여 sp2 객체    

	cout << endl << "end of main" << endl;
	
	delete sp1;
	free(sp2);
                                     // 🎈🎈 출력결과를 자세히보면 malloc()함수에 의해 생성된 Simple 객체는 생성자를 불러오지 않는다.                                                                  
	return 0;
}                                             이는 "new와 malloc 함수의 동작방식에는 차이가 있다" 는 것을 알 수 있다!!
 

/* 
  출력결과: case 1: I'm simple constructor!
            case 2:
            end of main
*/
      
      
      
      
      
🟢 포인터 연산 없이 힙 영역에 접근하는 법
      
int main()
{
	int* ptr = new int;

	int* (&ref) = ptr;
	*ref = 20;

	cout << *ptr << endl;   // 20 출력

	int& ref2 = *ptr;    <-- 🎈🎈 책에서 나온 예시
	ref2 = 50;

	cout << *ptr << endl;   // 50 출력

	return 0;
}

      

------------------------------------------------------------

🟠 문제 3  ❌
  
#include <iostream>
#include <stdlib.h>
using namespace std;

typedef struct __Point
{
	int xpos;
	int ypos;
} Point;

Point& PntAdder(const Point& p1, const Point& p2);

int main()
{
	Point* p1 = new Point;
	p1->xpos = 3;
	p1->ypos = 5;

	Point* p2 = new Point;
	p2->xpos = 10;
	p2->ypos = 2;

	//Point* sum = new Point;          <-- 🎈🎈 처음에 이렇게 할당을 했다. 하지만 문제가 있다.
	//*sum = PntAdder(*p1, *p2);                 *sum에 값을 반환을 해주면, main()의 sum과 PntAdder()의 sum은 서로 다른 곳을 가리키게 된다.
	//cout << sum->xpos << endl;                  결국 PntAdder()에서 힙에 할당한 sum은 해제를 못해주는 상황이 되어버린다.
	//cout << sum->ypos << endl;

	Point& sum = PntAdder(*p1, *p2);    // <-- 하지만 이렇게 참조자 sum에 포인터를 반환해주면 같은 힙 주소를 가리키므로,
	cout << sum.xpos << endl;           //     하나만 해제해줘도 같이 해제를 시켜줄 수가 있다.
	cout << sum.ypos << endl;

	delete p1;
	delete p2;
	delete &sum;

	return 0;
}

Point& PntAdder(const Point& p1, const Point& p2)
{
	Point* sum = new Point;
	sum->xpos = p1.xpos + p2.xpos;
	sum->ypos = p1.ypos + p2.ypos;

	return *sum;
}

      
      
      
      
