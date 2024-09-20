#pragma once
#include "pch.h"

/*
 * �������� � ������ �������� ��������: ��������������� ����� ��������, �������
 * � �������� ��������, ����������� ����� ��������, ����������� ����� ��������.
 * ���������� � ����� � ������ ������� � ������� �0�, � ������ ������ ��������
 * ������ ��� �����, ��� � �����, �������� � �42�, �42�, �32�.
 */
class Bus
{
	// ��������������� ����� ��������
	string regNum_; 

	// ������� � �������� ��������
	string fullName_;     

	// ����������� ����� ��������
	string orderedRoute_; 

	// ����������� ����� �������� (��� ��������� ���������� � ���������)
	string actualRoute_;  

	// ����� ��� ������ � ��������� �������������
	string buf_;

public:
	// ������� ����� � �������� �����
	static constexpr int N_REG_NUMBER = 14; // XX DDD X DDD
	static constexpr int N_FULL_NAME = 71;
	static constexpr int N_ROUTE = 8;    // ����� ���������� ��� ����� ����� ��������� 
	static constexpr int RECORD_SIZE = N_REG_NUMBER + N_FULL_NAME + (N_ROUTE << 1);     
	
	Bus():Bus("�� 111 � 180", "��������� �.�.", "42", "0") {}

	Bus(const string &regNum, const string& fullName, const string& orderedRoute, 
		const string& actualRoute)
	{
		this->regNum(regNum);
		this->fullName(fullName);
		this->orderedRoute(orderedRoute);
		this->actualRoute(actualRoute);
	} // Bus

	// ������� ���� �� ���������, �.�.����� ���� ����� ��� ������� �����������
	// Bus(const Bus& value) = default;
	// ~Bus() = default;

	// ���c�����
	const string& regNum() const;
	void regNum(const string& value);
	
	const string& fullName() const { return fullName_;  }
	void fullName(const string& value);
	
	const string& orderedRoute() const { return orderedRoute_;  }
	void orderedRoute(const string& value);
	
	const string& actualRoute() const { return actualRoute_;  }
	void actualRoute(const string& value);

	// ������������� ��������
	// Bus& operator=(const Bus& value) = default;
	friend ostream& operator<<(ostream& os, Bus& bus);

	// ������ � �������� �������
	void read(fstream& fs);
	void write(fstream& fs);

	// ����� � ��������� �������������
	const string& toString();
	const string& toTableRow(int row);

	// ����� ����� �������
	static ostream& header(ostream& os);

	// ����� ������� �������
	static ostream& footer(ostream& os);
}; 
