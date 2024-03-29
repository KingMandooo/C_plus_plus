#include <iostream>
using namespace std;

class Car
{
public:
	// 속도
	int speed;
	// 기어
	int gear;
	// 색깔
	const char* color;
	// 연비 (추가 변수)
	float fuelEfficiency;

	// 속도를 10만큼 증가하는 함수
	void speedUp()
	{
		speed += 10;
		cout << "현재 속도: " << speed << endl;
	}
	// 속도를 10만큼 감소하는 함수
	void speedDown()
	{
		speed -= 10;
		cout << "현재 속도: " << speed << endl;
	}
};

int main()
{
	Car myCar;
	myCar.speed = 100;
	myCar.gear = 3;
	myCar.color = "red";
	myCar.fuelEfficiency = 15.9f;

	myCar.speedUp();
	myCar.speedDown();

	// 추가 객체
	Car myCar2;
	myCar2.speed = 50;
	myCar2.gear = 2;
	myCar2.color = "yellow";
	myCar2.fuelEfficiency = 18.5f;

	myCar2.speedUp();
	myCar2.speedDown();

	return 0;
}
