
 C++ 진영에서는 C 스타일의 형 변환 연산자를 가리켜 '오래된 C 스타일 형 변환 연산자(Old C-style cast operator)'라 부르기도 한다.
 이렇듯 C 스타일의 형 변환 연산자는 C언어와의 호환성을 위해서 존재할 뿐, C++에서는 새로운 형 변환 연산자와 규칙을 제공하고 있다.
   
 -------------------------------------------------------------------------------------------------
   
   ✅C언어의 형 변환은 강력해서 변환하지 못하는 대상이 없다.
      따라서 아래의 코드에서 나오는 문제점을 컴파일러는 잡아내지 못한다.
   
#include <iostream>
using namespace std;

class Car
{
private:
	int fuelGauge;
public:
	Car(int fuel) : fuelGauge(fuel) {}
	void ShowCarState() { cout << "잔여 연료량: " << fuelGauge << endl; }
};

class Truck : public Car
{
private:
	int freightWeight;
public:
	Truck(int fuel, int weight) : Car(fuel), freightWeight(weight) {}
	void ShowTruckState()
	{
		ShowCarState();
		cout << "화물의 무게: " << freightWeight << endl;
	}
};

int main()
{
	Car* pcar1 = new Truck(80, 200);
	Truck* ptruck1 = (Truck*)pcar1;    // 문제가 있지만, 문제 없어 보이는 형 변환 !
	ptruck1->ShowTruckState();         //🎈🎈 기초 클래스의 포인터 형을 유도 클래스의 포인터 형으로 형 변환하는 것은 일반적인 경우의 형 변환이 아니다.
                                           //     그래서 이러한 형 변환은 두 가지 측면의 판단이 존재한다. 
    
                                           //  1. "포인터 변수 pcar1이 가리키는 것은 Truck 객체니까 이는 의도적으로 작성된 코드이다."
 	cout << endl;                      //  2. "물론 결과만 놓고 보면 컴파일도 실행결과에도 문제가 없다. 하지만 이는 불필요한 형 변환이다. 
                                           //      굳이 Trcuk 객체를 Car형 포인터 변수로 가리킬 이유가 없다."
  
                                           //      이러한 유형의 논란과 문제점으로 C++에서는 4개의 연산자를 추가로 제공하고
                                           //      용도에 맞는 형 변환 연산자의 사용을 유도하고 있다. (아래에 써놈)
  
	Car* pcar2 = new Car(120);
	Truck* ptruck2 = (Truck*)pcar2;    // 문제가 바로 보이는 형 변환 !
	ptruck2->ShowTruckState();

	return 0;
}

/*
출력결과 :  잔여 연료량: 80
            화물의 무게: 200

            잔여 연료량: 120
            화물의 무게: -33686019
*/


      
      * static_const
      
      * const_cast
        
      * dynamic_cast
        
      * reinterpret_cast

           🎈🎈 위의 형 변환 연산자들을 사용하면 프로그래머는 자신의 의도한 바를 명확히 표시할 수 있다.
                따라서 컴파일러도 프로그래머의 실수를 지적해 줄 수 있고, 코드를 직접 작성하지 않은 프로그래머들도
                코드를 직접 작성한 프로그래머의 실수여부를 판달할 수 있다.

-------------------------------------------------------------------------------------------------

🟢 dynamic_cast : 상속관계에서의 안전한 형 변환

    dynamic_cast<T>(expr)  이러한 형태를 갖는다.
  
    //🎈🎈 형태를 보면 함수 템플릿임을 알 수 있다. ㅋ
  
    <> 사이에 변환하고자 하는 자료형의 이름을 두되, 객체의 포인터 또는 참조형이 와야 하며,
    () 사시에는 변환의 대상이 와야 한다.
      
    요구한 형 변환이 적절한 경우에는 형 변환된 데이터를 반환하지만, 요구한 형 변환이 적절하지 않은 경우에는 컴파일 에러가 발생한다.

    "상속관계에 놓여 있는 두 클래스 사이에서 유도 클래스의 포인터 및 참조형 데이터를 기초 클래스의 포인터 및 참조형 데이터로 형 변환하는 경우."


      
#include <iostream>
using namespace std;

class Car
{
private:
	int fuelGauge;
public:
	Car(int fuel) : fuelGauge(fuel) {}
	void ShowCarState() { cout << "잔여 연료량: " << fuelGauge << endl; }
};

class Truck : public Car
{
private:
	int freightWeight;
public:
	Truck(int fuel, int weight) : Car(fuel), freightWeight(weight) {}
	void ShowTruckState()
	{
		ShowCarState();
		cout << "화물의 무게: " << freightWeight << endl;
	}
};

