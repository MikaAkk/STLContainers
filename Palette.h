#pragma once
#include "Colors.h"

// ������� ���������� - ������ �������������, ������ ������ ���� - ������ ���
enum Palette: int {
	mainColor = GRAY_ON_BLACK,     // �������� ���� ������
    infoColor = BLACK_ON_LTCYAN,   // ���� ������ �������������� ���������
    acctColor = RED_ON_WHITE,      // ���� �������� ������ � ������������� ������
    hintColor = BLACK_ON_WHITE,    // ���� ����������� ������ � ������������� ������ 
    sumColor  = BLUE_ON_WHITE,     // ���� ������ �������� 
    errColor  = WHITE_ON_RED,      // ���� ������ ��������� �� ������
    resColor  = LTCYAN_ON_BLACK,   // ����� ������� �����������
    arrColor  = LTCYAN_ON_BLACK, // ����� �������
    headerColor = WHITE_ON_BLACK // ����� ��������� �������

};