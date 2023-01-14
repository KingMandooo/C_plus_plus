
🟢 클래스의 friend 선언

- A 클래스가 B 클래스를 대상으로 friend를 선언을 하면, B 클래스는 A 클래스의 private 멤버에 직접 접근이 가능하다.
  
- 단, A 클래스도 B 클래스의 private 멤버에 직접 접근이 가능 하려면, B 클래스가 A 클래스를 대상으로 friend 선언을 해줘야 한다.
  
  
class Boy
{
private:
	int height;
	friend class Girl;        // 🎈🎈 Girl 클래스 내에서는 Boy 클래스의 모든 private 멤버에 직접 접근이 가능하다.
public:
	Boy(int len) : height(len) {}
};

class Girl
{
private:
	char phNum[20];
public:
	Girl(char* num)
	{
		strcpy(phNum, num);
	}
	void ShowYourFriendInfo(Boy& frn)
	{
		cout << "His height: " << frn.height << endl;    // 🎈🎈 Boy의 private 멤버인 height에 접근 가능
	}
};
            
                   
             👉👉 어렵게 생각할거 없어. private 멤버는 class 내에서만 접근이 가능하잖아. friend를 이용하면
                   friend로 선언된 class 내부에서도 private 멤버에 접근이 가능하도록 해주는 것이여.
                     
------------------------------------------------------------------------------------------------------------------
                     
#include <iostream>
#include <cstring>
using namespace std;

class Girl;                   // Girl이라는 이름이 클래스의 이름임을 알림

class Boy
{
private:
	int height;
	friend class Girl;             // 🎈🎈 Girl 클래스에 대한 friend 선언   (Girl 클래스에 내부에서 Boy 클래스의 private 접근 가능)
public:
	Boy(int len) : height(len) {}

	void ShowYourFriendInfo(Girl& frn);
};

class Girl
{
private:
	char phNum[20];                      ✅  Q. 왜 friend class Girl; 은 private에 선언되었고, friend class Boy; 은 public에 선언이 되었을까?
public:
	Girl(const char* num)                     A. 프렌드 선언은 클래스 선언부의 public, private, protected 영역 등 어디에나 위치할 수 있으며, 
	{                                            위치에 따른 차이는 전혀 없다.
		strcpy(phNum, num);          
	}                                     
 
	void ShowYourFriendInfo(Boy& frn);
	friend class Boy;                  // 🎈🎈 Boy 클래스에 대한 friend 선언 (Boy 클래스에 내부에서 Girl 클래스의 private 접근 가능)
}; 
 
void Boy::ShowYourFriendInfo(Girl& frn)
{
	cout << "Her phone number: " << frn.phNum << endl;
}

void Girl::ShowYourFriendInfo(Boy& frn)
{
	cout << "His height: " << frn.height << endl;
}

int main()
{
	Boy boy(170);
	Girl girl("010-1234-5678");
	boy.ShowYourFriendInfo(girl);
	girl.ShowYourFriendInfo(boy);

	return 0;
}



/*
  출력결과:   Her phone number: 010-1234-5678
              His height: 170
*/
      
------------------------------------------------------------------------------------------------------------------
  
🟢 friend 선언은 언제?
  
  friend 선언은 객체지향의 대명사 중 하나인 '정보은닉'을 무너뜨리는 문법이다.
  
  friend 선언은 지나치면 아주 위험할 수 있다. friend 선언은 필요한 상황에서 극히 소극적으로 사용해야 한다.
  
  (책 p.251 읽어봐도 나쁘지 않음)
  
  
  도움: http://www.tcpschool.com/cpp/cpp_encapsulation_friend
  
------------------------------------------------------------------------------------------------------------------
  
👉👉 코드 분석하기
  
#include <iostream>
#include <cstring>
using namespace std;

class Point;              // Point가 클래스의 이름임을 선언

class PointOP
{
private:
	int opcnt;
public:
	PointOP() : opcnt(0) {}

	Point PointAdd(const Point&, const Point&);

	Point PointSub(const Point&, const Point&);

	~PointOP()
	{
		cout << "Operation times: " << opcnt << endl;
	}
};

class Point
{
private:
	int x;
	int y;
public:
	Point(const int& xpos, const int& ypos) : x(xpos), y(ypos)
	{}
  
  // 🎈🎈 PointOP 클래스의 PointAdd() 함수에서 Point 클래스의 private 멤버변수에 접근이 가능하도록 함.
  //      그니까 쉽게 설명해서 현재 Point 클래스 내부에 선언된 friend 함수들은 Point 클래스의 private 멤버변수에 접근이 가능하다.
  //      (이것도 곱씹어보면 당연한거)
  
	friend Point PointOP::PointAdd(const Point&, const Point&);  
	friend Point PointOP::PointSub(const Point&, const Point&);
	friend void ShowPointPos(const Point&);                       // 전역함수 ShowPointPos()에 대해 friend 선언
};

Point PointOP::PointAdd(const Point& pnt1, const Point& pnt2)
{
	opcnt++;
	return Point(pnt1.x + pnt2.x, pnt1.y + pnt2.y);
}

Point PointOP::PointSub(const Point& pnt1, const Point& pnt2)
{
	opcnt++;
	return Point(pnt1.x - pnt2.x, pnt1.y - pnt2.y);
}

int main()
{
	Point pos1(1, 2);
	Point pos2(2, 4);
	PointOP op;

	ShowPointPos(op.PointAdd(pos1, pos2));
	ShowPointPos(op.PointSub(pos2, pos1));

	return 0;
}

void ShowPointPos(const Point& pos)
{
	cout << "x: " << pos.x << ", ";
	cout << "y: " << pos.y << endl;
}




/*
  출력결과: x: 3, y: 6
            x: 1, y: 2
            Operation times: 2

*/
