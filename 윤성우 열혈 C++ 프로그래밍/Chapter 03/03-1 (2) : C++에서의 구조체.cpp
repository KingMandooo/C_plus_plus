03-1 (1)  에서 

#define ID_LEN 20
#define MAX_SPD 200
#define FUEL_STEP 2
#define ACC_STEP 10
#define BRK_STEP 10     와 같은 매크로 상수들은 구조체 Car에만 의미가 있는 상수들이다.

        
struct Car
{
	enum                          <--  이들을 구조체 안에 열거형 형태로 넣어주는 것도 방법이 될 수 있다.
	{
		ID_LEN = 20,
		MAX_SPD = 200,
		FUEL_STEP = 2,
		ACC_STEP = 10,
		BRK_STEP = 10,
	};
         ...
}


               🎈🎈 아니면 namespace를 사용하여 이들을 위한 공간을 따로 만드는 것도 방법이 될 수 있다. (아래코드)
                    이렇게하면 상수가 어떻게 사용되는지 가독성이 좋아진다.
                 

#include <iostream>
using namespace std;

namespace CAR_CONST    // 네임스페이스를 활용하여 구조체 Car에 종속되는 상수 공간 만듬..!
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

struct Car
{
	char gameID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int carSpeed;

	void ShowCarState()    // 구조체 안에 삽입된 함수
	{
		cout << "소유자ID: " << gameID << endl;
		cout << "연료량: " << fuelGauge << "%" << endl;
		cout << "현재속도: " << carSpeed << "km/s" << endl << endl;
	}

	void Accel()          // 구조체 안에 삽입된 함수
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

	void Break()          // 구조체 안에 삽입된 함수
	{
		if (carSpeed < CAR_CONST::BRK_STEP)
		{
			carSpeed = 0;
			return;
		}

		carSpeed -= CAR_CONST::BRK_STEP;
	}
};

int main()
{
	Car run99 = { "run99", 100, 0 };
	run99.Accel();
	run99.Accel();
	run99.ShowCarState();
	run99.Break();
	run99.ShowCarState();

	Car sped77 = { "sped77", 100, 0 };
	sped77.Accel();
	sped77.Break();
	sped77.ShowCarState();

	return 0;
}



🟢 함수는 외부로 뺄 수 있다.
  
  함수가 포함되어 있는 C++의 구조체를 보는 순간, 다음의 정보들이 쉽게 눈에 들어와야 코드의 분석이 용이하다.
  
  - 선언되어 있는 변수정보
  - 정의되어 있는 함수정보
  
----------------------------------
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

struct Car
{
	char gameID[CAR_CONST::ID_LEN];
	int fuelGauge;
	int carSpeed;

	void ShowCarState();   // 상태정보 출력
	void Accel();          // 엑셀, 속도증가
	void Break();          // 브레이크, 속도감소
};

int main()
{
	Car run99 = { "run99", 100, 0 };
	run99.Accel();
	run99.Accel();
	run99.ShowCarState();
	run99.Break();
	run99.ShowCarState();

	Car sped77 = { "sped77", 100, 0 };
	sped77.Accel();
	sped77.Break();
	sped77.ShowCarState();

	return 0;
}

void Car::ShowCarState()       // 구조체 Car 안의 ShowCarState()
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
  


       🎈🎈 구조체 안에 정의되어 있는 함수는 인라인으로 처리가 된다.  그러나 위의 코드처럼 구조체 밖으로 빼내면,
             이러한 의미가 사라진다. 따라서 인라인의 의미를 그대로 유지하려면 명시적으로 inline 키워드를 사용해서 지시해야한다.
               
               inline void Car::ShowCarState() { ... }
               inline void Car::Accel() { ... }
               inline void Car::Break() { ... }

