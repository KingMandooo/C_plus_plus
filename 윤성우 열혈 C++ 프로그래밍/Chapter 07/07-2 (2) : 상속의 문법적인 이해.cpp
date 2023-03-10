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
  μΆλ ₯κ²°κ³Ό:   SoBase() : 15
              SoDerived() : 15
              SoBase() : 27
              SoDerived() : 27
              ~SoDerived() : 27      // ππ λ³΄λ©΄ μλ©Έμλ μ λ ν΄λμ€κ° λ¨Όμ  μλ©Έλ λ€, κΈ°μ΄ ν΄λμ€κ° μλ©Έλλ€.
              ~SoBase() : 27         //      μ΄λ κ°μ²΄κ° μ€νμ μμ±λμ΄ μκΈ°μ μλ©Έμμλ μμ±μμμ λ°λμΈ κ²μ΄λ€.
              ~SoDerived() : 15
              ~SoBase() : 15
*/


-------------------------------------------------------------------------------------------------------------------------
  
π  λ¬Έμ  07-1(1)
  
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
		cout << "μμ¬ κ°μλ¦°: " << GetGasGauge() << endl;
		cout << "μμ¬ μ κΈ°λ: " << GetElecGauge() << endl;
		cout << "μμ¬ μν°λ: " << waterGauge << endl;
	}
};

int main()
{
	HybridWaterCar hybrid(100, 300, 400);

	hybrid.ShowCurrentGauge();

	return 0;
}



π  λ¬Έμ  07-1(2)
  
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
		cout << "μ΄λ¦: " << name << endl;
		cout << "λμ΄: " << age << endl;
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
		cout << "μ£Όμ: " << addr << endl;
		cout << "μ ν: " << phone << endl << endl;
	}
	~MyFriendDetailInfo()
	{
		delete[] addr;
		delete[] phone;
	}
};

int main()
{
	MyFriendDetailInfo me("μ νμ±", 24, "κ²½κΈ°λ λΆμ²μ", "010-1234-5678");
	me.ShowMyFriendDetailInfo();

	MyFriendDetailInfo you("μμ΄μ ", 30, "μμΈ", "010-1234-5678");
	you.ShowMyFriendDetailInfo();

	return 0;
}

