
🟢 상속을 위한 기본 조건인 IS-A 관계의 성립

  - 무선 전화기 is a 전화기           - 노트북 is a 컴퓨터
  
  이렇게 상속관계가 성립하려면 기초 클래스와 유도 클래스간에 IS-A 관계가 성립해야 한다.
  
  만약 상속관계로 묶고자 하는 두 클래스가 IS-A 관계로 표현되지 않는다면, 이는 적절한 상속의 관계가 아닐 확률이 매우 높다.
  
--------------------------------------
  
#include <iostream>
#include <cstring>
using namespace std;

class Computer
{
private:
	char owner[50];
public:
	Computer(char* name)
	{
		strcpy(owner, name);
	}
	void Calculate()
	{
		cout << "요청 내용을 계산합니다." << endl;
	}
};

class NoteBook : public Computer       // 🎈🎈 노트북 is a 컴퓨터
{
private:
	int Battery;
public:
	NoteBook(char* name, int initChag) : Computer(name), Battery(initChag)
	{}
	void Charging() { Battery += 5; }
	void UseBattery() { Battery -= 1; }
	void MovingCal()
	{
		if (GetBatteryInfo() < 1)
		{
			cout << "충전이 필요합니다." << endl;
			return;
		}
		cout << "이동하면서 ";
		Calculate();
		UseBattery();
	}
	int GetBatteryInfo() { return Battery; }
};

class TabletNotebook : public NoteBook      // 🎈🎈 태블릿 노트북 is a 노트북
{
private:
	char regstPenModel[50];
public:
	TabletNotebook(char* name, int initChag, char* pen) : NoteBook(name, initChag)
	{
		strcpy(regstPenModel, pen);
	}
	void Write(char* penInfo)
	{
		if (GetBatteryInfo() < 1)
		{
			cout << "충전이 필요합니다." << endl;
			return;
		}
		if (strcmp(regstPenModel, penInfo) != 0)
		{
			cout << "등록된 펜이 아닙니다.";
			return;
		}
		cout << "필기 내용을 처리합니다." << endl;
		UseBattery();
	}
};

int main()
{
	NoteBook nc("이수종", 5);
	TabletNotebook tn("정수영", 5, "ISE-241-242");
	nc.MovingCal();
	tn.Write("ISE-241-242");
	
	return 0;
}

-------------------------------------------------------------------------------------
  
🟢 Has-A 관계도 상속의 조건은 되지만 복합 관계로 이를 대신하는 것이 일반적이다.
  
      🎈🎈 IS-A 관계 외에도 상속이 형성될만한 관계는 바로 '소유'의 관계이다.
      
           하지만 "복합 관계로 이를 대신하는 것이 일반적이다" 라는 걸 주의깊게 생각해야한다.
  
  
#include <iostream>
#include <cstring>
using namespace std;

class Gun
{
private:
	int bullet;
public:
	Gun(int bnum) : bullet(bnum) {}
	void Shot()
	{
		cout << "BBang!" << endl;
		bullet--;
	}
};

class Police : public Gun     // 🎈🎈 경찰 has a 
{
private:
	int handcuffs;
public:
	Police(int bnum, int bcuff) : Gun(bnum), handcuffs(bcuff)
	{}
	void PutHandcuff()
	{
		cout << "SNAP!" << endl;
		handcuffs--;
	}
};

int main()
{
	Police pman(5, 3);
	pman.Shot();
	pman.PutHandcuff();

	return 0;
}                                    ✅ Q.왜 일반적인 상황에서 위의 상속 기반의 코드보다 아래의 코드가 좋은 모델일까?

-------------------------------          A. 왜냐하면 위의 코드는 추가적인 요구사항을 반영하기가 쉽지 않기 때문이다. (책 p.311 읽기!!)
  
                                            - 권총을 소유하지 않은 경찰을 표현해야 한다.
#include <iostream>
#include <cstring>                          - 경찰이 권총과 수갑뿐만 아니라, 전기봉도 소유해야 한다.
using namespace std;

class Gun
{
private:
	int bullet;
public:
	Gun(int bnum) : bullet(bnum) {}
	void Shot()
	{
		cout << "BBang!" << endl;
		bullet--;
	}
};

class Police       // 🎈🎈 위의 코드와 달리 Gun 클래스를 상속하는 것이 아니라, 생성자에서 Gun 객체를 생성해서 이를 참조하고 있다.
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
	pman1.Shot();
	pman1.PutHandcuff();

	Police pman2(0, 3);
	pman2.Shot();
	pman2.PutHandcuff();

	return 0;
}


                      👊👊 상속은 IS-A 관계의 표현에 매우 적절하다.
                            그리고 경우에 따라서는 HAS-A 관계의 표현에도 사용될 수 있으나,
                            이는 프로그램의 변경에 많은 제약을 가져다 줄 수 있다.
                              
                      🎈🎈 IS-A랑 HAS-A 이외의 관계에서도 상속이 형성될만한 상황이 없다.
                              
-------------------------------------------------------------------------------------

🟠 문제 07-2(1)
                              
#include <iostream>
using namespace std;

class Rectangle
{
private:
	int width;
	int height;
	int area;
public:
	Rectangle(int width, int height) : width(width), height(height)
	{
		area = width * height;
	}
	void ShowAreaInfo()
	{
		cout << "면적: " << area << endl;
	}
};

class Square : public Rectangle
{
public:
	Square(int side) : Rectangle(side, side)
	{}
};

int main()
{
	Rectangle rec(4, 3);
	rec.ShowAreaInfo();   // 면적 12

	Square sqr(7);
	sqr.ShowAreaInfo();   // 면적 49

	return 0;
}



🟠 문제 07-2(2)
  
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
	Book book("좋은 C++", "555-12345-890-0", 20000);
	book.ShowBookInfo();
	cout << endl;

	EBook ebook("좋은 C++ ebook", "555-12345-890-1", 10000, "fdx9wi8kiw");
	ebook.ShowEBookInfo();

	return 0;
}
  
