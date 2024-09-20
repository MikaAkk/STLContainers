#include "pch.h"
#include "Utils.h"
#include "Menu.h"
#include <list>

#include "FKeys.h"

Menu::Menu(const COORD startPosition, const vector<MenuItem>& menuItems, Palette itemColor, Palette currentColor):
	startPosition_(startPosition),
	itemColor_(itemColor),
	currentColor_(currentColor),
    menuItems_(menuItems)  // ��� ���������� ���������� �����������
{
	// ��� ������ ��������� �������� ������ ����� ����
	menuItems_[0].selected(true);
} // Menu::Menu


// ���������
short Menu::itemColor() const { return itemColor_; }
void Menu::itemColor(short value) { itemColor_ = value; }

short Menu::currentColor() const { return currentColor_; }
void Menu::currentColor(short value) { currentColor_ = value; }

// ������ ������


// ���������� ������������ ����� ������ ������ ����
int Menu::getMaxLen()
{
	// �������� �������� �� ������ ������� ����, 
	// �������� ����� ������ ������� �������� ������ ������� ����
	size_t maxLen = menuItems_[0].text().length();

	// ������� �� ������� ������ � �������� ��������� 
	// �� ������ ������� ���� 
	for (size_t i = 1; i < menuItems_.size(); ++i) {
		const size_t lenItemText = menuItems_[i].text().length();
		if (lenItemText > maxLen) {
			maxLen = lenItemText;
		} // if
	} // for i

	return static_cast<int>(maxLen);
} // Menu::getMaxLen


// ����� ������� ����
void Menu::show() 
{
	// ������������ ����� ������ � ������ ����
	int maxLen = getMaxLen();
	cout << left;


	// ����� � �������� �������, ��� ������� ���������� ������,
	// � ����� ������� 4����������� ���� ����� � ����� ������
	size_t n = menuItems_.size();
	for (size_t i = 0; i < n; ++i) {
		cout<< pos(startPosition_.X, startPosition_.Y + (SHORT)i) 
			<< color(menuItems_[i].isSelected()?currentColor_:itemColor_)
			<< "    " << setw(maxLen)<< menuItems_[i].text() << "    ";
	} // for i 
	cout << right;

} // Menu::show


// ���������� ������ ���������� ������ ����
int Menu::findSelectedIndex()
{
	// ���������� ��� ������ ����
	int i = 0;
	for (auto item:menuItems_) {
		// ������� ������ ���������� ������ ����
		if (item.isSelected()) return i;
		++i;
	} // for i

	// ��� ���������� ������ ���
	return -1;
} // Menu::findSelectedIndex


// ��������� �� ������� ���� - ���������� ��� ��������� �������
int Menu::navigate()
{
	int cmd = -1;

	// ��������� ������
	cout << nocursor;

	// ���� ����� ����� ������, ����� - �� ENTER/RETURN ��� ESCAPE
	int i = findSelectedIndex();
	
	// ���������� ������� ����
	int n = menuItems_.size();

	while (true) {
		// ����� ������� ����
		show();
		

		// ������ ��� ������� �������
		short key = _getch();
		if (key == 0 || key == 224) key = _getch();

		// ����� �� ����� � ��������, ��������������� ������ ����
		if (key == VK_RETURN) {
			cmd = menuItems_[i].command();
			break;
		} // if

		// ����� �� ����� �� ����������� �������� - �����
		if (key == VK_ESCAPE || key == K_F10) {
			cmd = CMD_QUIT;
			break;
		} // if

		// ��������� ������ ���������� ��������
		switch (key) {
		// �� ������� ����
		case K_DOWN:
			// ������� ����� ���� ������ �� ���������
			menuItems_[i].selected(false);

			// ��������� � ���������� ������ ����
			i++;
			if (i >= n) i = 0;
			break;

		// �� ������� �����
		case K_UP:
			// ������� ����� ���� ������ �� ���������
			menuItems_[i].selected(false);

			// ��������� � ����������� ������ ����
			i--;
			if (i < 0) i = n - 1;
			break;

		case K_HOME:
			if (i != 0) {
				// ������� ����� ���� ������ �� ���������
				menuItems_[i].selected(false);

				i = 0;
			} // if
			break;

			case K_END:
			if (i != n - 1) {
				// ������� ����� ���� ������ �� ���������
				menuItems_[i].selected(false);

				i = n - 1;
			} // if
			break;
		} // switch

		// i-� ����� ���� ������ ���������
		menuItems_[i].selected(true);
	} // while

	// �������� ������, ������������ ����
	cout << cursor << color(mainColor);
	return cmd;
} // Menu::navigate
