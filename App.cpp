#include "pch.h"
#include "Utils.h"
#include "App.h"


#pragma region задача на использование ассоциативных контейнеров

// вывести коллекцию автобусов - map
void App::showBuses(const map<string, Bus>& buses, const string& title)
{
	cout << title << Bus::header;
	int i = 0;
	for (auto item : buses) {
		cout << "    " << item.second.toTableRow(++i) << "\n";
	} // for item
	cout << Bus::footer;
} // App::showBuses


// вывести коллекцию автобусов - multimap
void App::showBuses(const multimap<string, Bus>& buses, const string& title)
{
	cout << title << Bus::header;
	int i = 0;
	for (auto item : buses) {
		cout << "    " << item.second.toTableRow(++i) << "\n";
	} // for item
	cout << Bus::footer;
} // App::showBuses


// записать данные из коллекции всех автобусов в коллекции автобусов
// в парке и автобусов на маршрутах
void App::putToMaps()
{
	// чистим коллекции, т.к. метод может вызваться многократно
	busStation_.clear();
	route_.clear();
	
	// заполнение коллекций автобусов в парке и на маршрутах
	for (auto &item : total_) {
		// опредляем указатель на коллекцию для записи автобуса
		map<string, Bus>* pmap =
			(item.second.actualRoute() == "0") ? &busStation_ : &route_;
		// собственно запись в коллекцию
		pmap->insert(item);
	} // for
} // App::putToMaps


// создание multimap для сортировки коллекции по номеру маршрута
multimap<string, Bus> App::makeMultiMap(const map<string, Bus>& buses)
{
	multimap<string, Bus> multiMap;

	for (auto& item : buses) {
		multiMap.emplace(item.second.actualRoute(), item.second);
	} // for item

	return multiMap;
} // App::makeMultiMap


// загрузка коллекции всех автобусов из бинарного потока
// Для упрощения реализации загрузка только в коллекцию всех автобусов
// Копирование в коллекции автобусов на маршрутах и в автопарке делаем
// методом putToMaps()
void App::loadFromBinStream() {
	// открыть бинарный поток ввода
	fstream fs(fileName_, ios::binary | ios::in);
	if (!fs.is_open()) {
		throw exception(("App: не могу открыть файл \"" + fileName_ + "\" для чтения").c_str());
	} // if

	total_.clear();

	// чтение из бинарного потока ввода
	while (!fs.eof()) {
		Bus bus;

		bus.read(fs);

		// два идентичных способа добавления в коллекцию
		total_.emplace(bus.regNum(), bus);
		// total_.insert(make_pair(bus.regNum(), bus));
	} // while

	// закрыть бинарный поток вывода
	fs.close();
} // App::loadFromBinStream


// сохранение коллекции автобусов в поток
void App::saveToBinStream() {
	// открыть бинарный поток вывода
	// ios::trunc очищает файл, усекая его длину до нуля
	fstream fs(fileName_, ios::binary | ios::out | ios::trunc);
	if (!fs.is_open()) {
		throw exception(("App: не могу открыть файл \"" + fileName_ + "\" для записи").c_str());
	} // if

	// итерация по коллекции, запись в бинарный поток вывода
	for (auto &item : total_) {
		item.second.write(fs);
	} // for

	// закрыть бинарный поток вывода
	fs.close();
} // App::saveToBinStream


