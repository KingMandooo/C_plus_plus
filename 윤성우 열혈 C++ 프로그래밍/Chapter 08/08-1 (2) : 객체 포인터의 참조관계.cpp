🟢 '오렌지미디어 급여관리 확장성 문제'의 1차적 해결과 함수 오버라이딩

#include <iostream>
using namespace std;

class Employee
{
private:
	char name[100];
public:
	Employee(char* name)
	{
		strcpy(this->name, name);
	}
	void ShowYourName() const
	{
		cout << "name: " << name << endl;
	}
};

class PermanentWorker : public Employee   
{
private:
	int salary;
public:
	PermanentWorker(char* name, int money) : Employee(name), salary(money)
	{}
	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class EmployeeHandler   
{
private:
	Employee* empList[50];            // 🎈🎈 핵심! : Employee 객체의 주소 값을 저장하는 방식, 
	int empNum;                       //              Employee 클래스를 상속하는 클래스의 객체도 이 배열에 저장가능
public:
	EmployeeHandler() : empNum(0) {}

	void AddEmployee(Employee* emp)
	{
		empList[empNum++] = emp;                 // 🎈🎈 empList에 Employee 객체 주소값 저장
	}
	void ShowAllSalaryInfo() const
	{
		//for (int i = 0; i < empNum; i++)        <-- 주석을 풀면 오류 발생!
		//	empList[i]->ShowSalaryInfo();
	}
	void ShowTotalSalary() const
	{
		int sum = 0;
		//for (int i = 0; i < empNum; i++)        <-- 주석을 풀면 오류 발생!
		//	sum += empList[i]->GetPay();
		cout << "salary sum: " << sum << endl;
	}
	~EmployeeHandler()
	{
		for (int i = 0; i < empNum; i++)
			delete empList[i];
	}
};

int main()
{
	EmployeeHandler handler;

	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));
	handler.AddEmployee(new PermanentWorker("JUN", 2000));

	handler.ShowAllSalaryInfo();

	handler.ShowTotalSalary();

	return 0;
}

/*
  출력결과: salary sum: 0
*/

---------------------------------------------------------------------------------------------
  
🟢 오버라이딩

👉👉   참고 :  Override의 사전적 의미는 v.우선하다, 중단시키다 등이다. 
  
        자바에서 오버라이딩은 부모클래스로부터 상속받은 메소드를 재정의하는 것을 말한다. 
        오버라이딩된 메소드는 부모 클래스의 원래 메소드보다 우선되기 때문에 자식 객체에서 메소드 호출 시 오버라이딩 된 메소드가 호출된다.
        (C++도 마찬가지)
  
  
#include <iostream>
using namespace std;

class Employee  // 고용인
{
private:
	char name[100];
public:
	Employee(char* name)
	{
		strcpy(this->name, name);
	}
	void ShowYourName() const
	{
		cout << "name: " << name << endl;
	}
};

class PermanentWorker : public Employee    // 정규직
{
private:
	int salary;
public:
	PermanentWorker(char* name, int money) : Employee(name), salary(money)
	{}
	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class TemporaryWorker : public Employee  // 임시직
{
private:
	int workTime;
	int payPerHour;
public:
	TemporaryWorker(char* name, int pay) : Employee(name), workTime(0), payPerHour(pay)
	{}
	void AddWorkTime(int time)
	{
		workTime += time;
	}
	int GetPay() const
	{
		return workTime * payPerHour;
	}
	void ShowSalaryInfo() const
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}  
};

class SalesWorker : public PermanentWorker   // 영업직
{
private:
	int salesResult;
	double bonusRatio;
public:
	SalesWorker(char* name, int money, double bonusRatio)
		: PermanentWorker(name, money), salesResult(0), bonusRatio(bonusRatio) {}
	void AddSalesResult(int value)
	{
		salesResult += value;
	}
	int GetPay() const    // 🎈🎈 함수 오버라이딩               ✅ 기초 클래스인 PermanentWorker에 있는 GetPay()와 ShowSalaryInfo()를 
	{                                                           // 유도 클래스인 SalesWorker에도 추가하여 함수를 오버딩시켜주었다.
		return PermanentWorker::GetPay() + (int)(salesResult * bonusRatio);
	} 
	void ShowSalaryInfo() const     // 🎈🎈 함수 오버라이딩  
	{
		ShowYourName();                                  
		cout << "salary: " << GetPay() << endl << endl;
	}
};     // ✅ Q. 기초 클래스인 PermanentWorker와 유도 클래스인 SalesWorker의 ShowSalaryInfo()는 완전히 동일한데 왜 굳이 오버라이딩을 해줬을까?

class EmployeeHandler      
{
private:                             // ✅ A. 그건 바로 ShowSalaryInfo()의  GetPay() 함수는 각 클래스마다 서로 다르기 때문에
	Employee* empList[50];             //        ShowSalaryInfo()를 오버라이딩해줘야 각 클래스의  GetPay()를 불러오기 때문이다.
	int empNum;                                        
public:
	EmployeeHandler() : empNum(0) {}

	void AddEmployee(Employee* emp)                   // 🎈🎈 기초 클래스와 동일한 이름의 함수를 유도 클래스에서 정의한다고 해서
	{                                                 //      무조건 함수 오버라이딩이 되는 것은 아니다.
		empList[empNum++] = emp;                        //      매개변수의 자료형 및 개수가 다르면, 이는 함수 오버로딩이 되어,
	}                                                 //      전달되는 인자에 따라서 호출되는 함수가 결정된다.
	void ShowAllSalaryInfo() const                    //      즉, 함수 오버로딩은 상속의 관계에서도 구성이 될 수 있다.
	{
		//for (int i = 0; i < empNum; i++)              // 하지만 이름이 겹치는 함수가 존재하는 이상, 기초 class의 함수를 호출할 때에는 class의 이름을 명시해줘야함.
		//	empList[i]->ShowSalaryInfo();               // AA:Hello() 이런식으로.  08-1(1)에 나와있음.
	}
	void ShowTotalSalary() const
	{
		int sum = 0;
		//for (int i = 0; i < empNum; i++)
		//	sum += empList[i]->GetPay();
		cout << "salary sum: " << sum << endl;
	}
	~EmployeeHandler()
	{
		for (int i = 0; i < empNum; i++)
			delete empList[i];
	}
};

int main()
{
	// 직원관리를 목적으로 설계된 컨트롤 클래스의 객체생성
	EmployeeHandler handler;

	// 정규직 등록
	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));

	// 임시직 등록
	TemporaryWorker* alba = new TemporaryWorker("Jung", 700);
	alba->AddWorkTime(5);
	handler.AddEmployee(alba);

	// 영업직 등록
	SalesWorker* seller = new SalesWorker("Hong", 1000, 0.1);
	seller->AddSalesResult(7000);
	handler.AddEmployee(seller);
	
	// 이번 달에 지불해야 할 급여의 정보
	handler.ShowAllSalaryInfo();

	// 이번 달에 지불해야 할 급여의 총합
	handler.ShowTotalSalary();

	return 0;
}



/*
  출력결과: salary sum: 0   <-- 🎈🎈 아직 이게 정상임 아직 코드가 완성이 안됨. 08-2에서 계속...
*/  
