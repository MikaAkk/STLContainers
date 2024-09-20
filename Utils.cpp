// набор полезных функций
#include "pch.h"
#include "Utils.h"
#include "Colors.h"
#include "Palette.h"

// статическая переменная - локально-глобальная переменная
// глобальная переменная, доступная только в текущем файле
// исходного кода - инкапсуляция переменной
// время жизни переменной == время жизни (работы) программы
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void init(const wchar_t *title)
{
	SetConsoleTitle(title);
	SetConsoleOutputCP(CODE_PAGE);
	SetConsoleCP(CODE_PAGE);
	srand(GetTickCount());

	cout << fixed << setprecision(5) << boolalpha << color(mainColor) << cls;
} // init


// получение кода нажатой клавиши
int getKey(const string &message)
{
	cout << message;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	return key;
} // getKey


// генерация случайного числа типа int в диапазоне [low, high]
int getRand(int low, int high)
{
	return low + rand() % (high - low + 1);
} // getRand


// генерация случайного числа типа float в диапазоне [low, high]
float getRand(float low, float high)
{
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// генерация случайного числа типа double в диапазоне [low, high]
double getRand(double low, double high)
{
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// задание цвета консоли
// использование статической переменной h
void setColor(short color)
{
	SetConsoleTextAttribute(h, color);
} // setColor


// ввод целого числа
int getInt()
{
	int value;
	while(true) {
		// собственно ввод
		cout << "? ";
		cin >> value;

		// Если ввели число, выход из цикла и из функции
		if (!cin.fail()) break;

		// Если это не число - сброс состояния ошибки,
		// очистка буфера ввода
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	} // while

	return value;
} // getInt


// вывод верхней строки окна - строки навигации при исполнении задач
void showNavBarMessage(short hintColor, const string &message)
{
	setColor(hintColor);

	// определить в коде ширину консоли (WinAPI)
	const COORD conSize = getConsoleSize();
	cout << setw(conSize.X) << left << message << right;
	setColor(mainColor);
} // showNavBarMessage


// Вывод сообщения "Функция в разработке"
void showUnderConstruction(short width, short mainColor, short infoColor)
{
	ostringstream oss;
	oss << "\n\n\n\n" << left
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    [Информация]" << "\n"
		<< "\t" << setw(width) << "    Функция в разработке" << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    Нажмите любую клавишу для продолжения..." << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << " " << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << right;
	showMessage(oss.str(), infoColor, mainColor);
} // showUnderConstruction


// вывод сообщения
void showMessage(const string &msg, short msgColor, short mainColor)
{
	cout << color(msgColor) << left << msg << right << color(mainColor);
} // showMessage


// вывод приглашения ко вводу, представления строки ввода, цвет переключается
// в заданный color
void showInputLine(const string &prompt, short n, short colorInput)
{
	// вывести подсказку ввода
	// включить цвет и вывести "строку ввода"
	// переместить курсор в начало "строки ввода"
	cout << prompt << color(colorInput) << setw(n) << "  " << setfill('\b') << setw(n-1) << '\b' << setfill(' ');
} // showInputLine


// вывод приглашения ко вводу, представления строки ввода, цвет переключается
// в заданный color, вывод начинается в заданных экранных координатах
void showInputLine(COORD start, const string &prompt, short n, short colorInput)
{
	// вывести подсказку ввода
	// включить цвет и вывести "строку ввода"
	// переместить курсор в начало "строки ввода"
	cout << pos(start.X, start.Y) << prompt << color(colorInput) << setw(n) << "  " << setfill('\b') << setw(n - 1) << '\b' << setfill(' ');
} // showInputLine


// проверка формата ввода
void checkInputFormat(istream& is)
{
	// проверка формата ввода
	if (is.fail()) {
		// сброс признака ошибки и очистка буфера ввода
		is.clear();
		is.ignore(is.rdbuf()->in_avail(), '\n');

		// выброс исключения
		throw exception("Введено не число");
	} // if	
} // checkInputFormat


// ---------------------------------------------------------------------------------
#pragma region применение_структур_в_WinAPI
// включение или выключение курсора консоли
// mode: true  - включить курсор
//       false - выключить курсор
void showCursor(bool mode)
{
	// структура winAPI
	CONSOLE_CURSOR_INFO info;

	// получение данных в эту структуру, используется еще
	// одна перегрузка операции & - на этот раз это получение
	// адреса переменной

	// h - хэндл консоли
	// info - указатель на структуру
	GetConsoleCursorInfo(h, &info);

	info.bVisible = mode;
	SetConsoleCursorInfo(h, &info);
} // void showCursor


// возвращает значение видимости курсора - true: видимый или false: не видимый
bool isCursor()
{
	CONSOLE_CURSOR_INFO info;

	// h - хэндл консоли
	// info - указатель на структуру
	GetConsoleCursorInfo(h, &info);

	return info.bVisible;
} // IsCursorVisible

// позиционирование курсора в заданную позицию консоли
void gotoXY(short x, short y)
{
	SetConsoleCursorPosition(h, COORD{ x, y });
} // gotoXY

// получить текущую позицию курсора
void getXY(COORD* position)
{
	CONSOLE_SCREEN_BUFFER_INFO cbuf;
	GetConsoleScreenBufferInfo(h, &cbuf);

	position->X = cbuf.dwCursorPosition.X;
	position->Y = cbuf.dwCursorPosition.Y;
} // getXY


// очистка экрана консоли
void cls()
{
	// свойства консоли
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	// Получим число символьных ячеек в текущем буфере.
	if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

	// размер окна консоли в символах
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// координаты верхнего левого угла консоли
	COORD homeCoord{ 0, 0 };

	// Заполним полностью экран пробелами - это и есть очистка
	// cCharsWritten - счетчик записанных символов
	DWORD cCharsWritten;
	if (!FillConsoleOutputCharacter(h, (TCHAR)' ', dwConSize, homeCoord, &cCharsWritten))
		return;

	// Установим соответствующие атрибуты буфера из текущих атрибутов.
	if (!FillConsoleOutputAttribute(h, csbi.wAttributes,
		dwConSize, homeCoord, &cCharsWritten))
		return;

	// Поместим курсор в начальную позицию после очистки экрана - верхний левый угол
	SetConsoleCursorPosition(h, homeCoord);
} // cls


// получение размера экрана консоли
COORD getConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	return csbi.dwSize;
} // getConsoleSize

#pragma endregion


#pragma region реализация манипуляторов вывода
// "манипулятор" вывода для очистки экрана
ostream& cls(ostream& os)
{
	cls();
	return os;
}

// "манипулятор" вывода для вывода символа табуляции
ostream& tab(ostream& os)
{
	os << "\t";
	return os;
}


// "манипулятор" вывода для включения текстового курсора
ostream& cursor(ostream& os)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// возврат потока вывода - только для возможности встраивания
	// в цепочку операций вывода
	return os;
} // cursor