// Начальное формирование коллекции данных об автобусах
void App::demoInitialize()
{
	showNavBarMessage(hintColor, "  Начальное формирование коллекции данных об автобусах");

	/*
	// начальные данные для заполнения 
	vector<pair<string, Bus>> buses = {
		make_pair<string, Bus>("ВР 512 А 180", Bus("ВР 512 А 180", "Кравченко П.Р.",      "13", "0")),
		make_pair<string, Bus>("ВР 511 О 180", Bus("ВР 511 О 180", "Кравченко О.Р.",      "11", "0")),
		make_pair<string, Bus>("ВО 523 К 180", Bus("ВО 523 К 180", "Кравченко Д.В.",      "12", "0")),
		make_pair<string, Bus>("КА 506 Р 180", Bus("КА 506 Р 180", "Тимченко Д.С.",       "42", "0")),
		make_pair<string, Bus>("ОК 514 А 180", Bus("ОК 232 А 180", "Аскольдиков И.В.",   "85а", "85а")),
		make_pair<string, Bus>("АЕ 503 С 180", Bus("АЕ 503 С 180", "Котов К.С.",          "35", "35")),
		make_pair<string, Bus>("ЕН 525 О 180", Bus("ЕН 525 О 180", "Сурин В.Н.",         "76б", "0")),
		make_pair<string, Bus>("НК 121 Т 180", Bus("НК 121 Т 180", "Ларавель Р.М.",      "121е", "121е")),
		make_pair<string, Bus>("РР 012 А 180", Bus("РР 012 А 180", "Симфонический Р.Т.", "119р", "0")),
		make_pair<string, Bus>("ОН 001 Р 180", Bus("ОН 001 Р 180", "Миронов Н.С.",       "121е", "0")),
		make_pair<string, Bus>("АА 111 А 180", Bus())
	};

	// заполнение общей коллекции автобусов
	total_.clear();
	total_.insert(buses.begin(), buses.end());
	*/

	// вариант инициализации без литерального копирования ключей
	vector<Bus> buses = {
		Bus("ВР 512 А 180", "Кравченко П.Р.",      "13", "0"),
		Bus("ВР 511 О 180", "Кравченко О.Р.",      "11", "0"),
		Bus("ВО 523 К 180", "Кравченко Д.В.",      "12", "0"),
		Bus("КА 506 Р 180", "Тимченко Д.С.",       "42", "0"),
		Bus("ОК 232 А 180", "Аскольдиков И.В.",   "85а", "85а"),
		Bus("АЕ 503 С 180", "Котов К.С.",          "35", "35"),
		Bus("ЕН 525 О 180", "Сурин В.Н.",         "76б", "0"),
		Bus("НК 121 Т 180", "Ларавель Р.М.",      "121е", "121е"),
		Bus("РР 012 А 180", "Симфонический Р.Т.", "119р", "0"),
		Bus("ОН 001 Р 180", "Миронов Н.С.",       "121е", "0"),
		Bus()
	};

	total_.clear();
	for(auto &bus: buses) {
		total_.emplace(bus.regNum(), bus);
	} // for bus

	// забегая вперед - анонс алгоритмов и лямбда-выражений :)
	// применение алгоритма for_each и лямбда-выражения [](){}
	// for_each(buses.begin(), buses.end(), [&](Bus &bus) {
	// 	   total_.emplace(bus.regNum(), bus);
	// });

	putToMaps();

	showBuses(total_, "\n\n    Все автобусы:\n");
	showBuses(busStation_, "\n    Автобусы в автопарке:\n");
	showBuses(route_, "\n    Автобусы на маршрутах:\n");
} // App::demoInitialize


// Имитация выезда автобуса из парка
void App::demoGoOut()
{
	showNavBarMessage(hintColor, "  Имитация выезда автобуса из парка");
	
	showBuses(busStation_, "\n\n\n\n    Автобусы в парке:\n");

	// ввод номера автобуса для выхода из парка
	showInputLine("\n\n    Регистрационный номер автобуса: ", 16, hintColor);
	string regNumber;
	cout << cursor;
	// очистка буферов ввода от '\n' который может остаться после ввода числа 
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, regNumber);
	cout << color(mainColor) << nocursor;

	// имитация выхода автобуса на маршрут
	if (busStation_.find(regNumber) == busStation_.end()) {
		throw exception(("App. В автопарке нет автобуса с номером \""s + regNumber + "\""s).c_str());
	} // if
	
	// получить автобус из коллекции
	Bus bus = busStation_[regNumber];

	// отправить на маршрут
	bus.actualRoute(bus.orderedRoute());
	route_.emplace(bus.regNum(), bus);

	// убрать с автопарка
	busStation_.erase(bus.regNum());

	// скорректировать коллекцию всех автобусов
	total_[regNumber] = bus;

	// показать результат
	cls();
	showNavBarMessage(hintColor, "  Имитация выезда автобуса из парка");
	showBuses(busStation_, "\n\n\n\n    Автобусы в автопарке после выхода автобуса \"" + bus.regNum() + "\" на маршрут:\n");
	showBuses(route_, "\n\n    Автобусы на маршрутах, автобус \"" + bus.regNum() + "\" на маршруте \"" + bus.actualRoute() + "\":\n");
	cout << endlm(5);
} // App::demoGoOut