int main()
{
	Car* pcar1 = new Truck(80, 200);
	Truck* ptruck1 = dynamic_cast<Truck*>(pcar1);  // ❌ 컴파일 에러 !!
	ptruck1->ShowTruckState();

	cout << endl;

	Car* pcar2 = new Car(120);
	Truck* ptruck2 = dynamic_cast<Truck*>(pcar2);  // ❌ 컴파일 에러 !!
	ptruck2->ShowTruckState();

	Truck* ptruck3 = new Truck(70, 150);
	Car* pcar3 = dynamic_cast<Car*>(ptruck3);    // ⭕ 컴파일 OK !!
  
  //🎈🎈 dynamic_cast 연산자를 사용했다는 것은 다음의 의미가 담겨 있다.
  //     "상속 관계에 있는 유도 클래스의 포인터 및 참조형 데이터를 기초 클래스의 포인터 및 참조형 데이터로 형 변환하겠습니다!"
  
  //     유도 클래스인 Truck의 객체를 기초 클래스인 Car 클래스로 형 변환하겠다. 라는 뜻
  
	ptruck3->ShowCarState();                       

	return 0;
}



  위의 코드에서 pcar2를 Truck 클래스로 형 변환하지 못한다는 것을 알겠다.
  그치만 pcar1은 Truck 클래스로 의도적으로 형 변환을 하고 싶을 때 어떻게 하면 될까?
    
  그럴 때 사용하는 키워드가 있다.
    
  바로 static_cast 연산자이다.

-------------------------------------------------------------------------------------------------

🟢 static_cast : A 타입에서 B 타입으로

    static_cast<T>(expr)  이러한 형태를 갖는다.
  
    //🎈🎈 형태를 보면 함수 템플릿임을 알 수 있다. ㅋ
  
    static_cast 연산자를 사용하는 우리들에게 컴파일러는 다음과 같이 이야기한다.
  
    "좋아! 유도 클래스의 포인터 및 참조형 데이터를 기초 클래스의 포인터 및 참조형 데이터로뿐만 아니라,
     기초 클래스의 포인터 및 참조형 데이터도 유도 클래스의 포인터 및 참조형 데이터로 아무런 조건 없이
     형 변환시켜 줄게, 하지만 그에 대한 책임은 네가 져야 해!"
  
  
int main()
{
	Car* pcar1 = new Truck(80, 200);
	Truck* ptruck1 = static_cast<Truck*>(pcar1);    // ⭕ 컴파일 OK !!
	ptruck1->ShowTruckState();

	cout << endl;

	Car* pcar2 = new Car(120);
	Truck* ptruck2 = static_cast<Truck*>(pcar2);    // ⭕ 컴파일 OK 그러나 ❓❓
	ptruck2->ShowTruckState();

	return 0;
}       

/*
출력결과 :  잔여 연료량: 80
            화물의 무게: 200

            잔여 연료량: 120
            화물의 무게: -33686019   <-- 실행결과를 통해 알 수 있는 static_cast의 위험성.
*/
                       위의 코드에서 Truck* ptruck1 = static_cast<Truck*>(pcar1); 은 충분히 가능한 코드이다.
                         
                       그러나 
  
                       Truck* ptruck2 = static_cast<Truck*>(pcar2); 는 컴파일은 되지만,
                       pcar2가 가리키는 대상은 Car 객체이기 때문에, 이는 정당화가 될 수 없는 문장이다.
                       따라서 이러한 형태로 문장을 구성하면 안 된다.
                         
                       "static_cast 연산자는 dynamic_cast 연산자와 달리, 보다 많은 형 변환을 허용합니다.
                        하지만 그에 따른 책임도 프로그래머가 져야 하기 때문에 신중하게 선택해야 합니다.
                        dynamic_cast 연산자를 사용할 수 있는 경우에는 dynamic_cast 연산자를 사용해서 
                        안정성을 높여야 하며, 그 외의 경우에는 정말 책임질 수 있는 상황에서만 제한적으로
                        static_cast 연산자를 사용해야 합니다."
                         
                         
         🎈🎈 static_cast 연산자는 기본 자료형 데이터간의 형 변환에도 사용이 된다.
                         
int main()
{
  int num1 = 20, num2 = 3;
  double result = 20 / 3;     <-- 여기서 result는 정수 / 정수를 했으므로, 6이 들어간다.
}
                                  때문에 실수형 나눗셈을 진행하려면 다음과 같이 나눗셈 문장을 구성하는데,

                                 double result = (double)20 / 3;
                                 double result = double(20) / 3;

                         C++에서는 static_cast 연산자를 이용한 다음의 문장구성을 더 추천한다.
                         
                         double result = static_cast<double>(20) / 3;

                  ✅ Q. C언어의 형변환를 사용하나 static_cast 연산자를 사용하나 똑같은데 왜 굳이 static_cast를 사용해야할까?
                    
                  ✅ A. static_cast 연산자는 '기본 자료형 간의 형 변환'과 '클래스의 상속관계에서의 형 변환'만을 허용한다.
                         그러나 C언어의 형 변환 연산자는 일반적이지 않은 형 변환도 허용을 하기에
                         static_cast 연산자의 사용은 의미를 가진다.
                    
                         따라서 static_cast 연산자를 본 순간 이와 같이 판단할 수 있다.
                    
                       "흠, 상속관계에 있는 클래스의 포인터 및 참조형 데이터의 형 변환인가? 아니면 기본 자료형 데이터의 형 변환인가?"
                    
                    
