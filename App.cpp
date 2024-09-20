#include "pch.h"
#include "Utils.h"
#include "App.h"


#pragma region ������ �� ������������� ������������� �����������

// ������� ��������� ��������� - map
void App::showBuses(const map<string, Bus>& buses, const string& title)
{
	cout << title << Bus::header;
	int i = 0;
	for (auto item : buses) {
		cout << "    " << item.second.toTableRow(++i) << "\n";
	} // for item
	cout << Bus::footer;
} // App::showBuses


// ������� ��������� ��������� - multimap
void App::showBuses(const multimap<string, Bus>& buses, const string& title)
{
	cout << title << Bus::header;
	int i = 0;
	for (auto item : buses) {
		cout << "    " << item.second.toTableRow(++i) << "\n";
	} // for item
	cout << Bus::footer;
} // App::showBuses


// �������� ������ �� ��������� ���� ��������� � ��������� ���������
// � ����� � ��������� �� ���������
void App::putToMaps()
{
	// ������ ���������, �.�. ����� ����� ��������� �����������
	busStation_.clear();
	route_.clear();
	
	// ���������� ��������� ��������� � ����� � �� ���������
	for (auto &item : total_) {
		// ��������� ��������� �� ��������� ��� ������ ��������
		map<string, Bus>* pmap =
			(item.second.actualRoute() == "0") ? &busStation_ : &route_;
		// ���������� ������ � ���������
		pmap->insert(item);
	} // for
} // App::putToMaps


// �������� multimap ��� ���������� ��������� �� ������ ��������
multimap<string, Bus> App::makeMultiMap(const map<string, Bus>& buses)
{
	multimap<string, Bus> multiMap;

	for (auto& item : buses) {
		multiMap.emplace(item.second.actualRoute(), item.second);
	} // for item

	return multiMap;
} // App::makeMultiMap


// �������� ��������� ���� ��������� �� ��������� ������
// ��� ��������� ���������� �������� ������ � ��������� ���� ���������
// ����������� � ��������� ��������� �� ��������� � � ��������� ������
// ������� putToMaps()
void App::loadFromBinStream() {
	// ������� �������� ����� �����
	fstream fs(fileName_, ios::binary | ios::in);
	if (!fs.is_open()) {
		throw exception(("App: �� ���� ������� ���� \"" + fileName_ + "\" ��� ������").c_str());
	} // if

	total_.clear();

	// ������ �� ��������� ������ �����
	while (!fs.eof()) {
		Bus bus;

		bus.read(fs);

		// ��� ���������� ������� ���������� � ���������
		total_.emplace(bus.regNum(), bus);
		// total_.insert(make_pair(bus.regNum(), bus));
	} // while

	// ������� �������� ����� ������
	fs.close();
} // App::loadFromBinStream


// ���������� ��������� ��������� � �����
void App::saveToBinStream() {
	// ������� �������� ����� ������
	// ios::trunc ������� ����, ������ ��� ����� �� ����
	fstream fs(fileName_, ios::binary | ios::out | ios::trunc);
	if (!fs.is_open()) {
		throw exception(("App: �� ���� ������� ���� \"" + fileName_ + "\" ��� ������").c_str());
	} // if

	// �������� �� ���������, ������ � �������� ����� ������
	for (auto &item : total_) {
		item.second.write(fs);
	} // for

	// ������� �������� ����� ������
	fs.close();
} // App::saveToBinStream


