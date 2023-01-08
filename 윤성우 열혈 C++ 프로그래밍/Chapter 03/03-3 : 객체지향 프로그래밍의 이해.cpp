

    "객체지향 프로그래밍은 현실에 존재하는 사물과 대상, 그리고 그에 따른 행동을 있는 그대로 실체화시키는 형태의 프로그래밍이다."
      
      
      🎈🎈 객체를 이루는 것은 데이터와 기능이다.
      
      - 과일장수는 과일을 팝니다.
      - 과일장수는 사과 20개, 오렌지 10개를 보유하고 있습니다.
      - 과일장수의 과일판매 수익은 현재까지 50,000원입니다.
      
      첫 번째는 과일장수의 '행동(behavior)'을 의미한다.
      두 번째와 세 번째는 과일장수의 '상태(state)'를 의미한다.
      
      이처럼 객체는 하나 이상의 상태 정보(데이터)와 하나 이상의 행동(기능)으로 구성이된다.
      
      상태 정보 -> 변수   /   행동 -> 함수
      
      
      int SaleApples(int money)      // 사과 구매액이 함수의 인자로 전달
      {
        int num = money / APPLE_PRICE;      // 사과가 개당 1000원이라고 가정
        numOfApples -= num;          // 사과의 수가 줄어들고,
        myMoney += money;            // 판매 수익이 발생한다.
        return num;                  // 실제 구매가 발생한 사과의 수를 반환
      }
      
                   
🔷 과일장수를 표현한 class
  
class FruitSeller
{
private:
	int APPLE_PRICE;   // 사과의 가격
	int numOfApples;
	int myMoney;

public:
	void InitMembers(int price, int num, int money)
	{
		APPLE_PRICE = price;
		numOfApples = num;
		myMoney = money;
	}

	int SaleApples(int money)     // 판매한 사과의 개수를 반환
	{
		int num = money / APPLE_PRICE;    
		numOfApples -= num;       
		myMoney += money;           
		return num;                
	}

	void ShowSalesResult()
	{
		cout << "남은 사과: " << numOfApples << endl;
		cout << "판매 수익: " << myMoney << endl;
	}
};


🔷 나(me)를 표현한 class

class FruitBuyer
{
private:
	int myMoney;
	int numOfApples;

public:
	void InitMembers(int money)
	{
		myMoney = money;
		numOfApples = 0;
	}
  
	void BuyApples(FruitSeller& seller, int money)
	{
		numOfApples += seller.SaleApples(money);
		myMoney -= money;
	}
  
	void ShowBuyResult()
	{
		cout << "현재 잔액: " << myMoney << endl;
		cout << "사과 개수: " << numOfApples << endl;
	}
};


---------------------------------------------
                                                🎈🎈 두 객체가 대화를 한다고 생각해보기..!! (책 p.142 ~ 145 보기)
#include <iostream>
using namespace std;

class FruitSeller
{
private:
	int APPLE_PRICE;
	int numOfApples;
	int myMoney;

public:
	void InitMembers(int price, int num, int money)
	{
		APPLE_PRICE = price;
		numOfApples = num;
		myMoney = money;
	}

	int SaleApples(int money)      
	{
		int num = money / 1000;    
		numOfApples -= num;         
		myMoney += money;           
		return num;                  
	}

	void ShowSalesResult()
	{
		cout << "남은 사과: " << numOfApples << endl;
		cout << "판매 수익: " << myMoney << endl << endl;
	}
};

class FruitBuyer
{
private:
	int myMoney;
	int numOfApples;

public:
	void InitMembers(int money)
	{
		myMoney = money;
		numOfApples = 0;
	}
	void BuyApples(FruitSeller& seller, int money)
	{
		numOfApples += seller.SaleApples(money);
		myMoney -= money;
	}
	void ShowBuyResult()
	{
		cout << "현재 잔액: " << myMoney << endl;
		cout << "사과 개수: " << numOfApples << endl;
	}
};

int main()
{
	FruitSeller* seller = new FruitSeller;          // 이런 방식으로 역시 객체 생성 가능!
	seller->InitMembers(1000, 20, 0);

	FruitBuyer buyer;
	buyer.InitMembers(5000);
	buyer.BuyApples(*seller, 2000);

	cout << "과일 판매자의 현황" << endl;
	seller->ShowSalesResult();
	cout << "과일 구매자의 현황" << endl;
	buyer.ShowBuyResult();
	
	return 0;
}
