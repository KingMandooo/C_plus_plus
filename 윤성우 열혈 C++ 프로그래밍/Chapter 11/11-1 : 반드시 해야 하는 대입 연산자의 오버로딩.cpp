  🟢 객체간 대입연산의 비밀: 디폴트 대입 연산자
  
  - 정의하지 않으면 디폴트 복사 생성자가 삽입된다.
  - 디폴트 복사 생성자는 멤버 대 멤버의 복사(얕은 복사)를 진행한다.
  - 생성자 내에서 동적 할당을 한다면, 그리고 깊은 복사가 필요하다면 직접 정의해야 한다.
    
    
  - 정의하지 않으면 디폴트 대입 연산자가 삽입된다.
  - 디폴트 대입 연산자는 멤버 대 멤버의 복사(얕은 복사)를 진행한다.
  - 연산자 내에서 동적 할당을 한다면, 그리고 깊은 복사가 필요하다면 직접 정의해야 한다.
    
                           🎈🎈 디폴트 대입 연산자와 디폴트 복사 생성자는 유사하다.
                                하지만 당연히 차이는 존재한다. 바로 둘의 호출시점이 다르다는 것이다.

#include <iostream>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	Point(int x = 0, int y = 0) : xpos(x), ypos(y)    
	{
		cout << "생성자 호출" << endl;
	}
	void ShowPosition() const
	{
		cout << '[' << xpos << ", " << ypos << ']' << endl;
	}
	Point(Point& ref) : xpos(ref.xpos), ypos(ref.ypos)
	{
		cout << "복사생성자 호출" << endl;
	}
	Point& operator=(Point& ref)          // ✅ cout를 사용한줄을 빼면 디폴트 대입연산자는 이렇게 정의되어있다.
	{
		cout << "대입 연산자 호출" << endl;
		xpos = ref.xpos;
		ypos = ref.ypos;
		return *this;
	}
};                                      

int main()
{
	Point aa(3, 5);           // 🎈🎈 이미 생성 및 초기화가 진행된 객체는 두 객체간의 대입연산 시에는 대입 연산자가 호출된다.
	Point bb(1, 2);
	bb = aa;                  // 🎈🎈 여기서 대입연산자는 오버로딩된 대입연산자이다. 

  // Point cc = aa;         <-- 🎈🎈 이런식으로 되어있다면 여기서는 복사생성자를 호출한다.
                             //      왜냐하면 cc는 생성과 초기화가 진행되지 않았기 때문이다.
	aa.ShowPosition();
	bb.ShowPosition();
                                  // ✅ 	bb = aa;  우리는 이렇게 대입 연산이 가능한 것을보고 
	return 0;                       //     "어라? 동일한 자료형의 두 객체간에 대입연산이 허용되네!" 라고 생각하면 허수다.
}                                 //      이는 단순한 대입연산이 아닌, 대입 연산자를 오버로딩 한 함수의 호출이기 때문이다.
    
/*
  출력결과:   생성자 호출 
              생성자 호출
              대입 연산자 호출
              [3, 5]
              [3, 5]
*/

-----------------------------------------------------------------------------------
  
🟢 디폴트 대입 연산자의 문제점

  --> 이 부분에 대해서는 Chapter 05에서 이미 언급이 되었다.
      그리고 디폴트 대입 연산자도 이와 같은 문제를 야기할 가능성이 있다.
      이 말은 디폴트 대입 연산자도 깊은 복사를 할 수 있도록 정의를 해줘야한다는 것이다.
      
      
#include <iostream>
using namespace std;

class Person
{
private:
	char* name;
	int age;
public:
	Person(char* myname, int myage)
	{
		name = new char[strlen(myname) + 1];
		strcpy(name, myname);
		age = myage;
	}
	void ShowPersonInfo() const
	{
		cout << "이름: " << name << endl;
		cout << "나이: " << age <<  endl;
	}
	~Person()
	{
		delete[] name;
		cout << "called destructor!" << endl;
	}
};

int main()
{
	Person man1("Lee dong woo", 29);
	Person man2("Yoon ji yul", 22);
	man2 = man1;

	man1.ShowPersonInfo();
	man2.ShowPersonInfo();

	return 0;                              // 🎈🎈 출력결과를 보면 소멸자가 한 번 밖에 호출이 안된 것을 볼 수 있다.
}                                        //       이는 디폴트 대입 연산자가 얕은 복사로 통해 멤버 대 멤버의 복사를 했기 때문이다.
                                         //       즉, 각 객체의 포인터 멤버변수인 name이 같은 공간을 가리키는 상황이 발생하여
                                         //       "Yoon ji yul"를 가지고 있는 메모리가 누수가 발생하는 상황이 일어난다.
