#include <iostream>
using namespace std;

class SinivelCap // 콧물 처치용 캡슐
{
public:
	void Take() const { cout << "콧물이 싹~ 납니다." << endl; }
};

class SneezeCap // 재채기 처지용 캡슐
{
public:
	void Take() const { cout << "재채기가 멎습니다." << endl; }
};

class SnuffleCap // 코막힘 처치용 캡슐
{
public:
	void Take() const { cout << "코가 뻥 뚫립니다." << endl; }
};

class ColdPatient
{
public:
	void TakeSinivelCap(const SinivelCap& cap) const { cap.Take(); }
	void TakeSneezeCap(const SneezeCap& cap) const { cap.Take(); }
	void TakeSnuffleCap(const SnuffleCap& cap) const { cap.Take(); }
};

int main()
{
	SinivelCap scap;   // 각각의 증상에 대한 객체 생성
	SneezeCap zcap;
	SnuffleCap ncap;

	ColdPatient sufferer;          // 환자 객체 생성
	sufferer.TakeSinivelCap(scap);   // 증상에 대해 하나씩 치료..
	sufferer.TakeSneezeCap(zcap);
	sufferer.TakeSnuffleCap(ncap);

	return 0;
}

                    위의 코드는 캡슐화가 무너진 대표적인 사례이다.
                    
                    "코감기는 항상 콧물, 재채기, 코막힘을 동반한다."
                      
                     제일 먼저 확인 가능한 문제점은 복용의 절차가 너무 복잡하다는데 있다.
                     코감기, 재채기, 코막힘 약을 각각 복용하고 있기 때문에 한꺼번에 이 모든 증상을 치료해야 할
                     '코감기 캡슐'을 제대로 구현했다고 할 수 없기 때문이다.
                      
                     캡슐화가 무너지면 클래스 상호관계가 복잡해지기 때문에 이는 프로그램 전체의 복잡도를 높이는 결과로 이어진다.
                      

-----------------------------------------------------

#include <iostream>
using namespace std;

class SinivelCap // 콧물 처치용 캡슐
{
public:
	void Take() const { cout << "콧물이 싹~ 납니다." << endl; }
};

class SneezeCap // 재채기 처지용 캡슐
{
public:
	void Take() const { cout << "재채기가 멎습니다." << endl; }
};

class SnuffleCap // 코막힘 처치용 캡슐
{
public:
	void Take() const { cout << "코가 뻥 뚫립니다." << endl; }
};

class CONTAC600
{
private:
	SinivelCap sin;
	SneezeCap sne;
	SnuffleCap snu;
	
public:
	void Take() const
	{
		sin.Take();
		sne.Take();
		snu.Take();
	}
};

class ColdPatient
{
public:
	void TakeCONTAC600(const CONTAC600& cap) const { cap.Take(); }
};

int main()
{
	CONTAC600 cap;
	ColdPatient sufferer;
	sufferer.TakeCONTAC600(cap); // 확실히 더 가독성이 좋긴함. 환자가 코감기 약을 복용했구나가 보임.

	return 0;
}
                                                🎈🎈 캡슐화를 한다고 해서 하나의 클래스로만 모든 것을 구성해야 하는 것은 아니다.
                                                     위의 코드처럼 다른 클래스를 활용해도 된다.
                                                     
                                                     "문제는 어떻게 구성을 하느냐가 아니고, 어떠한 내용으로 구성을 하느냐에 있다."
                                                  
                                             
                                                  
🟢 캡슐화의 범위를 결정하는 일은 쉽지 않다..!!  (책 p.165 ~ 166 보기)
                                                  
              // 캡슐화를 시키는 과정은 구현해야할 것의 특성과 기능을 확실히 파악하는 일이 우선이겠구나..
                                                  
     캡슐화는 어려운 개념이다. 왜냐하면 캡슐화의 범위를 결정하는 일이 쉽지 않기 때문이다.
     
                                                  
     💙 정보를 은닉시키기는 쉽다. 그러나 캡슐화는 어렵다.
         --> 경험 많은 객체지향 프로그래머를 구분하는 첫 번째 기준은 캡슐화이다.
             캡슐화는 일관되게 적용할 수 있는 단순한 개념이 아니고, 구현하는 프로그램의 성격과 특성에 따라서
             적용하는 범위가 달라지는, 흔히 하는 말로 정답이란 것이 딱히 없는 개념이기 때문이다.
                                                  
                                                  

        
       🎈🎈 캡슐화에는 정보은닉이 기본적으로 포함된다.
            캡슐화는 감싸는 개념이다. 이왕이면 멤버변수가 보이지 않게 정보를 은닉해서 감싸는 것이 좋다.
                                                  
----------------------------------------------------------------

🟠 문제 04-2
                                                  
#include <iostream>
#include <cMath>
using namespace std;

class Point
{
private:
	int xpos, ypos;
public:
	void Init(int x, int y)
	{
		xpos = x;
		ypos = y;
	}

	void ShowPointInfo() const
	{
		cout << "[" << xpos << ", " << ypos << "]" << endl;
	}
};

class Circle
{
private:
	Point point;
	int radius;
public:
	void Init(int x, int y, int r)
	{
		point.Init(x, y);
		radius = r;
	}

	void ShowCircleInfo() const
	{
		cout << "radius: " << radius << endl;
		point.ShowPointInfo();
	}
};

class Ring
{
private:
	Circle c1;
	Circle c2;
public:
	void Init(int x1, int y1, int r1, int x2, int y2, int r2)
	{
		c1.Init(x1, y1, r1);
		c2.Init(x2, y2, r2);
	}

	void ShowRingInfo() const
	{
		cout << "Innder Circle Info..." << endl;
		c1.ShowCircleInfo();

		cout << "Outter Circle Info..." << endl;
		c2.ShowCircleInfo();
	}
};

int main()
{
	Ring ring;
	ring.Init(1, 1, 4, 2, 2, 9);
	ring.ShowRingInfo();

	return 0;
}                                               
                                                  
