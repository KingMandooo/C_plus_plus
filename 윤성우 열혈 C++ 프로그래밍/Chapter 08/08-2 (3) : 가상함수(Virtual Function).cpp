🟢 다형성(Polymorphism)
  
  
  "다형성(polymorphism)'이란 '동질이상'을 의미한다.
  
  "모습은 같은데 형태는 다르다."
  
  "문장은 같은데 결과는 다르다."

  
#include <iostream>
using namespace std;

class First
{
public:
	virtual void SimpleFunc() { cout << "First" << endl; }
};

class Second : public First
{
public:
	virtual void SimpleFunc() { cout << "Second" << endl; }
};

int main()
{
	First* ptr = new First();
	ptr->SimpleFunc();          // First 출력
	delete ptr;

	ptr = new Second();
	ptr->SimpleFunc();          // Second 출력
	delete ptr;

	return 0;
}

           🎈🎈 ptr은 동일한 포인터 변수이다. 그럼에도 불구하고 실행결과는 다르다. 
                포인터 변수 ptr이 참조하는 객체의 자료형이 다르기 때문이다.
                이것이 바로 C++에서의 '다형성'의 예이다.
       
       
       
       