/*
  출력결과:   이름: Lee dong woo
              나이: 29
              이름: Lee dong woo
              나이: 29
              called destructor!     
*/


                  Person& operator=(Person& ref)           // ✅ 이를 해결하기 위해서 Person 클래스에 이 코드를 추가해줘야한다.
                  {
                    delete[] name;  // 본래 name이 가리키는 메모리 해제 
                    name = new char[strlen(ref.name) + 1]; // 새로운 알맞는 길이의 메모리 공간 할당
                    strcpy(name, ref.name);  // 메모리 공간에 문자열 복사
                    age = ref.age;
                    return *this;
                  }

-----------------------------------------------------------------------------------
  
🟢 상속 구조에서의 대입 연산자 호출

  --> 🎈🎈 유도 클래스의 대입 연산자에는 아무런 명시를 하지 않으면, 기초 클래스의 대입 연산자가 호출되지 않는다.

	
#include <iostream>
using namespace std;

class First
{
private:
	int num1, num2;
public:
	First(int n1 = 0, int n2 = 0) : num1(n1), num2(n2)
	{}
	void ShowData() { cout << num1 << ", " << num2 << endl; }

	First& operator=(const First& ref)
	{
		cout << "First& operator=()" << endl;
		num1 = ref.num1;
		num2 = ref.num2;
		return *this;
	}
};

class Second : public First
{
private:
	int num3, num4;
public:
	Second(int n1, int n2, int n3, int n4) : First(n1, n2), num3(n3), num4(n4)
	{}
	void ShowData()
	{
		First::ShowData();
		cout << num3 << ", " << num4 << endl;
	}
};

int main()
{
	Second ssrc(111, 222, 333, 444);
	Second scpy(0, 0, 0, 0);
	scpy = ssrc;                  // scpy.operator=(ssrc); <-- 여기서 Second 클래스의 디폴트 대입 연산자가 호출된다.
	scpy.ShowData();              //                           그리고 그 디폴트 대입 연산자가 기초 클래스의 대입 연산자까지 호출해준다.

	return 0;
}

                                          🎈🎈 유도 클래스의 디폴트 대입 연산자는 기초 클래스의 대입 연산자까지 호출한다는 사실을 알 수 있다.
/*                                             이거 잘 이해해야 한다.
  출력결과:     First& operator=()  
		111, 222
		333, 444
*/
------------------------------------------------
						  
#include <iostream>
using namespace std;

class First
{
private:
	int num1, num2;
public:
	First(int n1 = 0, int n2 = 0) : num1(n1), num2(n2)
	{}
	void ShowData() { cout << num1 << ", " << num2 << endl; }

	First& operator=(const First& ref)
	{
		cout << "First& operator=()" << endl;
		num1 = ref.num1;
		num2 = ref.num2;
		return *this;
	}
};

class Second : public First
{
private:
	int num3, num4;
public:
	Second(int n1, int n2, int n3, int n4) : First(n1, n2), num3(n3), num4(n4)
	{}
	void ShowData()
	{
		First::ShowData();
		cout << num3 << ", " << num4 << endl;
	}

	Second& operator=(const Second& ref)                // 🎈🎈 즉, 이렇게 유도 클래스의 대입 연산자를 정의해야 하는 경우에는 
	{                                                   //       기초 클래스의 대입 연산자를 명시적으로 호출해야 한다.
	
		First::operator=(ref);  // 👉👉기초 클래스 대입 연산자 명시적으로 호출.  만약 이게 없으면,
		cout << "Second& operator=()" << endl;                                // 당연히 Second 객체의 num1과 num2는 초기화 되지 않는다.
		num3 = ref.num3;
		num4 = ref.num4;
		return *this;
	}
};

int main()
{
	Second ssrc(111, 222, 333, 444);
	Second scpy(0, 0, 0, 0);
	scpy = ssrc;
	scpy.ShowData();

	return 0;
}

/*                                           
  출력결과:     First& operator=()  
		111, 222
		333, 444
*/

------------------------------------------------------------------------------------------------
	
🟢 이니셜라이저가 성능 향상에 도움을 준다고 했던 것을 기억하나요?
	
#include <iostream>
using namespace std;

