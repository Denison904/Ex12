#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int const dm[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

struct date
{
	int dd;
	int mm;
	int yy;
	date(int d = 1, int m = 1, int y = 2017)
	{
		dd = d;
		mm = m;
		yy = y;
	}
	int vis(int y);
	bool verify(int dd, int mm, int yy);
	void print(void);
};

int vis(int y)
{
	if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) return 1;
	else return 0;
}

bool verify(int dd, int mm, int yy)
{
	if (yy <= 0) return false;
	if (mm < 1 || mm>12) return false;
	if (mm != 2 && (dd<1 || dd>dm[mm])) return false;
	if (mm == 2 && (dd<1 || dd>dm[2] + vis(yy))) return false;
	return true;
}

void date::print(void)
{
	if (dd < 10)
		cout << 0;
	else
		cout << dd / 10;
	cout << dd % 10 << '.';
	if (mm < 10)
		cout << 0;
	else
		cout << mm / 10;
	cout << mm % 10 << '.';
	if (yy < 1000)
		cout << 0;
	else
		cout << yy / 1000;
	int y = yy % 1000;
	if (y < 100)
		cout << 0;
	else
		cout << y / 100;
	y = y % 100;
	if (y < 10)
		cout << 0;
	else
		cout << y / 10;
	cout << y % 10;
}

struct Student
{
	int pkod;
	char* Fname;
	char* Sname;
	char* Tname;
	char* adress;
	date data;
	Student* next;
	Student(int p = NULL, char* F = NULL, char* S = NULL, char* T = NULL, char* ad = NULL, int d = 1, int m = 1, int y = 2017)
	{
		pkod = p;
		Fname = _strdup(F);
		Sname = _strdup(S);
		Tname = _strdup(T);
		adress = _strdup(ad);
		data = date(d, m, y);
		next = NULL;
	}
	Student* add(Student* first);
	void print(void);
	Student* poisk(int p, char* F, char* S, char* T, char* ad, int d, int m, int y);
};

struct Predmet
{
	int dkod;
	char* Nazvanie;
	int Semestr;
	Predmet* next;
	Predmet(int d = NULL, char* F1 = NULL, int Spec = NULL)
	{
		dkod = d;
		Nazvanie = _strdup(F1);
		Semestr = Spec;
		next = NULL;
	}
	Predmet* add(Predmet* first);
	void print(void);
	Predmet* poisk(int d, char* F1);
};

Predmet* Predmet::add(Predmet* first)
{
	Predmet* ptr, * prev;
	ptr = first;
	prev = NULL;
	while (ptr != NULL && (strcmp(Nazvanie, ptr->Nazvanie) > 0))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL)
	{
		this->next = first;
		first = this;
	}
	else
	{
		prev->next = this;
		this->next = ptr;
	}
	return first;
}

Student* Student::add(Student* first)
{
	Student* ptr, * prev;
	ptr = first;
	prev = NULL;
	while (ptr != NULL && (strcmp(Fname, ptr->Fname) > 0 || (strcmp(Fname, ptr->Fname) == 0 && strcmp(Sname, ptr->Sname) > 0 || strcmp(Fname, ptr->Fname) == 0 && strcmp(Sname, ptr->Sname) == 0 && strcmp(Tname, ptr->Tname) > 0)))
	{
		prev = ptr;
		ptr = ptr->next;
	}
	if (prev == NULL)
	{
		this->next = first;
		first = this;
	}
	else
	{
		prev->next = this;
		this->next = ptr;
	}
	return first;
}

Predmet* Predmet::poisk(int d, char* F1)
{
	Predmet* ptr = this;
	while (ptr)
	{
		if (strcmp(ptr->Nazvanie, F1) == 0)
			break;
		ptr = ptr->next;
	}
	return ptr;
}

Student* Student::poisk(int p, char* F, char* S, char* T, char* ad, int d, int m, int y)
{
	Student* ptr1 = this;
	while (ptr1)
	{
		if (strcmp(ptr1->Fname, F) == 0 && strcmp(ptr1->Sname, S) == 0 && strcmp(ptr1->Tname, T) == 0)
			break;
		ptr1 = ptr1->next;
	}
	return ptr1;
}

void Predmet::print(void)
{
	Predmet* ptr = this;
	cout << "Предмет :\n";
	while (ptr)
	{
		cout.width(5);
		cout.setf(ios::left);
		cout.width(5);
		cout << ptr->dkod;
		cout.width(30);
		cout << ptr->Nazvanie;
		cout.width(15);
		cout << "Семестр : ";
		cout.width(10);
		cout << ptr->Semestr << '\n';
		ptr = ptr->next;
	}
}

void Student::print(void)
{
	Student* ptr1 = this;
	cout << "Студенты :\n";
	while (ptr1)
	{
		cout.width(5);
		cout.setf(ios::left);
		cout.width(5);
		cout << ptr1->pkod;
		cout.width(15);
		cout << ptr1->Fname;
		cout.width(15);
		cout << ptr1->Sname;
		cout.width(15);
		cout << ptr1->Tname;
		cout.width(15);
		cout << "Группа : ";
		cout.width(40);
		cout << ptr1->adress;
		cout.width(10);
		cout << "Дата рождения : ";
		ptr1->data.print();
		cout << "\n";
		ptr1 = ptr1->next;
	}
}

