#pragma once
#include "pch.h"
#include "MenuItem.h"
#include "Palette.h"
#include <vector>


// ���� - ������������ ����� � �������� ������� ����
class Menu
{
	// ������� ���������� ���� �� ������
	COORD startPosition_;
	
	// ���� ������ �� ���������� ������ ����
	short itemColor_;

	// ���� ������ ���������� ������ ����
	short currentColor_;

	// ������ ������� ���� 
	vector<MenuItem> menuItems_;

	// ���������� ������ ���������� ������ ����
	int findSelectedIndex();

	// ���������� ������������ ����� ������ ������ ����
	int getMaxLen();

public:

	// ������������ � ����������
	Menu() :startPosition_(), itemColor_(mainColor), currentColor_(infoColor), menuItems_() {}

	Menu(const COORD startPosition, const vector<MenuItem> &menuItems, Palette itemColor, Palette currentColor);

	// Menu(const Menu& other) = default;

	// ����������
	// ~Menu() = default;

	// �������� ������������
	// Menu& operator=(const Menu& other) = default;

	// ���������
	short itemColor() const;
	void itemColor(short value);

	short currentColor() const;
	void currentColor(short value);

	// ������ ������
	// ����� ������� ����
	void show();

	// ��������� �� ������� ���� - ���������� ��� ��������� �������
	int navigate();

	// ���� ����������� ������ 
	static const int CMD_QUIT = 1;
};

