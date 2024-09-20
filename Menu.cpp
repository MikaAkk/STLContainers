#include "pch.h"
#include "Utils.h"
#include "Menu.h"
#include <list>

#include "FKeys.h"

Menu::Menu(const COORD startPosition, const vector<MenuItem>& menuItems, Palette itemColor, Palette currentColor):
	startPosition_(startPosition),
	itemColor_(itemColor),
	currentColor_(currentColor),
    menuItems_(menuItems)  // тут вызываются копирующий конструктор
{
	// при старте выбранным является первый пункт меню
	menuItems_[0].selected(true);
} // Menu::Menu


// аксессоры
short Menu::itemColor() const { return itemColor_; }
void Menu::itemColor(short value) { itemColor_ = value; }

short Menu::currentColor() const { return currentColor_; }
void Menu::currentColor(short value) { currentColor_ = value; }

// методы класса


// возвращает максимальную длину текста пункта меню
int Menu::getMaxLen()
{
	// получить итератор на список пунктов меню, 
	// получить длину текста первого элемента списка пунктов меню
	size_t maxLen = menuItems_[0].text().length();

	// переход ко второму пункту и движение итератора 
	// по списку пунктов меню 
	for (size_t i = 1; i < menuItems_.size(); ++i) {
		const size_t lenItemText = menuItems_[i].text().length();
		if (lenItemText > maxLen) {
			maxLen = lenItemText;
		} // if
	} // for i

	return static_cast<int>(maxLen);
} // Menu::getMaxLen


// вывод пунктов меню
void Menu::show() 
{
	// максимальная длина текста в пункте меню
	int maxLen = getMaxLen();
	cout << left;


	// вывод в заданные позиции, все элемены одмнаковой ширины,
	// а также выводим 4хпробельные поля перед и после текста
	size_t n = menuItems_.size();
	for (size_t i = 0; i < n; ++i) {
		cout<< pos(startPosition_.X, startPosition_.Y + (SHORT)i) 
			<< color(menuItems_[i].isSelected()?currentColor_:itemColor_)
			<< "    " << setw(maxLen)<< menuItems_[i].text() << "    ";
	} // for i 
	cout << right;

} // Menu::show


// возвращает индекс выбранного пункта меню
int Menu::findSelectedIndex()
{
	// перебираем все пункты меню
	int i = 0;
	for (auto item:menuItems_) {
		// вернуть индекс выбранного пункта меню
		if (item.isSelected()) return i;
		++i;
	} // for i

	// нет выбранного пункта мею
	return -1;
} // Menu::findSelectedIndex


// навигация по пунктам меню - возвращает код выбранной команды
int Menu::navigate()
{
	int cmd = -1;

	// выключить курсор
	cout << nocursor;

	// цикл ввода кодов клавиш, выход - по ENTER/RETURN или ESCAPE
	int i = findSelectedIndex();
	
	// количество пунктов меню
	int n = menuItems_.size();

	while (true) {
		// вывод пунктов меню
		show();
		

		// вводим код нажатой клавиши
		short key = _getch();
		if (key == 0 || key == 224) key = _getch();

		// выход из цикла с командой, соответствующей пункту меню
		if (key == VK_RETURN) {
			cmd = menuItems_[i].command();
			break;
		} // if

		// выход из цикла со стандартной командой - выход
		if (key == VK_ESCAPE || key == K_F10) {
			cmd = CMD_QUIT;
			break;
		} // if

		// отработка клавиш управления курсором
		switch (key) {
		// по стрелке вниз
		case K_DOWN:
			// текущий пункт меню делаем не выбранным
			menuItems_[i].selected(false);

			// переходим к следующему пункту меню
			i++;
			if (i >= n) i = 0;
			break;

		// по стрелке вверх
		case K_UP:
			// текущий пункт меню делаем не выбранным
			menuItems_[i].selected(false);

			// переходим к предыдущему пункту меню
			i--;
			if (i < 0) i = n - 1;
			break;

		case K_HOME:
			if (i != 0) {
				// текущий пункт меню делаем не выбранным
				menuItems_[i].selected(false);

				i = 0;
			} // if
			break;

			case K_END:
			if (i != n - 1) {
				// текущий пункт меню делаем не выбранным
				menuItems_[i].selected(false);

				i = n - 1;
			} // if
			break;
		} // switch

		// i-й пункт меню делаем выбранным
		menuItems_[i].selected(true);
	} // while

	// включить курсор, восстановить цвет
	cout << cursor << color(mainColor);
	return cmd;
} // Menu::navigate
