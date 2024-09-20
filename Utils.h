#pragma once
#include "Palette.h"

// ����� �������� �������

// ������ "�������" ������ ��������� ����������
const int W = 84;

// ��������� ���������� ������� � ������ ����������
void init(const wchar_t *title = L"��������� ����������");

// ��������� ���� ������� �������
int getKey(const string &message = "\t    ������� ����� ������� ��� �����������..."s);

// ��������� ���������� �����
int    getRand(int low, int high);
float  getRand(float low, float high);
double getRand(double low, double high);

// ������� ����� �������
void setColor(short color);

// ���� ������ �����
int getInt();

// ������� ��� ������ ������� ������ ���� - ������ ���������
void showNavBar(short acctColor, short hintColor);

// ������� ��� ������ ������� ������ ���� ��� ������� ������
void showNavBarMessage(short hintColor, const string &message);


// ����� ��������� "� ����������" 
void showUnderConstruction(short width, short mainColor, short infoColor);

// ����� ������������� ���������� ���������
void showMessage(const string &msg, short msgColor, short mainColor);

// ����� ����������� �� �����, ������������� ������ �����, ���� �������������
// � �������� color
void showInputLine(const string &prompt = "������� �����:"s, short n = 19, short colorInput = infoColor);
void showInputLine(COORD start, const string &prompt = "������� �����:"s, short n = 19, short colorInput = infoColor);

// �������� �� ������ ������� �����
void checkInputFormat(istream& is);



#pragma region ���������� �������� � WinAPI
// ������� ������ �������
void cls();

// ��������� ������� ������ �������
COORD getConsoleSize();
void showCursor(bool mode);
bool isCursor();

void gotoXY(short x, short y);
void getXY(COORD* position);

#pragma endregion


#pragma region ���������� ������������� ������
// �������� ������������ ������ ��� ���������

// "�����������" ������ ��� ������� ������
ostream& cls(ostream& os);

// "�����������" ������ ��� ������ ������� ���������
ostream& tab(ostream& os);

// "�����������" ������ ��� ��������� ���������� �������
ostream& cursor(ostream& os);
istream& cursor(istream& os);

// "�����������" ������ ��� ���������� ���������� �������
ostream& nocursor(ostream& os);
istream& nocursor(istream& os);

// "�����������" ������ � ����������� ��� ������
// ��� ������ ��������� ���������� ������� �������� ������
// ���� ����� ����� ������ ��� �������� ��������� ������������
class endlm
{
	// �������� ������������
	int n_;

public:
	endlm(int n) : n_(n) {}

	// ����� ����� -- ����������� ������ �� ������
	friend ostream& operator<<(ostream& os, const endlm& obj);
};

// ������� �����
class color
{
	// �������� ������������
	short color_;

public:
	color(short color) : color_(color) {}

	// ����� ����� -- ����������� ������ �� ������
	friend ostream& operator<<(ostream& os, const color& obj);
	friend istream& operator>>(istream& is, const color& obj);
};

// ������� ������� �������
class pos
{
	// �������� ������������
	short x_;
	short y_;

public:
	pos(short x, short y) : x_(x), y_(y) {}

	// ����� ����� -- ����������� ������ �� ������
	friend ostream& operator<<(ostream& os, const pos& obj);
	friend istream& operator>>(istream& os, const pos& obj);
};
#pragma endregion

// -----------------------------------------------
// �������� �� ��������� double ��������
inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }

// �������� �� ��������� float ��������
inline bool eq(float f1, float f2) { return fabs(f1 - f2) <= 1e-6; }


// -----------------------------------------------
// ������������� ������� �� ��������� "��������� ������-�����"
// https://vscode.ru/prog-lessons/kak-peremeshat-massiv-ili-spisok.html
template <typename T> void shuffle(T* arr, int n) {
	// ������������� ������ � �����
	for (int i = n - 1; i >= 1; i--) {

		// ���������� �������, � ������� ����� ������� � �������� i
		int j = getRand(0, i);

		// ������ ������� �������� ������� ��� ������ ��������� swap
		swap(arr[i], arr[j]);
	} // for i
} // shuffle
