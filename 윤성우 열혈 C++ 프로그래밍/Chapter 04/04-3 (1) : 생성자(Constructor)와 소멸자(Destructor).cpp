   
    '생성자'라는 것을 이용하면 객체도 생성과 동시에 초기화 할 수 있다.
      
      - 클래스의 이름과 함수의 이름이 동일하다.
      - 반환형이 선언되어 있지 않으며, 실제로 반환하지 않는다.
      - 객체 생성시 딱 한번 호출된다.
      
      
      - 생성자도 함수의 일종이니 오버로딩이 가능하다.
      - 생성자도 함수의 일종이니 매개변수에 '디폴트 값'을 설정할 수 있다.
      
--------------------------------------------
      
#include <iostream>
using namespace std;

class SimpleClass
{
private:
	int num1;
	int num2;
public:
	SimpleClass()
	{
		num1 = 0;
		num2 = 0;
	}

	SimpleClass(int n)
	{
		num1 = n;
		num2 = 0;
	}

	SimpleClass(int n1, int n2)
	{
		num1 = n1;
		num2 = n2;
	}

	//SimpleClass(int n1 = 3, int n2 = 5)
	//{
	//	num1 = n1;
	//	num2 = n2;
	//}

	void ShowData() const
	{
		cout << num1 << ' ' << num2 << endl;
	}
};

int main()
{ 
	SimpleClass sc1;                     // 🎈🎈	SimpleClass sc1();   <-- 이렇게 하면 안됨 오류발생❌  이건 함수의 원형이기 때문이다.
	//SimpleClass* sc1 = new SimpleClass;                  
	//SimpleClass* sc1 = new SimpleClass();
	sc1.ShowData();

	SimpleClass sc2(100);
	//SimpleClass* sc2 = new SimpleClass(100);            // 이런 식으로도 동적으로 할당을 해주어도 생성자 호출..!
	sc2.ShowData();

	SimpleClass sc3(100, 200);
	//SimpleClass* sc3 = new SimpleClass(100, 200);
	sc3.ShowData();

	//delete sc1;
	//delete sc2;
	//delete sc3;

	return 0;
}


--------------------------------------------------
  
💙 사과장수 코드 생성자로 수정 💙
  
#include <iostream>
using namespace std;

class FruitSeller              
{
private: 
	int APPLE_PRICE;
	int numOfApples;
	int myMoney;

public:
	FruitSeller(int price, int num, int money)   // 생성자 !
	{
		APPLE_PRICE = price;
		numOfApples = num;
		myMoney = money;
	}

	int SaleApples(int money)
	{
		int num = money / 1000;
		numOfApples -= num;
		myMoney += money;
		return num;
	}

	void ShowSalesResult()
	{
		cout << "남은 사과: " << numOfApples << endl;
		cout << "판매 수익: " << myMoney << endl << endl;
	}
};

class FruitBuyer
{
private:
	int myMoney;
	int numOfApples;

public:
	FruitBuyer(int money)    // 생성자 !
	{
		myMoney = money;
		numOfApples = 0;
	}

	void BuyApples(FruitSeller& seller, int money)
	{
		numOfApples += seller.SaleApples(money);
		myMoney -= money;
	}
	void ShowBuyResult()
	{
		cout << "현재 잔액: " << myMoney << endl;
		cout << "사과 개수: " << numOfApples << endl;
	}
};

int main()
{
	FruitSeller* seller = new FruitSeller(1000, 20, 0);       // 생성자로 멤버변수 초기화 !
	FruitBuyer buyer(5000);
	buyer.BuyApples(*seller, 2000);

	cout << "과일 판매자의 현황" << endl;
	seller->ShowSalesResult();
	cout << "과일 구매자의 현황" << endl;
	buyer.ShowBuyResult();

	delete seller;

	return 0;
}
--------------------------------------------------
  
🟢 멤버 이니셜라이저(Member Initializer)
  
🔷 Point.h

#ifndef __POINT_H_
#define __POINT_H_

class Point
{
private:
	int x;  // x좌표의 범위는 0 이상 100 이하
	int y;  // y좌표의 범위는 0 이상 100 이하

public:
  Point(const int& xpos, const int& ypos);     // ✅ 생성자 원형
	int GetX() const;
	int GetY() const;
	bool SetX(int xpos);
	bool SetY(int ypos);
};

#endif // __POINT_H_

                         
🔷 Point.cpp       

#include <iostream>
#include "Point.h"
using namespace std;

Point::Point(const int& xpos, const int& ypos)  // ✅ 생성자 
{
	x = xpos;
	y = ypos;
}

