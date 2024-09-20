#include "pch.h"
#include "Bus.h"

const string& Bus::regNum() const { return regNum_; }
void Bus::regNum(const string& value) 
{
	// ������ ������ ����� ���� �������� ����������� �����������
	if (value.empty()) {
		throw exception("Bus: ��������������� ����� �� �����");
	} // if
	
	regNum_ = value; 
} // Bus::regNum


void Bus::fullName(const string& value) 
{ 
	if (value.empty()) {
		throw exception("Bus: �������� �� �����");
	} // if


	fullName_ = value; 
} // Bus::fullName


void Bus::orderedRoute(const string& value) { 
	if (value.empty()) {
		throw exception("Bus: �� ����� �������, �� ������� �������� �������");
	} // if

	orderedRoute_ = value; 
} // Bus::orderedRoute


void Bus::actualRoute(const string& value) 
{ 
	if (value.empty()) {
		throw exception("Bus: �� ����� �������, �� ������� ����� �������");
	} // if

	actualRoute_ = value; 
} // Bus::actualRoute


// ����� ����� �������
ostream& Bus::header(ostream& os)
{
	os  << "    +�����+����������--�-+����������������������+�������������+�������������+\n"
		<< "    |  N  |  ���. �����  |     ������� �.�.     | ����������� | ����������� |\n"
		<< "    | �/� |   ��������   |       ��������       |   �������   |   �������   |\n"
		<< "    +�����+�����������---+����������������������+�������������+�������������+\n";
	return os;
} // Bus::header

// ����� ������� ������� 
ostream& Bus::footer(ostream& os)
{
	os << "    +�����+�����--�����-�+����������������������+�������������+�������������+\n";
	return os;
} // Bus::footer


// ����� � ��������� ������������� - ��������� ������
const string& Bus::toString() 
{
	ostringstream oss;
	oss << "Bus {" << regNum_ << ", " << fullName_ << ", �������� ��: \"" 
		<< orderedRoute_ << "\", ���������� �� \"" << actualRoute_ << "\"}";
	buf_ = oss.str();
	return buf_;
} // Bus::toString()


// ����� � ��������� ������������� - ������ �������
const string& Bus::toTableRow(int row)
{
	ostringstream oss;
	oss <<  "| " << setw(3) << row
		<< " | " << left << setw(9) << regNum_
		<< " | " << setw(20) << left << fullName_ << right
		<< " | " << setw(8) << orderedRoute_ << "   "
		<< " | " << setw(8) << actualRoute_ << "    |";
	buf_ = oss.str();
	return buf_;
} // Buf::toTableRow


// ���������� �������� ������
ostream& operator<<(ostream& os, Bus& bus)
{
	os << bus.toString();
	return os;
} // operator<<


// ������ �� ��������� �����
void Bus::read(fstream& fs)
{
	char* buf = new char[max(N_REG_NUMBER, max(N_FULL_NAME, N_ROUTE))] {};
	
	fs.read(buf, N_REG_NUMBER);
	regNum_ = buf;
	
	fs.read(buf, N_FULL_NAME);
	fullName_ = buf;
	
	fs.read(buf, N_ROUTE);
	orderedRoute_ = buf;
	
	fs.read(buf, N_ROUTE);
	actualRoute_ = buf;

	// ������� ������ �� ���� ���� ��� �������� ���������� ����� �����
	fs.peek();
	
	delete[] buf;
} // Bus::read


// ������ � �������� ����
void Bus::write(fstream& fs)
{
	// ����� ��� ������ �����
	char* buf = new char[max(N_REG_NUMBER, max(N_FULL_NAME, N_ROUTE))] {};

	strncpy(buf, regNum_.c_str(), N_REG_NUMBER-1);
	fs.write(buf, N_REG_NUMBER);

	// ������ ����� ��� ������������ ������ � ����, � ����� �� ����������� ������������
	memset(buf, 0, N_FULL_NAME);
	strncpy(buf, fullName_.c_str(), N_FULL_NAME - 1);
	fs.write(buf, N_FULL_NAME);

	memset(buf, 0, N_ROUTE);
	strncpy(buf, orderedRoute_.c_str(), N_ROUTE - 1);
	fs.write(buf, N_ROUTE);

	memset(buf, 0, N_ROUTE);
	strncpy(buf, actualRoute_.c_str(), N_ROUTE - 1);
	fs.write(buf, N_ROUTE);
	
	delete[] buf;
} //  Bus::write
