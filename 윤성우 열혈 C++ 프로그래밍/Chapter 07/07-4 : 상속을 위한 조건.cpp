
π’ μμμ μν κΈ°λ³Έ μ‘°κ±΄μΈ IS-A κ΄κ³μ μ±λ¦½

  - λ¬΄μ  μ νκΈ° is a μ νκΈ°           - λΈνΈλΆ is a μ»΄ν¨ν°
  
  μ΄λ κ² μμκ΄κ³κ° μ±λ¦½νλ €λ©΄ κΈ°μ΄ ν΄λμ€μ μ λ ν΄λμ€κ°μ IS-A κ΄κ³κ° μ±λ¦½ν΄μΌ νλ€.
  
  λ§μ½ μμκ΄κ³λ‘ λ¬Άκ³ μ νλ λ ν΄λμ€κ° IS-A κ΄κ³λ‘ ννλμ§ μλλ€λ©΄, μ΄λ μ μ ν μμμ κ΄κ³κ° μλ νλ₯ μ΄ λ§€μ° λλ€.
  
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
		cout << "μμ²­ λ΄μ©μ κ³μ°ν©λλ€." << endl;
	}
};

class NoteBook : public Computer       // ππ λΈνΈλΆ is a μ»΄ν¨ν°
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
			cout << "μΆ©μ μ΄ νμν©λλ€." << endl;
			return;
		}
		cout << "μ΄λνλ©΄μ ";
		Calculate();
		UseBattery();
	}
	int GetBatteryInfo() { return Battery; }
};

class TabletNotebook : public NoteBook      // ππ νλΈλ¦Ώ λΈνΈλΆ is a λΈνΈλΆ
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
			cout << "μΆ©μ μ΄ νμν©λλ€." << endl;
			return;
		}
		if (strcmp(regstPenModel, penInfo) != 0)
		{
			cout << "λ±λ‘λ νμ΄ μλλλ€.";
			return;
		}
		cout << "νκΈ° λ΄μ©μ μ²λ¦¬ν©λλ€." << endl;
		UseBattery();
	}
};

int main()
{
	NoteBook nc("μ΄μμ’", 5);
	TabletNotebook tn("μ μμ", 5, "ISE-241-242");
	nc.MovingCal();
	tn.Write("ISE-241-242");
	
	return 0;
}

-------------------------------------------------------------------------------------
  
π’ Has-A κ΄κ³λ μμμ μ‘°κ±΄μ λμ§λ§ λ³΅ν© κ΄κ³λ‘ μ΄λ₯Ό λμ νλ κ²μ΄ μΌλ°μ μ΄λ€.
  
      ππ IS-A κ΄κ³ μΈμλ μμμ΄ νμ±λ λ§ν κ΄κ³λ λ°λ‘ 'μμ 'μ κ΄κ³μ΄λ€.
      
           νμ§λ§ "λ³΅ν© κ΄κ³λ‘ μ΄λ₯Ό λμ νλ κ²μ΄ μΌλ°μ μ΄λ€" λΌλ κ±Έ μ£ΌμκΉκ² μκ°ν΄μΌνλ€.
  
  
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

class Police : public Gun     // ππ κ²½μ°° has a 
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
}                                    β Q.μ μΌλ°μ μΈ μν©μμ μμ μμ κΈ°λ°μ μ½λλ³΄λ€ μλμ μ½λκ° μ’μ λͺ¨λΈμΌκΉ?

-------------------------------          A. μλνλ©΄ μμ μ½λλ μΆκ°μ μΈ μκ΅¬μ¬ν­μ λ°μνκΈ°κ° μ½μ§ μκΈ° λλ¬Έμ΄λ€. (μ± p.311 μ½κΈ°!!)
  
                                            - κΆμ΄μ μμ νμ§ μμ κ²½μ°°μ ννν΄μΌ νλ€.
#include <iostream>
#include <cstring>                          - κ²½μ°°μ΄ κΆμ΄κ³Ό μκ°λΏλ§ μλλΌ, μ κΈ°λ΄λ μμ ν΄μΌ νλ€.
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

class Police       // ππ μμ μ½λμ λ¬λ¦¬ Gun ν΄λμ€λ₯Ό μμνλ κ²μ΄ μλλΌ, μμ±μμμ Gun κ°μ²΄λ₯Ό μμ±ν΄μ μ΄λ₯Ό μ°Έμ‘°νκ³  μλ€.
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


                      ππ μμμ IS-A κ΄κ³μ ννμ λ§€μ° μ μ νλ€.
                            κ·Έλ¦¬κ³  κ²½μ°μ λ°λΌμλ HAS-A κ΄κ³μ ννμλ μ¬μ©λ  μ μμΌλ,
                            μ΄λ νλ‘κ·Έλ¨μ λ³κ²½μ λ§μ μ μ½μ κ°μ Έλ€ μ€ μ μλ€.
                              
                      ππ IS-Aλ HAS-A μ΄μΈμ κ΄κ³μμλ μμμ΄ νμ±λ λ§ν μν©μ΄ μλ€.
                              
-------------------------------------------------------------------------------------

π  λ¬Έμ  07-2(1)
                              
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
		cout << "λ©΄μ : " << area << endl;
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
	rec.ShowAreaInfo();   // λ©΄μ  12

	Square sqr(7);
	sqr.ShowAreaInfo();   // λ©΄μ  49

	return 0;
}



π  λ¬Έμ  07-2(2)
  
#include <iostream>
#include <cstring>
using namespace std;

class Book
{
private:
	char* title;  // μ± μ λͺ©
	char* isbn;   // κ΅­μ νμ€λμλ²νΈ
	int price;    // μ±μ μ κ°
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
		cout << "μ λͺ©: " << title << endl;
		cout << "ISBN: " << isbn << endl;
		cout << "κ°κ²©: " << price << endl;
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
	char* DRMKey;  // λ³΄μκ΄λ ¨ ν€
public:
	EBook(char* title, char* isbn, int price, char* DRMKey) : Book(title, isbn, price)
	{
		this->DRMKey = new char[strlen(DRMKey) + 1];
		strcpy(this->DRMKey, DRMKey);
	}
	void ShowEBookInfo()
	{
		ShowBookInfo();
		cout << "μΈμ¦ν€: " << DRMKey << endl;
	}
	~EBook()
	{
		delete[] DRMKey;
	}
};

int main()
{
	Book book("μ’μ C++", "555-12345-890-0", 20000);
	book.ShowBookInfo();
	cout << endl;

	EBook ebook("μ’μ C++ ebook", "555-12345-890-1", 10000, "fdx9wi8kiw");
	ebook.ShowEBookInfo();

	return 0;
}
  