// ��������� ������������ ��������� ������ �� ���������
void App::demoInitialize()
{
	showNavBarMessage(hintColor, "  ��������� ������������ ��������� ������ �� ���������");

	/*
	// ��������� ������ ��� ���������� 
	vector<pair<string, Bus>> buses = {
		make_pair<string, Bus>("�� 512 � 180", Bus("�� 512 � 180", "��������� �.�.",      "13", "0")),
		make_pair<string, Bus>("�� 511 � 180", Bus("�� 511 � 180", "��������� �.�.",      "11", "0")),
		make_pair<string, Bus>("�� 523 � 180", Bus("�� 523 � 180", "��������� �.�.",      "12", "0")),
		make_pair<string, Bus>("�� 506 � 180", Bus("�� 506 � 180", "�������� �.�.",       "42", "0")),
		make_pair<string, Bus>("�� 514 � 180", Bus("�� 232 � 180", "����������� �.�.",   "85�", "85�")),
		make_pair<string, Bus>("�� 503 � 180", Bus("�� 503 � 180", "����� �.�.",          "35", "35")),
		make_pair<string, Bus>("�� 525 � 180", Bus("�� 525 � 180", "����� �.�.",         "76�", "0")),
		make_pair<string, Bus>("�� 121 � 180", Bus("�� 121 � 180", "�������� �.�.",      "121�", "121�")),
		make_pair<string, Bus>("�� 012 � 180", Bus("�� 012 � 180", "������������� �.�.", "119�", "0")),
		make_pair<string, Bus>("�� 001 � 180", Bus("�� 001 � 180", "������� �.�.",       "121�", "0")),
		make_pair<string, Bus>("�� 111 � 180", Bus())
	};

	// ���������� ����� ��������� ���������
	total_.clear();
	total_.insert(buses.begin(), buses.end());
	*/

	// ������� ������������� ��� ������������ ����������� ������
	vector<Bus> buses = {
		Bus("�� 512 � 180", "��������� �.�.",      "13", "0"),
		Bus("�� 511 � 180", "��������� �.�.",      "11", "0"),
		Bus("�� 523 � 180", "��������� �.�.",      "12", "0"),
		Bus("�� 506 � 180", "�������� �.�.",       "42", "0"),
		Bus("�� 232 � 180", "����������� �.�.",   "85�", "85�"),
		Bus("�� 503 � 180", "����� �.�.",          "35", "35"),
		Bus("�� 525 � 180", "����� �.�.",         "76�", "0"),
		Bus("�� 121 � 180", "�������� �.�.",      "121�", "121�"),
		Bus("�� 012 � 180", "������������� �.�.", "119�", "0"),
		Bus("�� 001 � 180", "������� �.�.",       "121�", "0"),
		Bus()
	};

	total_.clear();
	for(auto &bus: buses) {
		total_.emplace(bus.regNum(), bus);
	} // for bus

	// ������� ������ - ����� ���������� � ������-��������� :)
	// ���������� ��������� for_each � ������-��������� [](){}
	// for_each(buses.begin(), buses.end(), [&](Bus &bus) {
	// 	   total_.emplace(bus.regNum(), bus);
	// });

	putToMaps();

	showBuses(total_, "\n\n    ��� ��������:\n");
	showBuses(busStation_, "\n    �������� � ���������:\n");
	showBuses(route_, "\n    �������� �� ���������:\n");
} // App::demoInitialize


// �������� ������ �������� �� �����
void App::demoGoOut()
{
	showNavBarMessage(hintColor, "  �������� ������ �������� �� �����");
	
	showBuses(busStation_, "\n\n\n\n    �������� � �����:\n");

	// ���� ������ �������� ��� ������ �� �����
	showInputLine("\n\n    ��������������� ����� ��������: ", 16, hintColor);
	string regNumber;
	cout << cursor;
	// ������� ������� ����� �� '\n' ������� ����� �������� ����� ����� ����� 
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, regNumber);
	cout << color(mainColor) << nocursor;

	// �������� ������ �������� �� �������
	if (busStation_.find(regNumber) == busStation_.end()) {
		throw exception(("App. � ��������� ��� �������� � ������� \""s + regNumber + "\""s).c_str());
	} // if
	
	// �������� ������� �� ���������
	Bus bus = busStation_[regNumber];

	// ��������� �� �������
	bus.actualRoute(bus.orderedRoute());
	route_.emplace(bus.regNum(), bus);

	// ������ � ���������
	busStation_.erase(bus.regNum());

	// ��������������� ��������� ���� ���������
	total_[regNumber] = bus;

	// �������� ���������
	cls();
	showNavBarMessage(hintColor, "  �������� ������ �������� �� �����");
	showBuses(busStation_, "\n\n\n\n    �������� � ��������� ����� ������ �������� \"" + bus.regNum() + "\" �� �������:\n");
	showBuses(route_, "\n\n    �������� �� ���������, ������� \"" + bus.regNum() + "\" �� �������� \"" + bus.actualRoute() + "\":\n");
	cout << endlm(5);
} // App::demoGoOut