class AAA
{
private:
	int num; 
public:
	AAA(int n = 0) : num(n)      // 🎈🎈 int num = n   -->   AAA의 생성자 호출
	{
		cout << "AAA(int n = 0)" << endl;
	}
	AAA(const AAA& ref) : num(ref.num)
	{
		cout << "AAA(const AAA& ref)" << endl;
	}
	AAA& operator=(const AAA& ref)
	{
		num = ref.num;
		cout << "operator=(const AAA& ref)" << endl;
		return *this;
	}
};

class BBB
{
private:
	AAA mem;
public:
	BBB(const AAA& ref) : mem(ref) {}   // 🎈🎈 AAA mem = ref  -->  AAA의 복사 생성자 호출
};

class CCC
{
private:
	AAA mem;                             // AAA는 이미 생성 및 초기화가 진행된 객체이므로 여기서의 '='은 대입 연산자를 호출한다.
public:
	CCC(const AAA& ref) { mem = ref; }   // 🎈🎈 AAA mem;      -->  AAA의 생성자 호출
};                                           //      mem = ref;    -->  AAA의 대입연산자 호출

int main()
{
	AAA obj1(12);
	cout << "********************" << endl;
	BBB obj2(obj1);
	cout << "********************" << endl;
	CCC obj3(obj1);

	return 0;        
}
                                          ✅ 이렇듯 위 코드에서 보았듯이 이니셜라이저를 이용해서 초기화를 진행하면,
                                              함수의 호출횟수를 줄일 수 있어서, 그리고 초기화의 과정을 단순화시킬 수 있어서
					      약간의 성능향상을 기대할 수 있다.
/*                                           
  출력결과:     AAA(int n = 0)
		********************
		AAA(const AAA& ref)
		********************
		AAA(int n = 0)
		operator=(const AAA& ref)
*/

------------------------------------------------------------------------------------------------
🟠 문제 11-1(1)

💙 내가 푼 방식 💙

#include <iostream>
#include <cstring>                          
using namespace std;

class Gun
{
private:
	int bullet;
public:
	Gun(int bnum) : bullet(bnum) {}
	int GetBullet() { return bullet; }  // 총알 가져오는 함수 추가
	void Shot()
	{
		cout << "BBang!" << endl;
		bullet--;
	}
};

class Police      
{
private:
	int handcuffs;
	Gun* pistol;
public:
	Police(int bnum, int bcuff) : handcuffs(bcuff)
	{
		if (bnum > 0)
			pistol = new Gun(bnum);
		else
			pistol = NULL;
	}
	Police(Police& copy)  // 복사 생성자
	{
		handcuffs = copy.handcuffs;
		pistol = new Gun(copy.pistol->GetBullet());
	}
	Police& operator=(Police& ref) // 대입 연산자
	{
		delete pistol;
		handcuffs = ref.handcuffs;
		pistol = new Gun(ref.pistol->GetBullet());
		return *this;
	}
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
	void Shot()
	{
		if (pistol == NULL)
			cout << "No Gun!!" << endl;
		else
			pistol->Shot();
	}
	~Police()
	{
		if (pistol != NULL)
			delete pistol;
	}
};

int main()
{
	Police pman1(5, 3);

	//Police pman2 = pman1;

	Police pman2(1, 2);
	pman2 = pman1;

	pman2.Shot();
	pman2.PutHandcuff();

	return 0;
}

----------------------------------------------------------
💙 답지 💙

#include <iostream>
#include <cstring>                          
using namespace std;

class Gun
{
private:
	int bullet;
public:
	Gun(int bnum) : bullet(bnum) {}
	Gun(Gun& copy) : bullet(copy.bullet)  // 내가 추가한 복사생성자 (호출되는지 확인용)
	{
		cout << "복사생성자    ㅇㅇ " << endl;
	}
	void Shot()
	{
		cout << "BBang!" << endl;
		bullet--;
	}
};

class Police
{
private:
	int handcuffs;
	Gun* pistol;
public:
	Police(int bnum, int bcuff) : handcuffs(bcuff)
	{
		if (bnum > 0)
			pistol = new Gun(bnum);
		else
			pistol = NULL;
	}
	Police(Police& copy)  // 복사 생성자
	{
		handcuffs = copy.handcuffs;
		pistol = new Gun(*(copy.pistol)); // Gun의 복사생성자 호출
	}

