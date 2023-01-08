

        클래스는 구조체와 다르게 정의를 하는 과정에서 각각의 변수 및 함수의 접근 허용범위를 별도로 선언해야 한다.
          
          --> 접근제어 지시자를 통해서..    별도로 선언하지 않으면 모든 변수와 함수는 private로 선언된다. (구조체는 public)
          
                  
class Car
{
	char gameID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int carSpeed;

	void ShowCarState();  
	void Accel();          
	void Break();         
};

                    Car run99 = { "run99", 100, 0 };   // 오류 발생 ❌
                    run99.Accel();                     // 오류 발생 ❌
                    run99.ShowCarState();              // 오류 발생 ❌



🟢 접근제어 지시자(접근제어 레이블)
  
    - public    : 어디서든 접근허용
    
    - protected : 상속관계에 놓여있을 때, 유도 클래스에서의 접근허용
    
    - private   : 클래스 내(클래스 내에 정의된 함수)에서만 접근허용   
    

------------------------------------------
#include <iostream>
#include <cstring>
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

class Car                // Class Car
{
private: // private 접근제어 지시자
	char gameID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int carSpeed;

public:  // public 접근제어 지시자
	void InitMembers(const char* ID, int fuel); // <-- 🎈🎈  책과 다르게 const를 붙여준 이유: https://blog.naver.com/PostView.nhn?blogId=pk3152&logNo=221558157798
	void ShowCarState();   
	void Accel();          
	void Break();          
};

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

void Car::InitMembers(const char* ID, int fuel)         // 클래스 내에 정의된 함수로 private 멤버변수에 접근
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

                      
                          // private 멤버변수에 접근하기 위해서는 꼭 굳이 public으로 선언된 함수를 통해서 접근을 해야 하는 것인가..????????
------------------------------------------
  
🟢  용어정리: 객체(Object), 멤버변수, 멤버함수
  
  	Car run99;   <-- 위의 코드에서 run99은 '객체'이다.
      
    멤버변수 : 클래스를 구성하는(클래스 내에 선언된) 변수
    멤버함수 : 클래스를 구성하는(클래스 내에 정의된) 함수
  
  
  
