

            private < protected < public
              
              
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
                        
                        
                        
                            
