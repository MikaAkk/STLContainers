#pragma once
#include "Palette.h"

// набор полезных функций

// ширина "панелей" вывода сообщений приложения
const int W = 84;

// процедура подготовки консоли к работе приложения
void init(const wchar_t *title = L"Заголовок приложения");

// получение кода нажатой клавиши
int getKey(const string &message = "\t    Нажмите любую клавишу для продолжения..."s);

// генерация случайного числа
int    getRand(int low, int high);
float  getRand(float low, float high);
double getRand(double low, double high);

// задание цвета консоли
void setColor(short color);

// ввод целого числа
int getInt();

// Функция для вывода верхней строки окна - строки навигации
void showNavBar(short acctColor, short hintColor);

// Функция для вывода верхней строки окна при решении задачи
void showNavBarMessage(short hintColor, const string &message);


// вывод сообщения "В разработке" 
void showUnderConstruction(short width, short mainColor, short infoColor);

// вывод произвольного текстового сообщения
void showMessage(const string &msg, short msgColor, short mainColor);

// вывод приглашения ко вводу, представления строки ввода, цвет переключается
// в заданный color
void showInputLine(const string &prompt = "Введите число:"s, short n = 19, short colorInput = infoColor);
void showInputLine(COORD start, const string &prompt = "Введите число:"s, short n = 19, short colorInput = infoColor);

// проверка на ошибку формата ввода
void checkInputFormat(istream& is);



#pragma region применение структур в WinAPI
// очистка экрана консоли
void cls();

// получение размера экрана консоли
COORD getConsoleSize();
void showCursor(bool mode);
bool isCursor();

void gotoXY(short x, short y);
void getXY(COORD* position);

#pragma endregion


#pragma region реализация манипуляторов вывода
// имитация манипулятора вывода без параметра

// "манипулятор" вывода для очистки экрана
ostream& cls(ostream& os);

// "манипулятор" вывода для вывода символа табуляции
ostream& tab(ostream& os);

// "манипулятор" вывода для включения текстового курсора
ostream& cursor(ostream& os);
istream& cursor(istream& os);

// "манипулятор" вывода для выключения текстового курсора
ostream& nocursor(ostream& os);
istream& nocursor(istream& os);

// "манипулятор" вывода с параметрами для вывода
// для вывода заданного количества символа перевода строки
// этот класс нужен только для хранения параметра манипулятора
class endlm
{
	// параметр манипулятора
	int n_;

public:
	endlm(int n) : n_(n) {}

	// очень важно -- константная ссылка на объект
	friend ostream& operator<<(ostream& os, const endlm& obj);
};

// задание цвета
class color
{
	// параметр манипулятора
	short color_;

public:
	color(short color) : color_(color) {}

	// очень важно -- константная ссылка на объект
	friend ostream& operator<<(ostream& os, const color& obj);
	friend istream& operator>>(istream& is, const color& obj);
};

// задание позиции курсора
class pos
{
	// параметр манипулятора
	short x_;
	short y_;

public:
	pos(short x, short y) : x_(x), y_(y) {}

	// очень важно -- константная ссылка на объект
	friend ostream& operator<<(ostream& os, const pos& obj);
	friend istream& operator>>(istream& os, const pos& obj);
};
#pragma endregion

// -----------------------------------------------
// проверка на равенство double значений
inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }

// проверка на равенство float значений
inline bool eq(float f1, float f2) { return fabs(f1 - f2) <= 1e-6; }


// -----------------------------------------------
// перемешивание массива по алгоритму "Тасование Фишера-Йетса"
// https://vscode.ru/prog-lessons/kak-peremeshat-massiv-ili-spisok.html
template <typename T> void shuffle(T* arr, int n) {
	// просматриваем массив с конца
	for (int i = n - 1; i >= 1; i--) {

		// определяем элемент, с которым меням элемент с индексом i
		int j = getRand(0, i);

		// меняем местами элементы массива при помощи алгоритма swap
		swap(arr[i], arr[j]);
	} // for i
} // shuffle
