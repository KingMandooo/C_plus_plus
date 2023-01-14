
🟢 const 객체와 const 객체의 특성들

   const SoSimple sim(20);   //  🎈🎈 "이 객체의 데이터 변경을 허용하지 않겠다!"
   
   const 선언이 붙게 되면, 이 객체를 대상으로는 const 멤버함수만 호출이 가능하다.
     
------------------------------------------------------------------------------------ 
     
#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
  int test;
  
	SoSimple(int n) : num(n) {}                    🎈🎈 멤버변수에 저장된 값을 수정하지 않는 함수는 가급적 const로 선언해서, const 객체에도
                                                      호출이 가능하도록 할 필요가 있다.
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}
  
	void ShowData() const
	{
		cout << "num: " << num << endl;
	}
};

int main()
{
	const SoSimple obj(7);
	//obj.AddNum(20);         <-- const가 아닌 함수 호출 불가
	obj.ShowData();

  obj.test;
	//obj.test++; <-- 이건 오류 발생
  
	return 0;
}

------------------------------------------------------------------------------------     
  
🟢 const와 함수 오버로딩

      void SoSimpleFunc() { ... }               이 두가지 형태의 함수로도 오버로딩이 가능하다.
      void SoSimpleFunc() const { ... }         (🎈🎈 const의 선언 유무도 함수 오버로딩의 조건에 해당된다.)




#include <iostream>
using namespace std;

class SoSimple
{
private:
	int num;
public:
	SoSimple(int n) : num(n) {}
	SoSimple& AddNum(int n)
	{
		num += n;
		return *this;
	}

	void Func() 
	{
		cout << "Func: " << num << endl;
	}

	void Func() const      // Func() 오버로딩
	{
		cout << "const Func: " << num << endl;
	}
};

void YourFunc(const SoSimple& obj)
{
	obj.Func();
}

int main()
{
	SoSimple obj1(2);
	const SoSimple obj2(7);

	obj1.Func();
	obj2.Func();

	YourFunc(obj1);
	YourFunc(obj2);

	return 0;
}


/*
  출력결과: Func: 2
            const Func: 7
            const Func: 2
            const Func: 7
*/

