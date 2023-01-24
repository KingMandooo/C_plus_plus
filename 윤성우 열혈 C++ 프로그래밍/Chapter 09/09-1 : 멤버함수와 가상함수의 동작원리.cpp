🟢 객체 안에 정말로 멤버함수가 존재하는가?
  
// C언어 스타일로 구조체와 전역함수를 이용하여 C++의 객체와 멤버함수에 대한 관계를 따라한 코드
#include <iostream>
using namespace std;

typedef struct Data
{
	int data;
	void (*ShowData)(Data*);
	void (*Add)(Data*, int);
};

void ShowData(Data* THIS) { cout << "Data: " << THIS->data << endl; }
void Add(Data* THIS, int num) { THIS->data += num; }

int main()
{
	Data obj1 = { 15, ShowData, Add };
	Data obj2 = { 7, ShowData, Add };

	obj1.Add(&obj1, 17);
	obj2.Add(&obj2, 9);
	obj1.ShowData(&obj1);
	obj2.ShowData(&obj2);
	
	return 0;
}    
                       🎈🎈 위의 코드를 보면 두 개의 구조체 변수가 함수를 공유하고 있다.
                            그리고 실제로 C++의 객체와 멤버함수는 이러한 관계를 갖는다.
                            즉, 객체가 생성되면 멤버변수는 객체 내에 존재하지만, 멤버함수는 메모리의 한 공간에
                            별도로 위치하고선, 이 함수가 정의된 클래스의 모든 객체가 이를 공유하는 형태를 취한다.
                         
                         
                           멤버변수는 객체안에 존재! 
                           멤버함수는 별도의 메모리 공간에 위치! 그리고 서로 공유!!
                         
---------------------------------------------------------------------------------------------------
                         
🟢 가상함수의 동작원리와 가상함수 테이블

--> 한 개 이상의 가상함수를 포함하는 클래스에 대해서는 컴파일러가 '가상함수 테이블'이란 것을 만든다.
    이를 간단히 'V-Table(Virtual Table)'이라고도 한다. 이는 실제 호출되어야 할 함수의 위치정보를 담고있는 테이블이다.

                         
#include <iostream>
using namespace std;

class AAA
{
public:
	virtual void Func1() { cout << "Func1" << endl; }    
	virtual void Func2() { cout << "Func2" << endl; }
};

class BBB : public AAA
{
public:
	virtual void Func1() { cout << "BBB::Func1" << endl; }
	void Func3() { cout << "Func3" << endl; }
};

int main()
{
	AAA* aptr = new AAA();
	aptr->Func1();             // AAA 클래스의 Func1 호출

	BBB* bptr = new BBB();     // BBB 클래스의 Func1 호출
	bptr->Func1();
}

                       
            AAA 클래스의 가상함수 테이블    void AAA::Func1()      0x1024번지  
                                           void AAA::Func2()      0x2048번지
                           
            BBB 클래스의 가상함수 테이블    void BBB::Func1()      0x3072번지
                                           void AAA::Func2()      0x2048번지
                                           void BBB::Func3()      0x4096번지
                                           
            "AAA 클래스의 오버라이딩 된 가상함수 Funcl에 대한 정보가 존재하지 않는다."
            
            이렇게 오버라이딩 된 가상함수의 주소정보는 유도 클래스의 가상함수 테이블에 포함되지 않는다.
            때문에 오버라이딩 된 가상함수를 호출하면, 무조건 가장 마지막에 오버라이딩을 한 유도 클래스의 멤버함수가 호출되는 것이다.
              
              
              
              
              🎈🎈 가상함수 테이블은 객체의 생성과 상관없이 메모리 공간에 할당된다.
                   이는 가상함수 테이블이 멤버함수의 호출에 사용되는 일종의 데이터이기 때문이다.
                  
                   AAA 객체에는 AAA 클래스의 가상함수 테이블의 주소 값이 저장되고,
                   BBB 객체에는 BBB 클래스의 가상함수 테이블의 주소 값이 저장된다.
                     
                   즉, 가상함수를 하나이상 멤버로 지니는 클래스의 객체에는 가상함수 테이블의 주소 값이 저장된다.
                     
                     
              ✅  이렇게 클래스에 가상함수가 포함되면, 가상함수 테이블이 생성되고, 또 이 테이블을 참조하여
                  호출될 함수가 결정되기 때문에 실행속도가 감소하기 마련이다.
                  하지만 그 속도의 차이가 극히 미미하고 또 이러한 단점에도 불구하고 가상함수는 많은 장점을 제공하기 때문에
                  유용하게 활용되는 것이다.
              
