#pragma once
// ����� ����
class MenuItem
{
	// ��� �������
	int command_;

	// ����� ������ ����
	string text_;

	// ������� ���������� ������ ����
	bool selected_;

public:
	// ������������ � ����������
	MenuItem():MenuItem(1, "����� ������ ����") {}
	
	// MenuItem(int command, const char* text);
	MenuItem(int command, const string &text);

	MenuItem(const MenuItem& other)=default;

	~MenuItem() = default;

	// ���������� �������� ������������
	MenuItem& operator=(const MenuItem& other) = default;

	// ���������
    int command() const;
	const string &text() const;
	bool isSelected() const;
	void selected(bool value);
};

