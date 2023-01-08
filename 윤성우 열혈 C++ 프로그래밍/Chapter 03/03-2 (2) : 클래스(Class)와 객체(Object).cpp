
🟢 C++에서의 파일분할

   - Car.h   : 클래스의 선언을 담는다.
   - Car.cpp : 클래스의 정의(멤버함수의 정의)를 담는다.

🔷 1.cpp
  
#include "Car.h"
using namespace std;

int main()
{
	Car run99;
	run99.InitMembers("run99", 100);
	run99.Accel();
	run99.Accel();
	run99.Accel();
	run99.ShowCarState();
	run99.Break();
	run99.ShowCarState();

	return 0;
}

-----------------------------
🔷 Car.cpp

#include <iostream>
#include <cstring>
#include "Car.h"
using namespace std;

void Car::InitMembers(const char* ID, int fuel)
{
	strcpy(gameID, ID);
	fuelGauge = fuel;
	carSpeed = 0;
}

void Car::ShowCarState()       
{
	cout << "소유자ID: " << gameID << endl;
	cout << "연료량: " << fuelGauge << "%" << endl;
	cout << "현재속도: " << carSpeed << "km/s" << endl << endl;
}

void Car::Accel()
{
	if (fuelGauge <= 0)
		return;
	else
		fuelGauge -= CAR_CONST::FUEL_STEP;

	if (carSpeed + CAR_CONST::ACC_STEP >= CAR_CONST::MAX_SPD)
	{
		carSpeed = CAR_CONST::MAX_SPD;
		return;
	}

	carSpeed += CAR_CONST::ACC_STEP;
}

void Car::Break()
{
	if (carSpeed < CAR_CONST::BRK_STEP)
	{
		carSpeed = 0;
		return;
	}

	carSpeed -= CAR_CONST::BRK_STEP;
}

-----------------------------
🔷 Car.h      

#ifndef __CAR_H__
#define __CAR_H__

namespace CAR_CONST
{
	enum
	{
		ID_LEN = 20,
		MAX_SPD = 200,
		FUEL_STEP = 2,
		ACC_STEP = 10,
		BRK_STEP = 10,
	};
}

class Car
{
private:
	char gameID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int carSpeed;

public:
	void InitMembers(const char* ID, int fuel);
	void ShowCarState();   // 상태정보 출력
	void Accel();          // 엑셀, 속도증가
	void Break();          // 브레이크, 속도감소
};

#endif // __CAR_H__

-----------------------------------------------------------
  
🟢 인라인 함수는 헤더파일에 함께 넣어야 해요.
  
 🎈🎈 인라인함수는 "컴파일 과정에서 함수의 호출 문이 있느 곳에 함수의 몸체 부분이 삽입되어야 하므로!"
      클래스의 선언과 동일한 파일에 저장되어서 컴파일러가 동시에 참조할 수 있게 해야 한다.

🔷 Car.h 

#ifndef __CAR_H__
#define __CAR_H__

#include <iostream>
using namespace std;

namespace CAR_CONST
{
	enum
	{
		ID_LEN = 20,
		MAX_SPD = 200,
		FUEL_STEP = 2,
		ACC_STEP = 10,
		BRK_STEP = 10,
	};
}

class Car
{
private:
	char gameID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int carSpeed;

public:
	void InitMembers(const char* ID, int fuel);
	void ShowCarState();   // 상태정보 출력
	void Accel();          // 엑셀, 속도증가
	void Break();          // 브레이크, 속도감소
};

inline void Car::ShowCarState()                    
{
	cout << "소유자ID: " << gameID << endl;
	cout << "연료량: " << fuelGauge << "%" << endl;
	cout << "현재속도: " << carSpeed << "km/s" << endl << endl;
}

inline void Car::Accel()
{
	if (fuelGauge <= 0)
		return;
	else
		fuelGauge -= CAR_CONST::FUEL_STEP;

	if (carSpeed + CAR_CONST::ACC_STEP >= CAR_CONST::MAX_SPD)
	{
		carSpeed = CAR_CONST::MAX_SPD;
		return;
	}

	carSpeed += CAR_CONST::ACC_STEP;
}

#endif // __CAR_H__
  
-----------------------------------------------------------
  
🟠 문제 03-2(1)
  
🔷 main.cpp 
  
#include <iostream>
#include "calculaotr.h"
using namespace std;

int main()
{
	Calculator cal;
	cal.Init();
	cout << "3.2 + 2.4 = " << cal.Add(3.2, 2.4) << endl;
	cout << "3.5 / 1.7 = " << cal.Div(3.5, 1.7) << endl;
	cout << "2.2 - 1.5 = " << cal.Min(2.2, 1.5) << endl;
	cout << "4.9 / 1.2 = " << cal.Div(4.9, 1.2) << endl;
	cal.ShowOpCount();

	return 0;
}
  
🔷 calculator.cpp 

#include <iostream>
#include "calculator.h"
using namespace std;

double Calculator::Add(double a, double b)
{
	AddCount++;
	return a + b;
}

double Calculator::Min(double a, double b)
{
	MinCount++;
	return a - b;
}

double Calculator::Mult(double a, double b)
{
	MultCount++;
	return a * b;
}

double Calculator::Div(double a, double b)
{
	DivCount++;
	return a / b;
}

🔷 calculaotr.h 

#ifndef __Cal__
#define __Cal__
#include <iostream>

using namespace std;

class Calculator
{
private:
	int AddCount;
	int MinCount;
	int MultCount;
	int DivCount;

public:
	inline void Init();
	inline void ShowOpCount();
	double Add(double a, double b);
	double Min(double a, double b);
	double Mult(double a, double b);
	double Div(double a, double b);
};

inline void Calculator::Init()
{
	AddCount = 0;
	MinCount = 0;
	MultCount = 0;
	DivCount = 0;
}

inline void Calculator::ShowOpCount()
{
	cout << "덧셈: " << AddCount << " 뺄셈: " << MinCount << " 곱셈: " << MultCount << " 나눗셈: " << DivCount << endl;
}

#endif



🟠 문제 03-2(2)
  
🔷 main.cpp 

#include <iostream>
#include "setstring.h"
using namespace std;

int main()
{
	Printer pnt;
	pnt.SetString("Hello, World!");
	pnt.ShowString();

	pnt.SetString("I love YOU.. !");
	pnt.ShowString();
	
	return 0;
}

🔷 setstring.cpp 

#include <iostream>
#include "setstring.h"
using namespace std;

void Printer::SetString(const char* p)
{
	arr = p;
  //strcpy(arr, p);
}

void Printer::ShowString()
{
	cout << arr << endl;
}

🔷 setstring.h 

#ifndef __PRINTER
#define __PRINTER

class Printer
{
private:
	const char* arr;
  //char arr[30];

public:
	void SetString(const char* p);
	void ShowString();
};

#endif // __PRINTER

  
  
  