int Point::GetX() const  // const 함수
{
	return x;
}

int Point::GetY() const
{
	return y;
}

bool Point::SetX(int xpos)
{
	if (xpos < 0 || xpos > 100)
	{
		cout << "벗어난 범위의 값 전달" << endl;
		return false;
	}
	x = xpos;
	return true;
}

bool Point::SetY(int ypos)
{
	if (ypos < 0 || ypos > 100)
	{
		cout << "벗어난 범위의 값 전달" << endl;
		return false;
	}
	y = ypos;
	return true;
}


🔷 Rectangle.h

#ifndef __RECTANGLE_H_
#define __RECTANGLE_H_

#include "Point.h"

class Rectangle
{
private:
	Point upLeft;
	Point lowRight;

public:
  Rectangle(const int& x1, const int& y1, const int& x2, const int& y2);  // ✅ 생성자 원형
	void ShowRecInfo() const;
};

#endif //__RECTANGLE_H_


🔷 Rectangle.cpp

#include <iostream>
#include "헤더2.h"
using namespace std;

Rectangle::Rectangle(const int& x1, const int& y1, const int& x2, const int& y2) :upLeft(x1, y1), lowRight(x2, y2)  // ✅ 생성자 정의
{
      // empty
  
    /*
       🎈🎈 이게 결코 어려운 개념은 아님.. ㄹㅇ로 .. 아 정말로.. 
            우선 "이니셜라이저를 이용하면 선언과 동시에 초기화가 이뤄지는 형태로 바이너리 코드가 생성"된다는 것을 알아야한다.
            즉, Point 객체는 이니셜라이즈를 통해 upLeft와 lowRight에 각각 x1과 y1, x2와 y2를 넣어줌과 동시에 생성이되므로
            생성자 또한 불러오게 된다.
            
            이는 Point upLeft(x1, y1);   Point lowRight(x2, y2); 와 같은 의미를 가진다.
            
            (const 참조자를 매개변수로 가지는건 const 참조자는 상수로 초기화를 할 수 있기 때문에, 더 값을 넣기가 편해진다. // main() 참고)
    */ 
}

void Rectangle::ShowRecInfo() const
{
	cout << "좌 상단: " << '[' << upLeft.GetX() << ", ";
	cout << upLeft.GetY() << ']' << endl;
	cout << "우 하단: " << '[' << lowRight.GetX() << ", ";
	cout << lowRight.GetY() << ']' << endl << endl;
}


🔷 main.cpp

#include <iostream>
#include "Point.h"
#include "Rectangle.h"
using namespace std;

int main()
{
  Rectangle rec(1, 1, 5, 5);
	rec.ShowRecInfo();

	return 0;
}


       ✅ 객체의 생성과정 👍👍 (개인적으로 이해에 많은 도움을 주는 설명)

                   1단계 : 메모리 공간의 할당
                   2단계 : 이니셜라이저를 이용한 멤버변수(객체)의 초기화
                   3단계 : 생성자의 몸체부분 실행

                   만약, 이니셜라이저가 선언되지 않았다면, 메모리 공간의 할당과 생성자의 몸체부분의 실행으로 객체생성은 완성된다.
                     
                   그러나 생성자는 반드시 호출이 된다. '디폴트 생성자(default constructor)'라는게 자동으로 삽입되어 호출이 된다.
                     
                   
--------------------------------------------------
  
🟢 멤버 이니셜라이저(Member Initializer)를 이용한 변수 및 const 상수(변수) 초기화

#include <iostream>
using namespace std;

class Simple
{
private:
	int num1;
	int num2;

public:
	Simple(int n) : num2(n)    // 멤버변수 num2를 n으로 초기화
	{
		num1 = 3;
	}
	                                             🎈🎈 일반적으로 멤버변수의 초기화에 있어서는 이니셜라이즈를 선호하는 편이다.
	void ShowValue()                                  - 초기화의 대상을 명확히 인식할 수 있다.
	{                                                 - 성능에 약간의 이점이 있다.
		cout << "num1: " << num1 << endl;
		cout << "num2: " << num2 << endl;
	}
};

int main()                                     ✅ Q: 성능에 이점이 있다고???
{
	Simple sim(5);                                   A: 옆 코드의 생성자를 봐보자.
                                                      num1은 생성자의 몸체에서 초기화를 해주고, num2는 이니셜라이즈로 초기화를 해준다.
	sim.ShowValue();                                    이는 이러한 차이를 보인다.

	return 0;                                             int num1;  num1 = 3;     /    int num2 = 5;
}                              
                                                       비슷하지만 약간의 성능차이를 발생하는 것은 팩트다.
