#include <iostream>
#include <Windows.h>
#include <string>
using namespace std;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
int crypto(int i,int e,int n);
int decrypt(int i, int d, int n);
int calE(int f);
int GCD(int e, int f);
bool prime(int prime);
int calD(int e,int f);
int main()
{
	setlocale(LC_ALL, "rus");
	system("cls");
	//-------------Переменнмые-------------------
	bool lever = false;
	int p, q, n, f, e, d;
	string open_text;
	//-------------------------------------------
	while (lever == false)
	{
		cout << "Введите число p: ";
		cin >> p;
		lever = prime(p);
		if (lever == false)
		{
			cout << "Число не является простым!\n";
		}
	}
	lever = false;
	while (lever == false)
	{
		cout << "Введите число q: ";
		cin >> q;
		lever = prime(q);
		if (lever == false)
		{
			cout << "Число не является простым!\n";
		}
	}
	n = p * q;
	cout << "n= " << n << endl;
	f = (p - 1) * (q - 1);
	cout << "f(n)= " << f << endl;
	e = calE(f);
	d = calD(e, f);
	cout << "Открытый ключ { " << e << ", " << n << " }\n";
	cout << "Закрытый ключ { " << d << ", " << n << " }\n";
	cout << "Введите сообщение для шифрования: ";
	cin.ignore();
	getline(cin, open_text);
	char* enc_text = new char[open_text.length()];
	for (int i = 0; i < open_text.length(); i++)
	{
		enc_text[i] = crypto(open_text[i], e, n);
	}
	cout << "Зашифрованное сообщение: ";
	for (int i = 0; i < open_text.length(); i++)
	{
		cout << enc_text[i];
	}
	char* dec_text = new char[open_text.length()];
	for (int i = 0; i < open_text.length(); i++)
	{
		dec_text[i] = decrypt(enc_text[i], d, n);
	}
	cout << "\nРасшифрованное сообщение: ";
	for (int i = 0; i < open_text.length(); i++)
	{
		cout << dec_text[i];
	}
	delete[] dec_text;
	delete[] enc_text;
	system("pause");
	return 0;
}
bool prime(int prime)
{
	for (int i = 2; i <= sqrt(prime); i++)
	{
		if (prime % i == 0)
		{
			return false;
		}
	}
	return true;
}
int calE(int f)
{
	int e;
	for (e = 2; e < f; e++)
	{
		if (GCD(e, f) == 1)
		{
			return e;
		}
	}
	return -1;
}
int GCD(int e, int f)
{
	int temp;
	while (e > 0)
	{
		temp = e;
		e = f % e;
		f = temp;
	}
	return f;
}
int calD(int e, int f)
{
	int d,k=1;
	while (1)
	{
		k = k + f;
		if (k % e == 0)
		{
			d = (k / e);
			return d;
		}
	}
}
int crypto(int i, int e, int n)
{
	int result = 1;
	i = i-97;
	for (int j = 0; j < e; j++)
	{
		result = result * i;
		result = result % n;
	}
	return result;
}
int decrypt(int i, int d, int n)
{
	int result = 1;
	for (int j = 0; j < d; j++)
	{
		result = result * i;
		result = result % n;
	}
	return result+97;
}