// �������� ������ �������� � ����
void App::demoGoIn()
{
	showNavBarMessage(hintColor, "  �������� ������ �������� � ����");

	showBuses(route_, "\n\n\n\n    �������� �� ���������:\n");

	// ���� ������ �������� ��� �������� � ����
	showInputLine("\n\n    ��������������� ����� ��������: ", 16, hintColor);
	string regNumber;// ������� ������� ����� �� '\n' ������� ����� �������� ����� ����� ����� 
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	cout << cursor;
	getline(cin, regNumber);
	cout << color(mainColor) << nocursor;

	// �������� ��������
	if (route_.find(regNumber) == route_.end()) {
		throw exception(("App. �� �������� ��� �������� � ������� \"" + regNumber + "\"").c_str());
	} // if
	
	// �������� ������� �� ���������
	Bus bus = route_[regNumber];

	// ������� � ��������
	bus.actualRoute("0");
	busStation_.emplace(bus.regNum(), bus);

	// ������ � ��������
	route_.erase(bus.regNum());

	// ��������������� ��������� ���� ���������
	total_[regNumber] = bus;

	// �������� �������� ����� ��������
	cls();
	showNavBarMessage(hintColor, "  �������� ������ �������� � ����");
	showBuses(busStation_, "\n\n\n\n    �������� � ��������� ����� �������� �������� \"" + 
		bus.regNum() + "\" � �������� \"" + bus.orderedRoute() + "\":\n");
	showBuses(route_, "\n\n    �������� �� ��������� ����� �������� �������� \"" +
		bus.regNum() + "\" � �������� \"" + bus.orderedRoute() + "\":\n");
	cout << endlm(5);
} // App::demoGoIn


// ����� �������� �� ���������, ������������� �� ��������������� �������
void App::showOrderdByRegNum()
{
	showNavBarMessage(hintColor, "  ����� �������� �� ���������, ������������� �� ��������������� �������");
	showBuses(total_, "\n\n    ��������� ��������� �� ���. �������:\n");
	showBuses(busStation_, "\n    �������� � ��������� �� ���. �������:\n");
	showBuses(route_, "\n    �������� �� ��������� �� ���. �������:\n");
} // App::showOrderdByRegNum


// ����� �������� �� ���������, ������������� �� ������� ���������
// !!! ������, ��������� �� ���� ����������� ��� ������, �� �� ������� ���������� ��� ����� !!!
void App::showOrderdByRoutes()
{
	showNavBarMessage(hintColor, "  ����� �������� �� ���������, ������������� �� ������� ���������");

	// ��������� ��������� ��� ������ ���������, ������������� �� 
	// ������������ ������ ��������, �������������� ��� ����������
	multimap<string, Bus> all = makeMultiMap(total_);
	multimap<string, Bus> station = makeMultiMap(busStation_);
	multimap<string, Bus> route = makeMultiMap(route_);

	// ����� ������������� �� ������ ������������ �������� ���������
	showBuses(all,     "\n\n    ��� �������� - ����������� �� �����������  ���������\n");
	showBuses(station, "\n    �������� �� ������� - ����������� �� ����������� ���������\n");
	showBuses(route,   "\n    �������� �� ��������� - ����������� �� ����������� ���������\n");
} // App::showOrderdByRoutes


// ���������� ��������� ���� ��������� � �������� �����
void App::demoSaveToBinStream()
{
	showNavBarMessage(hintColor, "  ���������� ��������� ���� ��������� � �������� �����");

	// ���������� ������
	saveToBinStream();

	cout << "\n\n\n\n    ���� " << fileName_ << " ��������\n\n\n\n";
} // App::demoSaveToBinStream


// ������ ������ ��� ���� ��������� �� ��������� ����� � ���������
void App::demoLoadFromBinStream()
{
	showNavBarMessage(hintColor, "  ������ ������ ��� ���� ��������� �� ��������� ����� � ���������");

	// ��������� ��������� �� ������ �����
	loadFromBinStream();

	// ����� � ��������� ���������
	putToMaps();

	showBuses(total_, "\n\n\n    ��������� ��������� �� ����� "s + fileName_ + ":\n"s);
	showBuses(busStation_, "\n    �������� � ���������:\n");
	showBuses(route_, "\n    �������� �� ���������:\n");
} // App::demoLoadFromBinStream
#pragma endregion


