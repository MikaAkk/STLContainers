#pragma once
#include "pch.h"
#include <map>
#include "Bus.h"


// Моделирование автобусного парка
class App
{
	// коллекция автобусов
	//  рег. номер --> автобус
	map<string, Bus> total_;
	
    // коллекция автобусов в автопарке
	//  рег. номер --> автобус
	map<string, Bus> busStation_;
	
	// коллекция автобусов на маршруте
	//  рег. номер --> автобус
	map<string, Bus> route_;

	// имя файла для коллекции автобусов
	string fileName_;

	void showBuses(const map<string, Bus>& buses, const string& title);

	// для вывода автобусов, упорядоченных по номерам маршрутов
	void showBuses(const multimap<string, Bus>& buses, const string& title);
	void putToMaps();

	// формирование multimap для сортировки по номеру маршрута
	// номер маршрута --> Bus
	multimap<string, Bus> makeMultiMap(const map<string, Bus> &buses);

	// загрузка коллекции автобусов из потока
	void loadFromBinStream();

	// сохранение коллекции автобусов в поток
	void saveToBinStream();

	// --------------------------------------------------------------------

	stack<int> createStackAndFill(int lo = -20, int hi = 23);
	queue<int> createQueueAndFill(int lo = -20, int hi = 23);
	list<int>  createListAndFill(int lo = -20, int hi = 23);

	// Выводим копию стека, очереди т.к. для стека нет итераторов
	void show(const string& title, stack<int> st);
	void show(const string& title, queue<int> q);

	// выводим список итератором
	void show(const string& title, const list<int>& data, int a = 0, int b = -1);

	// работаем с бинарным файлом: запись, чтение 
	void writeBin(list <int>& data, const string& fileName);
	void readBin(list <int>& data, const string& fileName);

public:
	App():App("buses.bin") {};
	App(const string &fileName) { fileName_ = fileName; }


	// Начальное формирование коллекции данных об автобусах
	void demoInitialize();
	
	// Имитация выезда автобуса из парка
	void demoGoOut();
	
	// Имитация въезда автобуса в парк
	void demoGoIn();
	
	// Вывод сведений об автобусах, упорядоченных по регистрационным номерам
	void showOrderdByRegNum();
	
	// Вывод сведений об автобусах, упорядоченных по номерам маршрутов
	void showOrderdByRoutes();
	
	// Сохранение коллекции всех автобусов в бинарном файле
	void demoSaveToBinStream();
	
	// Чтение данных обо всех автобусах из бинарного файла в коллекцию
	void demoLoadFromBinStream();

	// Обработка стека stack<int>
    void doStack();

    // Обработка очереди queue<int>
    void doQueue();

    // Обработка двусвязного списка list<int>
    void doList();
};