// "манипулятор" ввода для включения текстового курсора
istream& cursor(istream& is)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// возврат потока ввода - только для возможности встраивания
	// в цепочку операций ввода
	return is;
} // cursor


// "манипулятор" вывода для выключения текстового курсора
ostream& nocursor(ostream& os)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// возврат потока вывода - только для возможности встраивания
	// в цепочку операций вывода
	return os;
} // nocursor


// "манипулятор" ввода для выключения текстового курсора
istream& nocursor(istream& is)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// возврат потока ввода - только для возможности встраивания
	// в цепочку операций ввода
	return is;
} // nocursor


// "манипулятор" вывода с параметром для вывода
// заданного количества символов перевода строки
ostream& operator<<(ostream& os, const endlm& obj)
{
	os << setfill('\n') << setw(obj.n_) << '\n' << setfill(' ');
	return os;
} // operator<<


// "манипулятор" вывода с параметром для установки цвета
ostream& operator<<(ostream& os, const color& obj)
{
	SetConsoleTextAttribute(h, obj.color_);
	return os;
} // operator<<


// "манипулятор" ввода с параметром для установки цвета
istream& operator>>(istream& is, const color& obj)
{
	SetConsoleTextAttribute(h, obj.color_);
	return is;
} // operator>>


// "манипулятор" вывода с параметром для установки курсора в заданную позицию экрана
ostream& operator<<(ostream& os, const pos& obj)
{
	SetConsoleCursorPosition(h, COORD{ obj.x_, obj.y_ });
	return os;
} // operator<<


// "манипулятор" ввода с параметром для установки курсора в заданную позицию экрана
istream& operator>>(istream& is, const pos& obj)
{
	SetConsoleCursorPosition(h, COORD{ obj.x_, obj.y_ });
	return is;
} // operator>>
#pragma endregion
