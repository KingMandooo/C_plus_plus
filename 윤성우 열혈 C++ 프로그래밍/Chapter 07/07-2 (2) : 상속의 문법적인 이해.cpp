#include <iostream>
using namespace std;

class SoBase
{
private:
	int baseNum;
public:
	SoBase(int n) : baseNum(n)
	{
		cout << "SoBase() : " << baseNum << endl;
	}
	~SoBase()
	{
		cout << "~SoBase() : " << baseNum << endl;
	}
};

class SoDerived : public SoBase
{
private:
	int derivNum;
public:
	SoDerived(int n) : SoBase(n), derivNum(n)
	{
		cout << "SoDerived() : " << derivNum << endl;
	}
	~SoDerived()
	{
		cout << "~SoDerived() : " << derivNum << endl;
	}
};

int main()
{
	SoDerived drv1(15);
	SoDerived drv2(27);

	return 0;
}


/*
  출력결과:   SoBase() : 15
              SoDerived() : 15
              SoBase() : 27
              SoDerived() : 27
              ~SoDerived() : 27      // 🎈🎈 보면 소멸자는 유도 클래스가 먼저 소멸된 뒤, 기초 클래스가 소멸된다.
              ~SoBase() : 27         //      이는 객체가 스택에 생성되어 있기에 소멸순서는 생성순서와 반대인 것이다.
              ~SoDerived() : 15
              ~SoBase() : 15
*/


-------------------------------------------------------------------------------------------------------------------------
  
🟠 문제 07-1(1)
  
#include <iostream>
using namespace std;

class Car
{
private:
	int gasolineGauge;
public:
	Car(int gg) : gasolineGauge(gg)
	{

	}
	int GetGasGauge()
	{
		return gasolineGauge;
	}
};

class HybridCar : public Car
{
private:
	int electricGauge;
public:
	HybridCar(int eg, int gg) : electricGauge(eg), Car(gg)
	{

	}
	int GetElecGauge()
	{
		return electricGauge;
	}
};

class HybridWaterCar : public HybridCar
{
private:
	int waterGauge;
public:
	HybridWaterCar(int wg, int eg, int gg) : waterGauge(wg), HybridCar(eg, gg)
	{

	}
	void ShowCurrentGauge()
	{
		cout << "잔여 가솔린: " << GetGasGauge() << endl;
		cout << "잔여 전기량: " << GetElecGauge() << endl;
		cout << "잔여 워터량: " << waterGauge << endl;
	}
};

int main()
{
	HybridWaterCar hybrid(100, 300, 400);

	hybrid.ShowCurrentGauge();

	return 0;
}



🟠 문제 07-1(2)
  
#include <iostream>
#include <cstring>
using namespace std;

class MyFriendInfo
{
private:
	char* name;
	int age;
public:
	MyFriendInfo(char* name, int age) : age(age)
	{
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	void ShowMyFriendInfo()
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age << endl;
	}
	~MyFriendInfo()
	{
		delete[] name;
	}
};

class MyFriendDetailInfo : public MyFriendInfo
{
private:
	char* addr;
	char* phone;
public:
	MyFriendDetailInfo(char* name, int age, char* addr, char* phone) : MyFriendInfo(name, age)
	{
		this->addr = new char[strlen(addr) + 1];
		strcpy(this->addr, addr);

		this->phone = new char[strlen(phone) + 1];
		strcpy(this->phone, phone);
	}
	void ShowMyFriendDetailInfo()
	{
		ShowMyFriendInfo();
		cout << "주소: " << addr << endl;
		cout << "전화: " << phone << endl << endl;
	}
	~MyFriendDetailInfo()
	{
		delete[] addr;
		delete[] phone;
	}
};

int main()
{
	MyFriendDetailInfo me("선태욱", 24, "경기도 부천시", "010-1234-5678");
	me.ShowMyFriendDetailInfo();

	MyFriendDetailInfo you("아이유", 30, "서울", "010-1234-5678");
	you.ShowMyFriendDetailInfo();

	return 0;
}

