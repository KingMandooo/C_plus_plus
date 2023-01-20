🟢 '오렌지미디어 급여관리 확장성 문제'의 해결을 통해서 확인한 상속의 이유


  "상속을 하는 이유는 무엇인가?"
  
  "상속을 통해 연관된 일렬의 클래스에 대한 공통적인 규약을 정의할 수 있습니다."
  
  "상속을 통해 연관된 일렬의 클래스 PermanentWorker, TemporaryWorker, SalesWorker에 공통적인 규약을 정의할 수 있습니다."
  
   --> 여기서 일렬의 클래스 PermanentWorker, TemporaryWorker, SalesWorker에 적용된 공통규약은 Employee 클래스이다.
       이로 인해, Employee 클래스를 상속하는 모든 클래스의 객체는 Employee 객체로 바라볼 수 있게 된 것이다.
  
------------------------------------------------------------------------------------------------------------------
  
🟢 순수 가상함수(Pure Virtual Function)와 추상 클래스(Abstract Class)
  
  
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
	virtual int GetPay() const     // 🎈🎈 이렇게 클래스 중에서는 객체생성을 목적으로 정의되지 않는 클래스도 존재한다.
	{                              //      따라서 이러한 경우에는 가상함수를 '순수 가상함수'로 선언하여 객체의 생성을 문법적으로 막는 것이 좋다.
		return 0; 
	}
	virtual void ShowSalaryInfo() const 
	{}
};



class Employee 
{
private:
	char name[100];
public:
	Employee(char* name)
	{  
		strcpy(this->name, name);           //  🎈🎈 '순수 가상함수'란 '함수의 몸체가 정의되지 않는 함수'를 의미한다.    
	}                                     //       Employee 클래스는 순수 가상함수를지닌, 완전하지 않는 클래스가 되기 때문에
	void ShowYourName() const             //       객체를 생성하려 들면 컴파일 에러가 발생한다..!!
	{
		cout << "name: " << name << endl;
	}
	virtual int GetPay() const = 0;             // 순수 가상함수
	virtual void ShowSalaryInfo() const = 0;    // 순수 가상함수
};
          
                    ✅ 순수 가상함수를 통해 얻은 이점 두 가지.
                      
                       1. 잘못된 객체의 생성을 막을 수 있다.
                      
                       2. Employee 클래스의 GetPay함수와 ShowSalaryInfo 함수는 유도 클래스에 
                          정의된 함수가 호출되게끔 돕는데 의미가 있었을 뿐,
                          실제로 실행이 되는 함수는 아니었는데, 이를 보다 명확히 명시하는 효과도 얻게 되었다.
                            
                            
                            
             🎈🎈 이렇듯 하나 이상의 멤버함수를 순수 가상함수로 선언한 클래스를 가리켜 '추상 클래스(abstract class)'라 한다.
                  이는 완전하지 않은, 그래서 객체생성이 불가능한 클래스라는 의미를 지닌다...
                            
------------------------------------------------------------------------------------------------------------------                            
                            
🟠 문제 08-1  (다시 풀어보기) 
                            
#include <iostream>
using namespace std;

enum RISK_LEVEL { RISK_A = 30, RISK_B = 20, RISK_C = 10 };

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
	virtual int GetPay() const = 0;
	virtual void ShowSalaryInfo() const = 0;
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
	int GetPay() const   
	{                                                           
		return PermanentWorker::GetPay() + (int)(salesResult * bonusRatio);
	}
	void ShowSalaryInfo() const     
	{
		ShowYourName();
		cout << "salary: " << GetPay() << endl << endl;
	}
};     

class ForeignSalesWorker : public SalesWorker
{
private:                  // 🎈🎈정말로 클래스는 하나의 객체라고 생각하고 코드를 짜야겠다.
	const int riskRate;
public:
	ForeignSalesWorker(char* name, int money, double bonusRatio, int riskRate)
		: SalesWorker(name, money, bonusRatio), riskRate(riskRate) {}

	int GetRiskPay() const  // 🎈🎈ForeignSalesWorker가 받는 리스크 비용
	{
		return (int)(SalesWorker::GetPay() * (riskRate / 100.0));
	}
	int GetPay() const    // 🎈🎈ForeignSalesWorker가 받는 전체 비용
	{ 
		return SalesWorker::GetPay() + GetRiskPay();
	}
	void ShowSalaryInfo() const  // 🎈🎈ForeignSalesWorker의 봉급 출력  
	{
		ShowYourName();
		cout << "salary: " << SalesWorker::GetPay() << endl;
		cout << "risk pay: " << GetRiskPay() << endl;
		cout << "sum: " << GetPay() << endl << endl;
	}
};

class EmployeeHandler
{
private:                             
	Employee* empList[50];            
	int empNum;
public:
	EmployeeHandler() : empNum(0) {}

	void AddEmployee(Employee* emp)                  
	{                                               
		empList[empNum++] = emp;                      
	}                                               
	void ShowAllSalaryInfo() const                  
	{
		for (int i = 0; i < empNum; i++)              
			empList[i]->ShowSalaryInfo();              
	}
	void ShowTotalSalary() const
	{
		int sum = 0;
		for (int i = 0; i < empNum; i++)
			sum += empList[i]->GetPay();
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
	ForeignSalesWorker* fseller1 = new ForeignSalesWorker("Hong", 1000, 0.1, RISK_LEVEL::RISK_A);
	fseller1->AddSalesResult(7000);
	handler.AddEmployee(fseller1);

	ForeignSalesWorker* fseller2 = new ForeignSalesWorker("Yoon", 1000, 0.1, RISK_LEVEL::RISK_B);
	fseller2->AddSalesResult(7000);
	handler.AddEmployee(fseller2);

	ForeignSalesWorker* fseller3 = new ForeignSalesWorker("Lee", 1000, 0.1, RISK_LEVEL::RISK_C);
	fseller3->AddSalesResult(7000);
	handler.AddEmployee(fseller3);

	handler.ShowAllSalaryInfo();
	return 0;
}
                            
