// ����� �������� �������
#include "pch.h"
#include "Utils.h"
#include "Colors.h"
#include "Palette.h"

// ����������� ���������� - ��������-���������� ����������
// ���������� ����������, ��������� ������ � ������� �����
// ��������� ���� - ������������ ����������
// ����� ����� ���������� == ����� ����� (������) ���������
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void init(const wchar_t *title)
{
	SetConsoleTitle(title);
	SetConsoleOutputCP(CODE_PAGE);
	SetConsoleCP(CODE_PAGE);
	srand(GetTickCount());

	cout << fixed << setprecision(5) << boolalpha << color(mainColor) << cls;
} // init


// ��������� ���� ������� �������
int getKey(const string &message)
{
	cout << message;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	return key;
} // getKey


// ��������� ���������� ����� ���� int � ��������� [low, high]
int getRand(int low, int high)
{
	return low + rand() % (high - low + 1);
} // getRand


// ��������� ���������� ����� ���� float � ��������� [low, high]
float getRand(float low, float high)
{
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// ��������� ���������� ����� ���� double � ��������� [low, high]
double getRand(double low, double high)
{
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// ������� ����� �������
// ������������� ����������� ���������� h
void setColor(short color)
{
	SetConsoleTextAttribute(h, color);
} // setColor


// ���� ������ �����
int getInt()
{
	int value;
	while(true) {
		// ���������� ����
		cout << "? ";
		cin >> value;

		// ���� ����� �����, ����� �� ����� � �� �������
		if (!cin.fail()) break;

		// ���� ��� �� ����� - ����� ��������� ������,
		// ������� ������ �����
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	} // while

	return value;
} // getInt


// ����� ������� ������ ���� - ������ ��������� ��� ���������� �����
void showNavBarMessage(short hintColor, const string &message)
{
	setColor(hintColor);

	// ���������� � ���� ������ ������� (WinAPI)
	const COORD conSize = getConsoleSize();
	cout << setw(conSize.X) << left << message << right;
	setColor(mainColor);
} // showNavBarMessage


// ����� ��������� "������� � ����������"
void showUnderConstruction(short width, short mainColor, short infoColor)
{
	ostringstream oss;
	oss << "\n\n\n\n" << left
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    [����������]" << "\n"
		<< "\t" << setw(width) << "    ������� � ����������" << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    ������� ����� ������� ��� �����������..." << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << " " << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << right;
	showMessage(oss.str(), infoColor, mainColor);
} // showUnderConstruction


// ����� ���������
void showMessage(const string &msg, short msgColor, short mainColor)
{
	cout << color(msgColor) << left << msg << right << color(mainColor);
} // showMessage


// ����� ����������� �� �����, ������������� ������ �����, ���� �������������
// � �������� color
void showInputLine(const string &prompt, short n, short colorInput)
{
	// ������� ��������� �����
	// �������� ���� � ������� "������ �����"
	// ����������� ������ � ������ "������ �����"
	cout << prompt << color(colorInput) << setw(n) << "  " << setfill('\b') << setw(n-1) << '\b' << setfill(' ');
} // showInputLine


// ����� ����������� �� �����, ������������� ������ �����, ���� �������������
// � �������� color, ����� ���������� � �������� �������� �����������
void showInputLine(COORD start, const string &prompt, short n, short colorInput)
{
	// ������� ��������� �����
	// �������� ���� � ������� "������ �����"
	// ����������� ������ � ������ "������ �����"
	cout << pos(start.X, start.Y) << prompt << color(colorInput) << setw(n) << "  " << setfill('\b') << setw(n - 1) << '\b' << setfill(' ');
} // showInputLine


// �������� ������� �����
void checkInputFormat(istream& is)
{
	// �������� ������� �����
	if (is.fail()) {
		// ����� �������� ������ � ������� ������ �����
		is.clear();
		is.ignore(is.rdbuf()->in_avail(), '\n');

		// ������ ����������
		throw exception("������� �� �����");
	} // if	
} // checkInputFormat


// ---------------------------------------------------------------------------------
#pragma region ����������_��������_�_WinAPI
// ��������� ��� ���������� ������� �������
// mode: true  - �������� ������
//       false - ��������� ������
void showCursor(bool mode)
{
	// ��������� winAPI
	CONSOLE_CURSOR_INFO info;

	// ��������� ������ � ��� ���������, ������������ ���
	// ���� ���������� �������� & - �� ���� ��� ��� ���������
	// ������ ����������

	// h - ����� �������
	// info - ��������� �� ���������
	GetConsoleCursorInfo(h, &info);

	info.bVisible = mode;
	SetConsoleCursorInfo(h, &info);
} // void showCursor


// ���������� �������� ��������� ������� - true: ������� ��� false: �� �������
bool isCursor()
{
	CONSOLE_CURSOR_INFO info;

	// h - ����� �������
	// info - ��������� �� ���������
	GetConsoleCursorInfo(h, &info);

	return info.bVisible;
} // IsCursorVisible

// ���������������� ������� � �������� ������� �������
void gotoXY(short x, short y)
{
	SetConsoleCursorPosition(h, COORD{ x, y });
} // gotoXY

// �������� ������� ������� �������
void getXY(COORD* position)
{
	CONSOLE_SCREEN_BUFFER_INFO cbuf;
	GetConsoleScreenBufferInfo(h, &cbuf);

	position->X = cbuf.dwCursorPosition.X;
	position->Y = cbuf.dwCursorPosition.Y;
} // getXY


// ������� ������ �������
void cls()
{
	// �������� �������
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	// ������� ����� ���������� ����� � ������� ������.
	if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

	// ������ ���� ������� � ��������
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// ���������� �������� ������ ���� �������
	COORD homeCoord{ 0, 0 };

	// �������� ��������� ����� ��������� - ��� � ���� �������
	// cCharsWritten - ������� ���������� ��������
	DWORD cCharsWritten;
	if (!FillConsoleOutputCharacter(h, (TCHAR)' ', dwConSize, homeCoord, &cCharsWritten))
		return;

	// ��������� ��������������� �������� ������ �� ������� ���������.
	if (!FillConsoleOutputAttribute(h, csbi.wAttributes,
		dwConSize, homeCoord, &cCharsWritten))
		return;

	// �������� ������ � ��������� ������� ����� ������� ������ - ������� ����� ����
	SetConsoleCursorPosition(h, homeCoord);
} // cls


// ��������� ������� ������ �������
COORD getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	return csbi.dwSize;
} // getConsoleSize

#pragma endregion


#pragma region ���������� ������������� ������
// "�����������" ������ ��� ������� ������
ostream& cls(ostream& os)
{
	cls();
	return os;
}

// "�����������" ������ ��� ������ ������� ���������
ostream& tab(ostream& os)
{
	os << "\t";
	return os;
}


// "�����������" ������ ��� ��������� ���������� �������
ostream& cursor(ostream& os)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ������ - ������ ��� ����������� �����������
	// � ������� �������� ������
	return os;
} // cursor


