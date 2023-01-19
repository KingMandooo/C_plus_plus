
            🎈🎈 상속은 재활용의 목적으로만 존재하는 문법적 요소가 아니다!!
             
------------------------------------------------------------------------
             
#include <iostream>
using namespace std;

class PermanentWorker    // 직원들 이름과 월급 알려주는 클래스
{
private:
	char name[100];
	int salary;
public:
	PermanentWorker(const char* name, int money) : salary(money)
	{
		strcpy(this->name, name);
	}
	int GetPay() const
	{
		return salary;
	}
	void ShowSalaryInfo() const
	{
		cout << "name: " << name << endl;
		cout << "salary: " << GetPay() << endl << endl;
	}
};

class EmployeeHandler    // 고용자들 정보 들어가 있는 클래스
{                                           
private: 
	PermanentWorker* empList[50];                //🎈🎈 EmployeeHandler 클래스와 같이 기능의 처리를 실제로 담당하는 클래스를 가리켜
	int empNum;                                  //     '컨트롤(control) 클래스' 또는 '핸들러(handler) 클래스'라 한다.
public:
	EmployeeHandler() : empNum(0) {}

	void AddEmployee(PermanentWorker* emp)
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
	EmployeeHandler handler;

	handler.AddEmployee(new PermanentWorker("KIM", 1000));
	handler.AddEmployee(new PermanentWorker("LEE", 1500));
	handler.AddEmployee(new PermanentWorker("JUN", 2000));

	handler.ShowAllSalaryInfo();

	handler.ShowTotalSalary();

	return 0;
}
                                    
                           🎈🎈 위의 코드는 확장성에 있어서 좋은 점수를 줄 수 없는 상태이다. 좋은 점수를 받으려면, SalesMan 클래스와
                                Temporary 클래스의 추가로 인한 변경을 최소화할 수 있어야 한다.
