#include "pch.h"
#include "Bus.h"

const string& Bus::regNum() const { return regNum_; }
void Bus::regNum(const string& value) 
{
	// формат номера может быть проверен регулярными выражениями
	if (value.empty()) {
		throw exception("Bus: регистрационный номер не задан");
	} // if
	
	regNum_ = value; 
} // Bus::regNum


void Bus::fullName(const string& value) 
{ 
	if (value.empty()) {
		throw exception("Bus: водитель не задан");
	} // if


	fullName_ = value; 
} // Bus::fullName


void Bus::orderedRoute(const string& value) { 
	if (value.empty()) {
		throw exception("Bus: не задан маршрут, на который назначен автобус");
	} // if

	orderedRoute_ = value; 
} // Bus::orderedRoute


void Bus::actualRoute(const string& value) 
{ 
	if (value.empty()) {
		throw exception("Bus: не задан маршрут, на который вышел автобус");
	} // if

	actualRoute_ = value; 
} // Bus::actualRoute


// вывод шапки таблицы
ostream& Bus::header(ostream& os)
{
	os  << "    +—————+——————————--—-+——————————————————————+—————————————+—————————————+\n"
		<< "    |  N  |  Рег. номер  |     Фамилия И.О.     | Назначенный | Фактический |\n"
		<< "    | п/п |   автобуса   |       водителя       |   маршрут   |   маршрут   |\n"
		<< "    +—————+———————————---+——————————————————————+—————————————+—————————————+\n";
	return os;
} // Bus::header

// вывод подвала таблицы 
ostream& Bus::footer(ostream& os)
{
	os << "    +—————+—————--—————-—+——————————————————————+—————————————+—————————————+\n";
	return os;
} // Bus::footer


// вывод в строковом представлении - свободный формат
const string& Bus::toString() 
{
	ostringstream oss;
	oss << "Bus {" << regNum_ << ", " << fullName_ << ", назначен на: \"" 
		<< orderedRoute_ << "\", фактически на \"" << actualRoute_ << "\"}";
	buf_ = oss.str();
	return buf_;
} // Bus::toString()


// вывод в строковом представлении - строка таблицы
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


// перегрузка операции вывода
ostream& operator<<(ostream& os, Bus& bus)
{
	os << bus.toString();
	return os;
} // operator<<


// чтение из бинарного файла
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

	// смотрим вперед на один байт для проверки достижения конца файла
	fs.peek();
	
	delete[] buf;
} // Bus::read


// запись в бинарный файл
void Bus::write(fstream& fs)
{
	// буФер для записи строк
	char* buf = new char[max(N_REG_NUMBER, max(N_FULL_NAME, N_ROUTE))] {};

	strncpy(buf, regNum_.c_str(), N_REG_NUMBER-1);
	fs.write(buf, N_REG_NUMBER);

	// чистим буфер для читабельного вывода в файл, а также из соображений безопасности
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