// Имитация въезда автобуса в парк
void App::demoGoIn()
{
	showNavBarMessage(hintColor, "  Имитация въезда автобуса в парк");

	showBuses(route_, "\n\n\n\n    Автобусы на маршрутах:\n");

	// ввод номера автобуса для возврата в парк
	showInputLine("\n\n    Регистрационный номер автобуса: ", 16, hintColor);
	string regNumber;// очистка буферов ввода от '\n' который может остаться после ввода числа 
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << cursor;
	getline(cin, regNumber);
	cout << color(mainColor) << nocursor;

	// имитация возврата
	if (route_.find(regNumber) == route_.end()) {
		throw exception(("App. На маршруте нет автобуса с номером \"" + regNumber + "\"").c_str());
	} // if
	
	// получить автобус из коллекции
	Bus bus = route_[regNumber];

	// возврат в автопарк
	bus.actualRoute("0");
	busStation_.emplace(bus.regNum(), bus);

	// убрать с маршрута
	route_.erase(bus.regNum());

	// скорректировать коллекцию всех автобусов
	total_[regNumber] = bus;

	// показать автобусы после возврата
	cls();
	showNavBarMessage(hintColor, "  Имитация въезда автобуса в парк");
	showBuses(busStation_, "\n\n\n\n    Автобусы в автопарке после возврата автобуса \"" + 
		bus.regNum() + "\" с маршрута \"" + bus.orderedRoute() + "\":\n");
	showBuses(route_, "\n\n    Автобусы на маршрутах после возврата автобуса \"" +
		bus.regNum() + "\" с маршрута \"" + bus.orderedRoute() + "\":\n");
	cout << endlm(5);
} // App::demoGoIn


// Вывод сведений об автобусах, упорядоченных по регистрационным номерам
void App::showOrderdByRegNum()
{
	showNavBarMessage(hintColor, "  Вывод сведений об автобусах, упорядоченных по регистрационным номерам");
	showBuses(total_, "\n\n    Коллекция автобусов по рег. номерам:\n");
	showBuses(busStation_, "\n    Автобусы в автопарке по рег. номерам:\n");
	showBuses(route_, "\n    Автобусы на маршрутах по рег. номерам:\n");
} // App::showOrderdByRegNum


// Вывод сведений об автобусах, упорядоченных по номерам маршрутов
// !!! строки, состоящие из цифр сортируются как строки, мы же ожидаем сортировки как чисел !!!
void App::showOrderdByRoutes()
{
	showNavBarMessage(hintColor, "  Вывод сведений об автобусах, упорядоченных по номерам маршрутов");

	// заполнить коллекции для вывода автобусов, упорядоченных по 
	// фактическому номеру маршрута, упорядочивание при заполнении
	multimap<string, Bus> all = makeMultiMap(total_);
	multimap<string, Bus> station = makeMultiMap(busStation_);
	multimap<string, Bus> route = makeMultiMap(route_);

	// вывод упорядоченных по номеру фактического маршрута коллекций
	showBuses(all,     "\n\n    Все автобусы - упорядочены по фактическим  маршрутам\n");
	showBuses(station, "\n    Автобусы на станции - упорядочены по фактическим маршрутам\n");
	showBuses(route,   "\n    Автобусы на маршрутах - упорядочены по фактическим маршрутам\n");
} // App::showOrderdByRoutes


// Сохранение коллекции всех автобусов в бинарном файле
void App::demoSaveToBinStream()
{
	showNavBarMessage(hintColor, "  Сохранение коллекции всех автобусов в бинарном файле");

	// собственно запись
	saveToBinStream();

	cout << "\n\n\n\n    Файл " << fileName_ << " сохранен\n\n\n\n";
} // App::demoSaveToBinStream


// Чтение данных обо всех автобусах из бинарного файла в коллекцию
void App::demoLoadFromBinStream()
{
	showNavBarMessage(hintColor, "  Чтение данных обо всех автобусах из бинарного файла в коллекцию");

	// загрузить коллекцию из потока ввода
	loadFromBinStream();

	// вывод в коллекции автобусов
	putToMaps();

	showBuses(total_, "\n\n\n    Коллекция прочитана из файла "s + fileName_ + ":\n"s);
	showBuses(busStation_, "\n    Автобусы в автопарке:\n");
	showBuses(route_, "\n    Автобусы на маршрутах:\n");
} // App::demoLoadFromBinStream
#pragma endregion


