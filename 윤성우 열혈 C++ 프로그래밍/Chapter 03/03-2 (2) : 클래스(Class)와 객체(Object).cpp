
π’ C++μμμ νμΌλΆν 

   - Car.h   : ν΄λμ€μ μ μΈμ λ΄λλ€.
   - Car.cpp : ν΄λμ€μ μ μ(λ©€λ²ν¨μμ μ μ)λ₯Ό λ΄λλ€.

π· 1.cpp
  
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
π· Car.cpp

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
	cout << "μμ μID: " << gameID << endl;
	cout << "μ°λ£λ: " << fuelGauge << "%" << endl;
	cout << "νμ¬μλ: " << carSpeed << "km/s" << endl << endl;
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
π· Car.h      

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
	void ShowCarState();   // μνμ λ³΄ μΆλ ₯
	void Accel();          // μμ, μλμ¦κ°
	void Break();          // λΈλ μ΄ν¬, μλκ°μ
};

#endif // __CAR_H__

-----------------------------------------------------------
  
π’ μΈλΌμΈ ν¨μλ ν€λνμΌμ ν¨κ» λ£μ΄μΌ ν΄μ.
  
 ππ μΈλΌμΈν¨μλ "μ»΄νμΌ κ³Όμ μμ ν¨μμ νΈμΆ λ¬Έμ΄ μλ κ³³μ ν¨μμ λͺΈμ²΄ λΆλΆμ΄ μ½μλμ΄μΌ νλ―λ‘!"
      ν΄λμ€μ μ μΈκ³Ό λμΌν νμΌμ μ μ₯λμ΄μ μ»΄νμΌλ¬κ° λμμ μ°Έμ‘°ν  μ μκ² ν΄μΌ νλ€.

π· Car.h 

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
	void ShowCarState();   // μνμ λ³΄ μΆλ ₯
	void Accel();          // μμ, μλμ¦κ°
	void Break();          // λΈλ μ΄ν¬, μλκ°μ
};

inline void Car::ShowCarState()                    
{
	cout << "μμ μID: " << gameID << endl;
	cout << "μ°λ£λ: " << fuelGauge << "%" << endl;
	cout << "νμ¬μλ: " << carSpeed << "km/s" << endl << endl;
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
  
π  λ¬Έμ  03-2(1)
  
π· main.cpp 
  
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
  
π· calculator.cpp 

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

π· calculaotr.h 

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
	cout << "λ§μ: " << AddCount << " λΊμ: " << MinCount << " κ³±μ: " << MultCount << " λλμ: " << DivCount << endl;
}

#endif



π  λ¬Έμ  03-2(2)
  
π· main.cpp 

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

π· setstring.cpp 

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

π· setstring.h 

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

  
  
  
