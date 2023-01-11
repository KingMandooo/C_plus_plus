
🟢 this 포인터의 활용 

class ThisClass
{
private:
	int a;
public:
  void ThisFunc(int a)          
	{
		a = 5;            // 매개변수 a에 5 저장
    
		this->a = 300;    // 멤버변수 a에 300 저장
	}
};

                    🎈🎈 이러한 특성을 활용하면, 매개변수의 이름을 멤버변수의 이름과 달리하기 위해서 고민할 필요가 없다.
                          (매개변수가 중점..)
                      
-------------------------------------------------------------

#include <iostream>
using namespace std;

class TwoNumber
{
private:
	int num1;
	int num2;
public:
	TwoNumber(int num1, int num2)
	{
		this->num1 = num1 + 100;           // 🎈🎈 유사한 성격을 지니는 두 변수의 이름을 구별되게 짓는 수고를 덜수있다. 
		this->num2 = num2;
	}

	/*TwoNumber(int num1, int num2) : num1(num1), num2(num2)
	{
	
	}*/

	void ShowNumber()
	{
		cout << num1 << endl;    // 104 출력
		cout << num2 << endl;    /    2 출력
	}
};

int main()
{
	TwoNumber two(4, 2);       
	two.ShowNumber();
}
-------------------------------------------------------------
  
🟢 Self-Reference의 반환

#include <iostream>
using namespace std;

class SelfRef
{
private:
	int num;

public:
	SelfRef(int n) : num(n)
	{
		cout << "객체생성" << endl;
	}

	SelfRef& Adder(int n)
	{
		num += n; 
		return *this;    // 자신의 참조 값을 반환
	}

	SelfRef& ShowTwoNumber()
	{
		cout << num << endl;
		return *this;    // 자신의 참조 값을 반환
	}
};

int main()
{
	SelfRef obj(3);
	SelfRef& ref = obj.Adder(2);  // ref는 obj를 참조할 수 있는 참조 값이 반환되었다.
  
  // 🎈🎈 참조자 ref에 obj.Adder()가 반환하는 참조 값을 받아서 ref는 obj를 참조할 수 있게 된다.

	obj.ShowTwoNumber();
	ref.ShowTwoNumber();

	ref.Adder(1).ShowTwoNumber().Adder(2).ShowTwoNumber();
}

-------------------------------------------------------------
  
🟢 참조의 정보(참조 값)에 대한 이해

int num = 7;
int& ref = num;  // 참조자 ref가 변수 num을 참조하고 있다.

            위의 코드에서 참조자 ref에 넘어가는 것이 변수 num의 값일까?
            그건 결코 아닐 것이다.
             
            "변수 num을 참조할 수 있는 참조의 정보가 전달된다."
              
            "변수 num을 참조할 수 있는 참조 값이 참조자 ref에 전달되어, ref가 변수 num을 참조하게 된다."
              
            따라서 왼편이 '참조자의 선언'이 오거나, 반환형으로 '참조형'이 선언되면, 
            그 때 전달되는 정보를 표현하기 위해서 '참조의 정보' 또는 '참조 값'이라는 표현을 사용한다.
              
              