/*                                                     이러한 차이가 나는 이유는 위에서도 언급했듯이
  출력결과: num1: 3                                    "이니셜라이저를 이용하면 선언과 동시에 초기화가 이뤄지는 형태로 바이너리 코드가 생성된다."
            num2: 5                                   
*/                                                     따라서 "const 멤버변수도 이니셜라이저를 이용하면 초기화가 가능하다!"
                                                         
                                                         
-------------------------------------------------------
                                                         
     ✔ 위의 설명에서 이니셜라이즈를 이용하면 선언과 동시에 초기화가 된다고 했으므로
        const 멤버변수도 이니셜라이즈를 이용하면 초기화가 가능하다고 했다.
      
        이를 활용하여 사과장수 코드를 좀 더 수정해보자.

                                                         
// 사과장수 클래스                                                         
class FruitSeller
{
private:
	const int APPLE_PRICE;        // 상수 멤버변수 선언
	int numOfApples;
	int myMoney;

public:
	FruitSeller(int price, int num, int money) : APPLE_PRICE(price)  //  🎈🎈 이니셜라이즈를 활용하여 상수 멤버변수를 초기화
	{
		numOfApples = num;
		myMoney = money;
	}

	int SaleApples(int money)
	{
		int num = money / 1000;
		numOfApples -= num;
		myMoney += money;
		return num;
	}

	void ShowSalesResult()
	{
		cout << "남은 사과: " << numOfApples << endl;
		cout << "판매 수익: " << myMoney << endl << endl;
	}
};

                                                         
--------------------------------------------------
  
🟢 이니셜라이저의 이러한 특징은 멤버변수로 참조자를 선언할 수 있게 한다.
  
  
#include <iostream>               // 👊👊 코드 분석!!
using namespace std;

class AAA
{
public:
	AAA()
	{
		cout << "empty object" << endl;
	}

	void ShowYourName()
	{
		cout << "I'm class AAA" << endl;
	}
};

class BBB
{
private:
	AAA& ref;         // 참조자 멤버변수
	const int& num;

public:
	BBB(AAA& r, const int& n) : ref(r), num(n) {}  // ref안에 AAA& 넣어주기

	void ShowYourName()
	{
		ref.ShowYourName();
		cout << "and" << endl;
		cout << "I ref num " << num << endl;
	}
};

int main()
{
	AAA obj1;                // "empty object" 출력
	BBB obj2(obj1, 20);     
	obj2.ShowYourName();     // 함수 안에 있는 내용 출력
}                                                     


/*
  출력결과: empty object
            I'm class AAA
            and
            I ref num 20    
*/
                                                     
                                                         
--------------------------------------------------
  
🟢 디폴트 생성자

  메모리 공간의 할당 이후에 생성자의 호출까지 완료되어야 '객체'라 할 수 있다. 
  즉, 객체가 되기 위해서는 반드시 하나의 생성자가 호출되어야 한다.
  
  C++에서는 생성자가 정의되어 있지 않으면 디폴트 생성자를 자동으로 삽입해주고
  디폴트 생성자는 내부적으로 아무런 일을 하지 않는다.
  
  참고로, malloc 함수를 이용하면 생성자는 호출되지 않는다.
  
---------------------------------------------------------

#include <iostream>
using namespace std;

class Simple
{
private:
	int n;
public:
	Simple(int n) : n(n) {};
	Simple() : n(5) {};

	void Show()
	{
		cout << n << endl;
	}
};

int main()
{
	Simple s1(4);   
	Simple s2;

	s1.Show();   // 4 출력
	s2.Show();   // 5 출력
}

------------------------------------------------------
  
🟢 private 생성자         --> 객체의 생성방법을 제
 
#include <iostream>
using namespace std;

class AAA
{
private:
	int num;
public:
	AAA() :num(0) {}

	AAA& CreateInitObj(int n)const
	{
		AAA* ptr = new AAA(n);  // "힙에 할당딘 메모리 공간은 변수로 간주하여, 참조자를 통한 참조가 가능하다."
		return *ptr;
	}

	void ShowNum() const
	{
		cout << num << endl;
	}

private:
	AAA(int n) : num(n) {}
};

int main()
{
	AAA base;
	base.ShowNum();

	AAA& obj1 = base.CreateInitObj(3);
	obj1.ShowNum();

	AAA& obj2 = base.CreateInitObj(12);
	obj2.ShowNum();

	delete& obj1;
	delete& obj2;

	return 0;
}