	// pistol = new Gun(*(copy.pistol)); 이게 무슨 뜻일까? 
	// 그니까 내가 궁금한건 왜 * 를 붙여주는 걸까?
	// copy.pistol은 pos1.pistol이고 pistol은 주소 값일테고,
	// 그렇다면 *(copy.pistol), *(pos1.pistol)은 뭐지?
	// copy.pistol(객체의 주소)이 가리키는 객체이겠다.
	// pistol에는 주소값이 저장 돼. Gun의 객체의 주소값이 저장 돼.
	// 이를 가리키는 표현은 *(copy.pistol) 이거야.
	// 그리고 Gun의 복사생성자에서 Gun& copy는 참조자이므로 값을 받아야 돼.
	// 따라서 포인터가 붙어야 돼.
	// int num = 3;
	// int& num2 = num;  이렇게 값을 받잖아. 참조자는.
	// 그렇다면 이제 이해할 수 있어.
	// pistol = new Gun(*(copy.pistol)); 은 pistol에 새로운 매모리를 참조하도록 함과 동시에
	// Gun 클래스의 복사생성자를 호출하는 거야. 그러면 Gun의 객체인 pistol의 멤버변수 bullet이
	// 복사가 되겠지.
	
	Police& operator=(Police& ref) // 대입 연산자
	{
		delete pistol;
		handcuffs = ref.handcuffs;
		pistol = new Gun(*(ref.pistol));  // Gun의 복사생성자 호출
		return *this;
	}
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
	void Shot()
	{
		if (pistol == NULL)
			cout << "No Gun!!" << endl;
		else
			pistol->Shot();
	}
	~Police()
	{
		if (pistol != NULL)
			delete pistol;
	}
};

int main()
{
	Police pman1(5, 3);
	Police pman2 = pman1;
	Police pman3(4, 7);
	pman3 = pman1;

	pman2.Shot();
	pman2.PutHandcuff();

	return 0;
}



🟠 문제 11-1(2)

#include <iostream>
#include <cstring>
using namespace std;

class Book
{
private:
	char* title;  // 책 제목
	char* isbn;   // 국제표준도서번호
	int price;    // 책의 정가
public:
	Book(char* title, char* isbn, int price) : price(price)
	{
		this->title = new char[strlen(title) + 1];
		strcpy(this->title, title);

		this->isbn = new char[strlen(isbn) + 1];
		strcpy(this->isbn, isbn);
	}
	Book(Book& copy) : price(copy.price)
	{
		title = new char[strlen(copy.title) + 1];
		strcpy(title, copy.title);

		isbn = new char[strlen(copy.isbn) + 1];
		strcpy(isbn, copy.isbn);
	}
	Book operator=(Book& ref)
	{
		delete[] title;
		delete[] isbn;
		title = new char[strlen(ref.title) + 1];
		strcpy(title, ref.title);

		isbn = new char[strlen(ref.isbn) + 1];
		strcpy(isbn, ref.isbn);

		price = ref.price;

		return *this;
	}
	void ShowBookInfo()
	{
		cout << "제목: " << title << endl;
		cout << "ISBN: " << isbn << endl;
		cout << "가격: " << price << endl;
	}
	~Book()
	{
		delete[] title;
		delete[] isbn;
	}
};

class EBook : public Book
{
private:
	char* DRMKey;  // 보완관련 키
public:
	EBook(char* title, char* isbn, int price, char* DRMKey) : Book(title, isbn, price)
	{
		this->DRMKey = new char[strlen(DRMKey) + 1];
		strcpy(this->DRMKey, DRMKey);
	}
	EBook(EBook& copy) : Book(copy)
	{
		DRMKey = new char[strlen(copy.DRMKey) + 1];
		strcpy(DRMKey, copy.DRMKey);
	}
	EBook operator=(EBook& ref)
	{
		Book::operator=(ref);
		delete[] DRMKey;
		DRMKey = new char[strlen(ref.DRMKey) + 1];
		strcpy(DRMKey, ref.DRMKey);

		return *this;
	}
	void ShowEBookInfo()
	{
		ShowBookInfo();
		cout << "인증키: " << DRMKey << endl;
	}
	~EBook()
	{
		delete[] DRMKey;
	}
};

int main()
{
	EBook ebook1("좋은 C++ ebook", "555-12345-890-1", 10000, "fdx9wi8kiw");
	//EBook ebook2 = ebook1;

	EBook ebook2("나폴레옹", "335-12345-890-1", 7000, "AA9cwi8sc5w");
	ebook2 = ebook1;  // ebook.operator=(ebook1);

	ebook2.ShowEBookInfo();

	return 0;
}
