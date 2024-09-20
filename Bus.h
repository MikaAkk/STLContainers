#pragma once
#include "pch.h"

/*
 * Сведения о каждом автобусе содержат: регистрационный номер автобуса, фамилию
 * и инициалы водителя, назначенный номер маршрута, фактический номер маршрута.
 * Нахождение в парке – особый маршрут с номером «0», в состав номера маршрута
 * входят как цифры, так и буквы, например – «42», «42а», «32в».
 */
class Bus
{
	// регистрационный номер автобуса
	string regNum_; 

	// фамилию и инициалы водителя
	string fullName_;     

	// назначенный номер маршрута
	string orderedRoute_; 

	// фактический номер маршрута (для индикации нахождения в автопарке)
	string actualRoute_;  

	// буфер для вывода в строковом представлении
	string buf_;

public:
	// размеры полей в бинарном файле
	static constexpr int N_REG_NUMBER = 14; // XX DDD X DDD
	static constexpr int N_FULL_NAME = 71;
	static constexpr int N_ROUTE = 8;    // длина одинаковая для обоих полей маршрутов 
	static constexpr int RECORD_SIZE = N_REG_NUMBER + N_FULL_NAME + (N_ROUTE << 1);     
	
	Bus():Bus("АА 111 А 180", "Терешкова В.С.", "42", "0") {}

	Bus(const string &regNum, const string& fullName, const string& orderedRoute, 
		const string& actualRoute)
	{
		this->regNum(regNum);
		this->fullName(fullName);
		this->orderedRoute(orderedRoute);
		this->actualRoute(actualRoute);
	} // Bus

	// правило трех не реализуем, т.к.типов всех полей это правило реализовано
	// Bus(const Bus& value) = default;
	// ~Bus() = default;

	// аксcесоры
	const string& regNum() const;
	void regNum(const string& value);
	
	const string& fullName() const { return fullName_;  }
	void fullName(const string& value);
	
	const string& orderedRoute() const { return orderedRoute_;  }
	void orderedRoute(const string& value);
	
	const string& actualRoute() const { return actualRoute_;  }
	void actualRoute(const string& value);

	// перегруженные операции
	// Bus& operator=(const Bus& value) = default;
	friend ostream& operator<<(ostream& os, Bus& bus);

	// работа с бинарным потоком
	void read(fstream& fs);
	void write(fstream& fs);

	// вывод в строковом представлении
	const string& toString();
	const string& toTableRow(int row);

	// вывод шапки таблицы
	static ostream& header(ostream& os);

	// вывод подвала таблицы
	static ostream& footer(ostream& os);
}; 
