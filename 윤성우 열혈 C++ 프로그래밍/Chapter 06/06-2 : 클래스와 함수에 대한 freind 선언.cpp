
π’ ν΄λμ€μ friend μ μΈ

- A ν΄λμ€κ° B ν΄λμ€λ₯Ό λμμΌλ‘ friendλ₯Ό μ μΈμ νλ©΄, B ν΄λμ€λ A ν΄λμ€μ private λ©€λ²μ μ§μ  μ κ·Όμ΄ κ°λ₯νλ€.
  
- λ¨, A ν΄λμ€λ B ν΄λμ€μ private λ©€λ²μ μ§μ  μ κ·Όμ΄ κ°λ₯ νλ €λ©΄, B ν΄λμ€κ° A ν΄λμ€λ₯Ό λμμΌλ‘ friend μ μΈμ ν΄μ€μΌ νλ€.
  
  
class Boy
{
private:
	int height;
	friend class Girl;        // ππ Girl ν΄λμ€ λ΄μμλ Boy ν΄λμ€μ λͺ¨λ  private λ©€λ²μ μ§μ  μ κ·Όμ΄ κ°λ₯νλ€.
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
		cout << "His height: " << frn.height << endl;    // ππ Boyμ private λ©€λ²μΈ heightμ μ κ·Ό κ°λ₯
	}
};
            
                   
             ππ μ΄λ ΅κ² μκ°ν κ±° μμ΄. private λ©€λ²λ class λ΄μμλ§ μ κ·Όμ΄ κ°λ₯νμμ. friendλ₯Ό μ΄μ©νλ©΄
                   friendλ‘ μ μΈλ class λ΄λΆμμλ private λ©€λ²μ μ κ·Όμ΄ κ°λ₯νλλ‘ ν΄μ£Όλ κ²μ΄μ¬.
                     
------------------------------------------------------------------------------------------------------------------
                     
#include <iostream>
#include <cstring>
using namespace std;

class Girl;                   // Girlμ΄λΌλ μ΄λ¦μ΄ ν΄λμ€μ μ΄λ¦μμ μλ¦Ό

class Boy
{
private:
	int height;
	friend class Girl;             // ππ Girl ν΄λμ€μ λν friend μ μΈ   (Girl ν΄λμ€μ λ΄λΆμμ Boy ν΄λμ€μ private μ κ·Ό κ°λ₯)
public:
	Boy(int len) : height(len) {}

	void ShowYourFriendInfo(Girl& frn);
};

class Girl
{
private:
	char phNum[20];                      β  Q. μ friend class Girl; μ privateμ μ μΈλμκ³ , friend class Boy; μ publicμ μ μΈμ΄ λμμκΉ?
public:
	Girl(const char* num)                     A. νλ λ μ μΈμ ν΄λμ€ μ μΈλΆμ public, private, protected μμ­ λ± μ΄λμλ μμΉν  μ μμΌλ©°, 
	{                                            μμΉμ λ°λ₯Έ μ°¨μ΄λ μ ν μλ€.
		strcpy(phNum, num);          
	}                                     
 
	void ShowYourFriendInfo(Boy& frn);
	friend class Boy;                  // ππ Boy ν΄λμ€μ λν friend μ μΈ (Boy ν΄λμ€μ λ΄λΆμμ Girl ν΄λμ€μ private μ κ·Ό κ°λ₯)
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
  μΆλ ₯κ²°κ³Ό:   Her phone number: 010-1234-5678
              His height: 170
*/
      
------------------------------------------------------------------------------------------------------------------
  
π’ friend μ μΈμ μΈμ ?
  
  friend μ μΈμ κ°μ²΄μ§ν₯μ λλͺμ¬ μ€ νλμΈ 'μ λ³΄μλ'μ λ¬΄λλ¨λ¦¬λ λ¬Έλ²μ΄λ€.
  
  friend μ μΈμ μ§λμΉλ©΄ μμ£Ό μνν  μ μλ€. friend μ μΈμ νμν μν©μμ κ·Ήν μκ·Ήμ μΌλ‘ μ¬μ©ν΄μΌ νλ€.
  
  (μ± p.251 μ½μ΄λ΄λ λμμ§ μμ)
  
  
  λμ: http://www.tcpschool.com/cpp/cpp_encapsulation_friend
  
------------------------------------------------------------------------------------------------------------------
  
ππ μ½λ λΆμνκΈ°
  
#include <iostream>
#include <cstring>
using namespace std;

class Point;              // Pointκ° ν΄λμ€μ μ΄λ¦μμ μ μΈ

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
  
  // ππ PointOP ν΄λμ€μ PointAdd() ν¨μμμ Point ν΄λμ€μ private λ©€λ²λ³μμ μ κ·Όμ΄ κ°λ₯νλλ‘ ν¨.
  //      κ·ΈλκΉ μ½κ² μ€λͺν΄μ νμ¬ Point ν΄λμ€ λ΄λΆμ μ μΈλ friend ν¨μλ€μ Point ν΄λμ€μ private λ©€λ²λ³μμ μ κ·Όμ΄ κ°λ₯νλ€.
  //      (μ΄κ²λ κ³±μΉμ΄λ³΄λ©΄ λΉμ°νκ±°)
  
	friend Point PointOP::PointAdd(const Point&, const Point&);  
	friend Point PointOP::PointSub(const Point&, const Point&);
	friend void ShowPointPos(const Point&);                       // μ μ­ν¨μ ShowPointPos()μ λν΄ friend μ μΈ
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
  μΆλ ₯κ²°κ³Ό: x: 3, y: 6
            x: 1, y: 2
            Operation times: 2

*/
