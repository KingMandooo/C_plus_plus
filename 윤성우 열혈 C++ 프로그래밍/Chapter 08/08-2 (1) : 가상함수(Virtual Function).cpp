#include <iostream>
using namespace std;

class AA
{
public:
	void AAShow()
	{
		cout << "AA Show()" << endl;
	}
};

class BB : public AA
{
public:
	void BBShow()
	{
		cout << "BB Show()" << endl;
	}
};

class CC : public BB
{
public:
	void CCShow()
	{
		cout << "CC Show()" << endl;
	}
};

int main()
{
	CC* cc = new CC();                        // 🎈🎈 포인터 형에 해당하는 클래스에 정의된 멤버에만 접근이 가능하다. 
	BB* bb = cc;                              //       "C++ 컴파일러는 포인터를 이용한 연산의 가능성 여부를 판단할 때, 포인터의 자료형을 기준으로
	AA* aa = bb;                              //        판단하지, 실제 가리키는 객체의 자료형을 기준으로 판단하지 않는다."

	aa->AAShow();
	//aa->BBShow();    ❌ 오류발생    <-- AA형에만 접근 가능.
	//aa->CCShow();    ❌ 오류발생

	bb->AAShow();
	bb->BBShow();
	//bb->CCShow();    ❌ 오류발생    <-- BB형에만 접근 가능.

	cc->AAShow();
	cc->BBShow();
	cc->CCShow();
}

-----------------------------------------------------------------------------------
  
🟢 함수의 오버라이딩과 포인터 형

--> 함수가 오버라이딩이 되어도, 포인터 형에 따라 자신에게 속해있는 함수를 호출한다.

#include <iostream>
using namespace std;

class AA
{
public:
	void Show()
	{
		cout << "AA Show()" << endl;
	}
};

class BB : public AA
{
public:
	void Show()   // 함수 오버라이딩
	{
		cout << "BB Show()" << endl;
	}
};

class CC : public BB
{
public:
	void Show()   // 함수 오버라이딩
	{
		cout << "CC Show()" << endl;
	}
};

int main()
{
	CC* cc = new CC();
	BB* bb = cc;    
	AA* aa = bb;    

	aa->Show();        // aa는 AA형 포인터이니, 이 포인터가 가리키는 객체를 대상으로 AA 클래스에 정의된 Show()를 호출해야겠다
  
	bb->Show();        // bb는 BB형 포인터이니, 이 포인터가 가리키는 객체에는 AA의 Show()와 BB의 Show()가 오버라이딩 관계로 존재하는군! 
                     // 그럼 오버라이딩을한 BB의 Show()를 호출해야겠다.
	cc->Show();         
}


/*
  출력결과:   AA Show()
              BB Show()
              CC Show()
*/

-----------------------------------------------------------------------------------
  
🟢 가상함수(Virtual Function)

#include <iostream>
using namespace std;

class AA
{
public:
	virtual void Show()
	{
		cout << "AA Show()" << endl;
	}
};

class BB : public AA                   // 🎈🎈 함수가 가상함수로 선언되면, 해당 함수호출 시, 포인터의 자료형을 기반으로 호출대상을 결정하지 않고,
{                                      //       포인터 변수가 실제로 가리키는 객체를 참조하여 호출의 대상을 결정한다.
public:
	virtual void Show()
	{
		cout << "BB Show()" << endl;
	}
};

class CC : public BB
{
public:
	virtual void Show()
	{
		cout << "CC Show()" << endl;
	}
};

int main()
{
	CC* cc = new CC();
	BB* bb = cc;     // 클래스 CC를 가리킴
	AA* aa = bb;     // 클래스 CC를 가리킴 왜냐하면 bb가 CC를 가리키니까

	aa->Show();
	bb->Show();
	cc->Show();
}


/*
  출력결과:   CC Show()
              CC Show()
              CC Show()
*/

-----------------------------------------------------------------------------------
  
🟢 '오렌지미디어 급여관리 확장석 문제'의 완전한 해결

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
	virtual int GetPay() const              // 🎈🎈 가상함수 추가!!
	{
		return 0;
	}
	virtual void ShowSalaryInfo() const     // 🎈🎈 가상함수 추가!!
	{}
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

class EmployeeHandler
{
private:                             
	Employee* empList[50];            
	int empNum;
public:
	EmployeeHandler() : empNum(0) {}

	void AddEmployee(Employee* emp)                  
	{                                               
		empList[empNum++] = emp;                       //  🎈🎈 empList[0]  ->   PermanentWorker 객체 가리킴    
	}                                                //  🎈🎈 empList[1]  ->   PermanentWorker 객체 가리킴    
	void ShowAllSalaryInfo() const                   //  🎈🎈 empList[2]  ->   TemporaryWorker 객체 가리킴    
	{                                                //  🎈🎈 empList[3]  ->   SalesWorker 객체 가리킴    
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
  실행결과:    name: KIM
               salary: 1000

               name: LEE
               salary: 1500

               name: Jung
               salary: 3500

               name: Hong
               salary: 1700
   
               salary sum: 7700
*/
