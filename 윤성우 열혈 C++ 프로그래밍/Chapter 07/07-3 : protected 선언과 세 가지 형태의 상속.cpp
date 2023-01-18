

            private < protected < public
              
            이 개념은 다중상속을 할 때 필요한 개념이다.
              
----------------------------------------------------------------
 
🟢 protected로 선언된 멤버가 허용하는 접근의 범위              
              
#include <iostream>
using namespace std;

class Person
{
protected:            // protected 선언  <-- 🎈🎈 protected 멤버는 유도 클래스에서 접근이 가능하다. 
	int age;
	double height;
};

class Me : public Person
{
public:
	Me(int age, double height) 
	{
		this->age = age;             // Person::age     
		this->height = height; 
		cout << "My age is " << age << endl;
		cout << "I'm " << height << endl;
	}
};

int main()
{
	Me na(24, 180);
}

               
                      🎈🎈 protected 선언은 private와 public에 비해 그리 많이 사용되지 않는다. 
                           "기초 클래스와 이를 상속하는 유도 클래스 사이에서도 '정보은닉'은 지켜지는 게 좋다."
                        
                        
----------------------------------------------------------------
 
🟢 세가지 형태의 상속


class Base
{
private:            
	int num1;
protected:
	int num2;
public:
	int num3;
}; 


class Derived : protected Base    // protected 상속 
{
접근불가:            
	int num1;
protected:
	int num2;
protected:
	int num3;                        // 🎈🎈 "protected보다 접근의 범위가 넓은 멤버는 protected로 변경시켜서 상속하겠다."
};   

----------------------------

class Base
{
private:            
	int num1;
protected:
	int num2;
public:
	int num3;
}; 


class Derived : private Base      // private 상속
{
접근불가:            
	int num1;
private:
	int num2;
private:
	int num3;                        // 🎈🎈 "private 접근의 범위가 넓은 멤버는 private 변경시켜서 상속하겠다."
};   


class GOGOGOGO : private Derived      
{
접근불가:            
	int num1;                 // 🎈🎈 만약 Derived 클래스를 상속받는 또 다른 클래스는 변수 num2와 num3를 private 형으로 받기 때문에, 
접근불가:                         //       Base 클래스의 멤버변수들에게 전부 접근불가가 된다.
	int num2;
접근불가:
	int num3;                        
};  	   

----------------------------

class Base
{
private:            
	int num1;
protected:
	int num2;
public:
	int num3;
}; 


class Derived : public Base      // public 상속
{
접근불가:            
	int num1;
protected:
	int num2;
public:
	int num3;                        // 🎈🎈 "private을 제외한 나머지는 그냥 그대로 상속한다."
};   

------------------------------------------------------------------------------------

                   어느 교수님은 다음과 같이 학생들을 가르치기도 한다고 들었다.
	
	               "C++의 상속은 public 상속만 있다고 생각을 해라."