#pragma region задача на стек
// Дан непустой стек (класс stack). Создать два новых стека, переместив
// в первый из них все элементы исходного стека с положительными
// значениями, а во второй — с отрицательными (элементы в новых стеках
// будут располагаться в порядке, обратном исходному; один из этих стеков
// может оказаться пустым). Вывести стеки до и после обработки.
void App::doStack() {
	showNavBarMessage(hintColor, "  Обработка стеков stack<int>, перемещение элементов по стекам");

	// сформировать стеки
	stack<int> src = createStackAndFill();

	// положительные в positives, отрицательные в negatives
	stack<int> positives, negatives;

	// показать стеки до обработки
	cout << "\n\n\n\n\tСтеки до обработки\n";
	show("\tИсходный стек     : ", src);
	show("\tCтек положительных: ", positives);
	show("\tCтек отрицательных: ", negatives);

	// перемещение данных по заданию: положительные и отрицательные значения
	// в соответствующие стеки 
	while (!src.empty()) {
		int temp = src.top();
		src.pop();

		// перемещение по стекам
		(temp >= 0 ? positives : negatives).push(temp);
	} // while

	// показать стеки после обработки
	cout << "\n\n\tСтеки после обработки\n";
	show("\tИсходный стек     : ", src);
	show("\tCтек положительных: ", positives);
	show("\tCтек отрицательных: ", negatives);

	cout << endlm(5);
} // App::doStack

// формирование стека 
stack<int> App::createStackAndFill(int lo, int hi)
{
	stack<int> st;

	int n = getRand(8, 12);
	for (int i = 0; i < n; i++) {
		st.push(getRand(lo, hi));
	} // for i

	return st;
} // App::createStackAndFill

// выводим копию стека, т.к. для стека нет итераторов
void App::show(const string& title, stack<int> st)
{
	cout << title;
	if (st.empty()) {
		cout << color(headerColor) << "    стек пуст" << color(mainColor) << "\n";
		return;
	} // if

	// выводим копию стека
	while (!st.empty()) {
		int t = st.top();
		cout << color(t >= 0 ? arrColor : headerColor) << setw(6) << t << color(mainColor);
		st.pop();
	} // while
	cout << "\n";
} // App::show
#pragma endregion


#pragma region задача на очередь
// Даны две непустые очереди (класс queue). Перемещать элементы из начала
// первой очереди в конец второй, пока значение начального элемента
// первой очереди не станет равным 0 (если первая очередь не содержит
// нулевых элементов, то переместить из первой очереди во вторую все
// элементы). Вывести очереди до и после обработки. 

void App::doQueue() {
	// сформировать очереди
	queue<int> q1 = createQueueAndFill(-10, 10);
	queue<int> q2 = createQueueAndFill(-22, 45);

	// показать очереди до обработки
	cout << "\n\n\n\n\tОчереди до обрабтки\n";
	show("\tПервая очередь: ", q1);
	show("\tВторая очередь: ", q2);

	// перемещение данных по заданию: до нулевого элемента в первой очереди
	// или до ее опустошения
	while (!q1.empty() && q1.front() != 0) {
		q2.push(q1.front());
		q1.pop();
	} // while

	// показать очереди после обработки
	cout << "\n\n\n\n\tОчереди после обработки, перемещения из первой во вторую очередь до нулевого элемента:\n";
	show("\tПервая очередь: ", q1);
	show("\tВторая очередь: ", q2);

	cout << endlm(5);
} // App::doStack

// формирование очереди
queue<int> App::createQueueAndFill(int lo, int hi)
{
	queue<int> q;


	int n = getRand(8, 12);
	for (int i = 0; i < n; i++) {
		q.push(getRand(lo, hi));
	} // for i

	return q;
} // App::createQueueAndFill