#pragma region ������ �� ����
// ��� �������� ���� (����� stack). ������� ��� ����� �����, ����������
// � ������ �� ��� ��� �������� ��������� ����� � ��������������
// ����������, � �� ������ � � �������������� (�������� � ����� ������
// ����� ������������� � �������, �������� ���������; ���� �� ���� ������
// ����� ��������� ������). ������� ����� �� � ����� ���������.
void App::doStack() {
	showNavBarMessage(hintColor, "  ��������� ������ stack<int>, ����������� ��������� �� ������");

	// ������������ �����
	stack<int> src = createStackAndFill();

	// ������������� � positives, ������������� � negatives
	stack<int> positives, negatives;

	// �������� ����� �� ���������
	cout << "\n\n\n\n\t����� �� ���������\n";
	show("\t�������� ����     : ", src);
	show("\tC��� �������������: ", positives);
	show("\tC��� �������������: ", negatives);

	// ����������� ������ �� �������: ������������� � ������������� ��������
	// � ��������������� ����� 
	while (!src.empty()) {
		int temp = src.top();
		src.pop();

		// ����������� �� ������
		(temp >= 0 ? positives : negatives).push(temp);
	} // while

	// �������� ����� ����� ���������
	cout << "\n\n\t����� ����� ���������\n";
	show("\t�������� ����     : ", src);
	show("\tC��� �������������: ", positives);
	show("\tC��� �������������: ", negatives);

	cout << endlm(5);
} // App::doStack

// ������������ ����� 
stack<int> App::createStackAndFill(int lo, int hi)
{
	stack<int> st;

	int n = getRand(8, 12);
	for (int i = 0; i < n; i++) {
		st.push(getRand(lo, hi));
	} // for i

	return st;
} // App::createStackAndFill

// ������� ����� �����, �.�. ��� ����� ��� ����������
void App::show(const string& title, stack<int> st)
{
	cout << title;
	if (st.empty()) {
		cout << color(headerColor) << "    ���� ����" << color(mainColor) << "\n";
		return;
	} // if

	// ������� ����� �����
	while (!st.empty()) {
		int t = st.top();
		cout << color(t >= 0 ? arrColor : headerColor) << setw(6) << t << color(mainColor);
		st.pop();
	} // while
	cout << "\n";
} // App::show
#pragma endregion


#pragma region ������ �� �������
// ���� ��� �������� ������� (����� queue). ���������� �������� �� ������
// ������ ������� � ����� ������, ���� �������� ���������� ��������
// ������ ������� �� ������ ������ 0 (���� ������ ������� �� ��������
// ������� ���������, �� ����������� �� ������ ������� �� ������ ���
// ��������). ������� ������� �� � ����� ���������. 

void App::doQueue() {
	// ������������ �������
	queue<int> q1 = createQueueAndFill(-10, 10);
	queue<int> q2 = createQueueAndFill(-22, 45);

	// �������� ������� �� ���������
	cout << "\n\n\n\n\t������� �� ��������\n";
	show("\t������ �������: ", q1);
	show("\t������ �������: ", q2);

	// ����������� ������ �� �������: �� �������� �������� � ������ �������
	// ��� �� �� �����������
	while (!q1.empty() && q1.front() != 0) {
		q2.push(q1.front());
		q1.pop();
	} // while

	// �������� ������� ����� ���������
	cout << "\n\n\n\n\t������� ����� ���������, ����������� �� ������ �� ������ ������� �� �������� ��������:\n";
	show("\t������ �������: ", q1);
	show("\t������ �������: ", q2);

	cout << endlm(5);
} // App::doStack

// ������������ �������
queue<int> App::createQueueAndFill(int lo, int hi)
{
	queue<int> q;


	int n = getRand(8, 12);
	for (int i = 0; i < n; i++) {
		q.push(getRand(lo, hi));
	} // for i

	return q;
} // App::createQueueAndFill

// ������� ����� �������, �.�. ��� ������� ��� ����������
void App::show(const string& title, queue<int> q)
{
	cout << title;
	if (q.empty()) {
		cout << color(headerColor) << "    ������� �����" << color(mainColor) << "\n";
		return;
	} // if

	// ������� ����� �������
	while (!q.empty()) {
		int t = q.front();
		cout << color(t >= 0 ? arrColor : headerColor) << setw(6) << t << color(mainColor);
		q.pop();
	} // while
	cout << "\n";
} // App::show