// "�����������" ����� ��� ��������� ���������� �������
istream& cursor(istream& is)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ����� - ������ ��� ����������� �����������
	// � ������� �������� �����
	return is;
} // cursor


// "�����������" ������ ��� ���������� ���������� �������
ostream& nocursor(ostream& os)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ������ - ������ ��� ����������� �����������
	// � ������� �������� ������
	return os;
} // nocursor


// "�����������" ����� ��� ���������� ���������� �������
istream& nocursor(istream& is)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// ������� ������ ����� - ������ ��� ����������� �����������
	// � ������� �������� �����
	return is;
} // nocursor


// "�����������" ������ � ���������� ��� ������
// ��������� ���������� �������� �������� ������
ostream& operator<<(ostream& os, const endlm& obj)
{
	os << setfill('\n') << setw(obj.n_) << '\n' << setfill(' ');
	return os;
} // operator<<


// "�����������" ������ � ���������� ��� ��������� �����
ostream& operator<<(ostream& os, const color& obj)
{
	SetConsoleTextAttribute(h, obj.color_);
	return os;
} // operator<<


// "�����������" ����� � ���������� ��� ��������� �����
istream& operator>>(istream& is, const color& obj)
{
	SetConsoleTextAttribute(h, obj.color_);
	return is;
} // operator>>


// "�����������" ������ � ���������� ��� ��������� ������� � �������� ������� ������
ostream& operator<<(ostream& os, const pos& obj)
{
	SetConsoleCursorPosition(h, COORD{ obj.x_, obj.y_ });
	return os;
} // operator<<


// "�����������" ����� � ���������� ��� ��������� ������� � �������� ������� ������
istream& operator>>(istream& is, const pos& obj)
{
	SetConsoleCursorPosition(h, COORD{ obj.x_, obj.y_ });
	return is;
} // operator>>
#pragma endregion