// Выводим копию очереди, т.к. для очереди нет итераторов
void App::show(const string& title, queue<int> q)
{
	cout << title;
	if (q.empty()) {
		cout << color(headerColor) << "    очередь пуста" << color(mainColor) << "\n";
		return;
	} // if

	// выводим копию очереди
	while (!q.empty()) {
		int t = q.front();
		cout << color(t >= 0 ? arrColor : headerColor) << setw(6) << t << color(mainColor);
		q.pop();
	} // while
	cout << "\n";
} // App::show

#pragma endregion


#pragma region задача на список
// Дан двусвязный список (класс list), содержащий не менее двенадцати
// элементов. Вывести этот список. Сохранить его в бинарном файле.
// Продублировать в списке элементы, значение которых попадает в заданный
// с клавиатуры диапазон значений (новые элементы добавлять перед
// существующими элементами) и вывести преобразованный список.
// Восстановить список из бинарного файла. При помощи set определите все
// различные значения в списке, количество таких значений.

void App::doList()
{
	showNavBarMessage(hintColor, "  Обработка двусвязных списков - классов STL");

	list<int> data = createListAndFill(-5, 5);
	show("\n\n\n\n\tИсходный список:\n\t\t\t", data);
	writeBin(data, "list.dat");

	int a, b;
	showInputLine("\n\n\tВведите границы интервала дублирования: ", 24);
	cin >> cursor >> a >> b >> nocursor >> color(mainColor);

	// проверка корректности ввода диапазона
	checkInputFormat(cin);
	if (a >= b) {
		throw exception("Некорректный диапазон выборки");
	} // if

	// дублировать элементы списка по заданию
	for (auto it = data.begin(); it != data.end(); ++it) {

		int value = *it;
		// дублирование элементов по условию
		if (a <= value && value <= b) {
			data.insert(it, value);
		} // if
	} // for

	ostringstream oss;
	oss << "\n\n\tПреобразованный список, продублированные значения в диапазоне [" << a << ", " << b << "]:\n\t\t\t";
	show(oss.str(), data, a, b);

	readBin(data, "list.dat");
	show("\n\n\tИсходный список, восстановленный из файла:\n\t\t\t", data);

	cout << endlm(5);
} // App::dolList


// формирование двусвязного списка
list<int> App::createListAndFill(int lo, int hi)
{
	list<int> data;

	int n = getRand(8, 18);
	for (int i = 0; i < n; i++) {
		data.push_back(getRand(lo, hi));
	} // for i

	return data;
} // App::createListAndFill

// запись списка в бинарный поток вывода
void App::writeBin(list <int>& data, const string& fileName)
{
	// открыть бинарный поток для вывода
	ofstream ofs(fileName, ios::binary | ios::trunc);
	if (!ofs.is_open()) {
		throw exception(("Не могу открыть бинарный поток для записи списка в файл \"" + fileName + "\"").c_str());
	} // if

	// вывод записей в поток при помощи итератора
	for (auto datum : data) {
		// собственно запись
		ofs.write(reinterpret_cast<char*>(&datum), sizeof(datum));
	} // for 

	// закрыть поток вывода
	ofs.close();
} // App::writeBin


// чтение из бинарного файла при помощи потока ввода в двусвязный список
void App::readBin(list <int>& data, const string& fileName)
{
	// открытие бинарного потока ввода для чтения
	ifstream ifs(fileName, ios::binary);
	if (!ifs.is_open()) {
		throw exception(("Не могу открыть бинарный поток для чтения из файла \"" + fileName + "\"").c_str());
	} // if

	// чистим список для прочитанных данных
	data.clear();

	// чтение данных
	while (!ifs.eof()) {
		int temp;
		ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));

		data.emplace_back(temp);
		ifs.peek();
	} // while

	// закрыть поток чтения, вернуть прочитанные данные
	ifs.close();
} // App::readBin


// вывод списка с выделением цветом элементов с диапазоном значений [a, b]
void App::show(const string& title, const list<int>& data, int a, int b)
{
	cout << title;
	if (data.empty()) {
		cout << color(headerColor) << "    список пуст" << color(mainColor) << "\n";
		return;
	} // if

	// выводим список
	int i = 1;
	for (auto datum : data) {
		cout << color(a <= datum && datum <= b ? arrColor : mainColor)
			 << setw(6) << datum << color(mainColor);
		if (++i % 15 == 0) cout << "\n\t\t\t";
	} // while
	cout << "\n";
} // App::show
#pragma endregion