#pragma endregion


#pragma region ������ �� ������
// ��� ���������� ������ (����� list), ���������� �� ����� ����������
// ���������. ������� ���� ������. ��������� ��� � �������� �����.
// �������������� � ������ ��������, �������� ������� �������� � ��������
// � ���������� �������� �������� (����� �������� ��������� �����
// ������������� ����������) � ������� ��������������� ������.
// ������������ ������ �� ��������� �����. ��� ������ set ���������� ���
// ��������� �������� � ������, ���������� ����� ��������.

void App::doList()
{
	showNavBarMessage(hintColor, "  ��������� ���������� ������� - ������� STL");

	list<int> data = createListAndFill(-5, 5);
	show("\n\n\n\n\t�������� ������:\n\t\t\t", data);
	writeBin(data, "list.dat");

	int a, b;
	showInputLine("\n\n\t������� ������� ��������� ������������: ", 24);
	cin >> cursor >> a >> b >> nocursor >> color(mainColor);

	// �������� ������������ ����� ���������
	checkInputFormat(cin);
	if (a >= b) {
		throw exception("������������ �������� �������");
	} // if

	// ����������� �������� ������ �� �������
	for (auto it = data.begin(); it != data.end(); ++it) {

		int value = *it;
		// ������������ ��������� �� �������
		if (a <= value && value <= b) {
			data.insert(it, value);
		} // if
	} // for

	ostringstream oss;
	oss << "\n\n\t��������������� ������, ���������������� �������� � ��������� [" << a << ", " << b << "]:\n\t\t\t";
	show(oss.str(), data, a, b);

	readBin(data, "list.dat");
	show("\n\n\t�������� ������, ��������������� �� �����:\n\t\t\t", data);

	cout << endlm(5);
} // App::dolList


// ������������ ����������� ������
list<int> App::createListAndFill(int lo, int hi)
{
	list<int> data;

	int n = getRand(8, 18);
	for (int i = 0; i < n; i++) {
		data.push_back(getRand(lo, hi));
	} // for i

	return data;
} // App::createListAndFill

// ������ ������ � �������� ����� ������
void App::writeBin(list <int>& data, const string& fileName)
{
	// ������� �������� ����� ��� ������
	ofstream ofs(fileName, ios::binary | ios::trunc);
	if (!ofs.is_open()) {
		throw exception(("�� ���� ������� �������� ����� ��� ������ ������ � ���� \"" + fileName + "\"").c_str());
	} // if

	// ����� ������� � ����� ��� ������ ���������
	for (auto datum : data) {
		// ���������� ������
		ofs.write(reinterpret_cast<char*>(&datum), sizeof(datum));
	} // for 

	// ������� ����� ������
	ofs.close();
} // App::writeBin


// ������ �� ��������� ����� ��� ������ ������ ����� � ���������� ������
void App::readBin(list <int>& data, const string& fileName)
{
	// �������� ��������� ������ ����� ��� ������
	ifstream ifs(fileName, ios::binary);
	if (!ifs.is_open()) {
		throw exception(("�� ���� ������� �������� ����� ��� ������ �� ����� \"" + fileName + "\"").c_str());
	} // if

	// ������ ������ ��� ����������� ������
	data.clear();

	// ������ ������
	while (!ifs.eof()) {
		int temp;
		ifs.read(reinterpret_cast<char*>(&temp), sizeof(temp));

		data.emplace_back(temp);
		ifs.peek();
	} // while

	// ������� ����� ������, ������� ����������� ������
	ifs.close();
} // App::readBin


// ����� ������ � ���������� ������ ��������� � ���������� �������� [a, b]
void App::show(const string& title, const list<int>& data, int a, int b)
{
	cout << title;
	if (data.empty()) {
		cout << color(headerColor) << "    ������ ����" << color(mainColor) << "\n";
		return;
	} // if

	// ������� ������
	int i = 1;
	for (auto datum : data) {
		cout << color(a <= datum && datum <= b ? arrColor : mainColor)
			 << setw(6) << datum << color(mainColor);
		if (++i % 15 == 0) cout << "\n\t\t\t";
	} // while
	cout << "\n";
} // App::show
#pragma endregion