struct Vedomost
{
	int pkod;
	int dkod;
	int marks;
	date data;
	Vedomost* next;
	Vedomost(int pk = 0, int dk = 0, int ma = 0, int d = 1, int m = 1, int y = 2017)
	{
		pkod = pk;
		dkod = dk;
		marks = ma;
		data = date(d, m, y);
		next = NULL;
	}
	Vedomost* add(Vedomost* first);
	void print(Student* P, Predmet* D);
};

void Vedomost::print(Student* P, Predmet* D)
{
	Vedomost* ptr = this;
	Student* ptr1 = P;
	Predmet* ptr2 = D;
	int h = 0, j = 0;
	cout << "\nВедомость : \n";
	cout.width(15);
	while (ptr)
	{
		h = 0;
		j = 0;
		cout.setf(ios::left);
		while (ptr1 != NULL && ptr->pkod != ptr1->pkod)
			ptr1 = ptr1->next;
		while (ptr2 != NULL && ptr->dkod != ptr2->dkod)
			ptr2 = ptr2->next;
		cout.width(13);
		if (ptr1 != NULL)
		{
			cout << "Студент : ";
			cout.width(13);
			cout << ptr1->Fname;
			cout.width(13);
			cout << ptr1->Sname;
			cout.width(13);
			cout << ptr1->Tname << "\n";
		}
		else
		{
			cout << "Такого студента нет !\n";
			h = 1;
			break;

		}


		if (ptr2 != NULL)
		{
			cout << "Предмет : ";
			cout << ptr2->Nazvanie;
			cout << "\n";
		}
		else
		{
			cout << "Такого предмета нет !\n";
			j = 1;
			break;
		}
		if ((h == 0) && (j == 0))
		{
			cout.width(13);
			cout << "Дата сдачи экзамена: ";
			ptr->data.print();
			cout << "\nОценка : ";
			cout << ptr->marks;
			cout << '\n';
			ptr = ptr->next;
		}
	}
}

int main()
{
	setlocale(LC_CTYPE, "russian");
	char F1[30], S2[10], T3[15], U[40];
	int d, m, y, k1, k2 = 0, n, q, a, b, l, o;
	bool T;
	date d1;
	fstream ff("input.txt");
	Predmet* first = NULL, * new_el, * tmp;
	Student* first1 = NULL, * new_el1, * tmp1;
	Vedomost* first2 = NULL;
	ff >> n;
	for (int i = 0; i < n; i++)
	{
		ff >> k1;
		if (k2 == k1) {
			cout << "Ошибка! Два разных предмета не могут иметь один код !\n";
			system("pause");
			exit(1);
		}
		ff >> F1 >> l;
		if (first == NULL)
		{
			first = new Predmet(k1, F1, l);
			k2 = k1;
		}
		else
		{
			tmp = first->poisk(k1, F1);
			if (tmp)
				tmp->Semestr;
			else
			{
				new_el = new Predmet(k1, F1, l);
				first = new_el->add(first);
			}
		}
	}
	n = 0;
	k1 = 0;
	first->print();
	ff >> n;
	for (int i = 0; i < n; i++)
	{
		ff >> k1;
		if (k2 == k1) {
			cout << "Ошибка! Два разных cтудента не могут иметь один код !\n";
			system("pause");
			exit(1);
		}
		ff >> F1 >> S2 >> T3 >> U >> d >> m >> y;
		T = verify(d, m, y);
		if (T);
		else
		{
			cout << "Ошибка в дате! Проверте файл !\n";
			system("pause");
			exit(1);
		}

		if (first1 == NULL)
		{
			first1 = new Student(k1, F1, S2, T3, U, d, m, y);
			k2 = k1;
		}
		else
		{
			tmp1 = first1->poisk(k1, F1, S2, T3, U, d, m, y);
			if (tmp1)
				tmp1->data;
			else
			{
				new_el1 = new Student(k1, F1, S2, T3, U, d, m, y);
				first1 = new_el1->add(first1);
			}
		}
	}
	first1->print();
	cout << "\n";
	int key = 0;
	while (key == 0)
	{
		cout << "Введите код студента и предмета : \n";
		cin >> q >> a;
		cout << "Введите оценку за предмет :\n";
		cin >> o;
		do
		{
			cout << "Введите дату сдачи предмета ( День, Месяц, Год ) :\n ";
			cin >> d >> m >> y;
			b = verify(d, m, y);
			if (b);
			else
				cout << "Дата введена неправильно\n";
		} while (!b);
		first2 = new Vedomost(q, a, o, d, m, y);
		first2->print(first1, first);
		cout << "\nХотете продолжить ? Да(1) или Нет(2)\n";
		cin >> b;
		if (b == 1) { key = 0; }
		else
		{
			key = 1;
			break;
		}
	}
	system("pause");
	return 0;
}

