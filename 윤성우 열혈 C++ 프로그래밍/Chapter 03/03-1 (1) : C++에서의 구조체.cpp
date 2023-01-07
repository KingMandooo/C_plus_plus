
struct Car
{
	char gameID[ID_LEN];
	int fuelGauge;
	int carSpeed;
};


  C언어에서 위를 예시로 구조체 변수를 선언하는 방법은
  
         struct Car basicCar;   이런 식으로 해야한다.
           
           
           하지만 C++에서는 바로
           
           Car basicCar;    <-- 이런 식으로 별도의 typedef 선언 없이도 다음과 같이 변수를 선언할 수도 있다.


----------------------------------------

#include <iostream>
using namespace std;

#define ID_LEN 20
#define MAX_SPD 200
#define FUEL_STEP 2
#define ACC_STEP 10
#define BRK_STEP 10

struct Car
{
	char gameID[ID_LEN];
	int fuelGauge;
	int carSpeed;
};

void ShowCarState(const Car& car)
{
	cout << "소유자ID: " << car.gameID << endl;
	cout << "연료량: " << car.fuelGauge << "%" << endl;
	cout << "현재속도: " << car.carSpeed << "km/s" << endl << endl;
}

void Accel(Car& car)
{
	if (car.fuelGauge <= 0)
		return;
	else
		car.fuelGauge -= FUEL_STEP;

	if (car.carSpeed + ACC_STEP >= MAX_SPD)
	{
		car.carSpeed = MAX_SPD;
		return;
	}

	car.carSpeed += ACC_STEP;
}

void Break(Car& car)
{
	if (car.carSpeed < BRK_STEP)
	{
		car.carSpeed = 0;
		return;
	}

	car.carSpeed -= BRK_STEP;
}

int main()
{
	Car run99 = { "run99", 100, 0 };
	Accel(run99);
	Accel(run99);
	ShowCarState(run99);
	Break(run99);
	ShowCarState(run99);

	Car sped77 = { "sped77", 100, 0 };
	Accel(sped77);
	Break(sped77);
	ShowCarState(sped77);
	
	return 0;
}                   
                                     
                                   🎈🎈 위의 코드의 함수들은 구조체 Car에 종속된 함수라고 볼 수 있다.
                                        즉, "구조체 Car와 함께 부류를 형성하여, Car와 관련된 데이터의 처리를 담당하는 함수들이다."
                                     
                                        그러나 전역함수의 형태를 띠기 때문에, 이 함수들은 구조체 Car에 종속적이지 못하고
                                        다른 영역에서 이 함수를 호출할 수가 있다.
                                     
                                        이를 보완하기 위해서는 구조체 Car에 이러한 종속된 함수들을 묶어버리는 것이다.
                                        아래의 코드를 관찰해보자.

#include <iostream>
using namespace std;

#define ID_LEN 20
#define MAX_SPD 200
#define FUEL_STEP 2
#define ACC_STEP 10
#define BRK_STEP 10

struct Car
{
	char gameID[ID_LEN];
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
			fuelGauge -= FUEL_STEP;

		if (carSpeed + ACC_STEP >= MAX_SPD)
		{
			carSpeed = MAX_SPD;
			return;
		}

		carSpeed += ACC_STEP;
	}

	void Break()          // 구조체 안에 삽입된 함수
	{
		if (carSpeed < BRK_STEP)
		{
			carSpeed = 0;
			return;
		}

		carSpeed -= BRK_STEP;
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

------------------------------------------------------------------
  
🟠 문제 03-1
  
#include <iostream>
using namespace std;

struct Point
{
	int xpos;
	int ypos;

	void MovePos(int x, int y)
	{
		xpos += x;
		ypos += y;
	}

	void AddPoint(const Point &pos)
	{
		xpos += pos.xpos;
		ypos += pos.ypos;
	}

	void ShowPosition()
	{
		cout << "[" << xpos << "," << ypos << "]" << endl;
	}
};

int main()
{
	Point pos1 = { 12, 4 };
	Point pos2 = { 20, 30 };

	pos1.MovePos(-7, 10);
	pos1.ShowPosition();

	pos1.AddPoint(pos2);
	pos1.ShowPosition();

	return 0;
}
