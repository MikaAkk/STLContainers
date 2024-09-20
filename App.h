#pragma once
#include "pch.h"
#include <map>
#include "Bus.h"


// ������������� ����������� �����
class App
{
	// ��������� ���������
	//  ���. ����� --> �������
	map<string, Bus> total_;
	
    // ��������� ��������� � ���������
	//  ���. ����� --> �������
	map<string, Bus> busStation_;
	
	// ��������� ��������� �� ��������
	//  ���. ����� --> �������
	map<string, Bus> route_;

	// ��� ����� ��� ��������� ���������
	string fileName_;

	void showBuses(const map<string, Bus>& buses, const string& title);

	// ��� ������ ���������, ������������� �� ������� ���������
	void showBuses(const multimap<string, Bus>& buses, const string& title);
	void putToMaps();

	// ������������ multimap ��� ���������� �� ������ ��������
	// ����� �������� --> Bus
	multimap<string, Bus> makeMultiMap(const map<string, Bus> &buses);

	// �������� ��������� ��������� �� ������
	void loadFromBinStream();

	// ���������� ��������� ��������� � �����
	void saveToBinStream();

	// --------------------------------------------------------------------

	stack<int> createStackAndFill(int lo = -20, int hi = 23);
	queue<int> createQueueAndFill(int lo = -20, int hi = 23);
	list<int>  createListAndFill(int lo = -20, int hi = 23);

	// ������� ����� �����, ������� �.�. ��� ����� ��� ����������
	void show(const string& title, stack<int> st);
	void show(const string& title, queue<int> q);

	// ������� ������ ����������
	void show(const string& title, const list<int>& data, int a = 0, int b = -1);

	// �������� � �������� ������: ������, ������ 
	void writeBin(list <int>& data, const string& fileName);
	void readBin(list <int>& data, const string& fileName);

public:
	App():App("buses.bin") {};
	App(const string &fileName) { fileName_ = fileName; }


	// ��������� ������������ ��������� ������ �� ���������
	void demoInitialize();
	
	// �������� ������ �������� �� �����
	void demoGoOut();
	
	// �������� ������ �������� � ����
	void demoGoIn();
	
	// ����� �������� �� ���������, ������������� �� ��������������� �������
	void showOrderdByRegNum();
	
	// ����� �������� �� ���������, ������������� �� ������� ���������
	void showOrderdByRoutes();
	
	// ���������� ��������� ���� ��������� � �������� �����
	void demoSaveToBinStream();
	
	// ������ ������ ��� ���� ��������� �� ��������� ����� � ���������
	void demoLoadFromBinStream();

	// ��������� ����� stack<int>
    void doStack();

    // ��������� ������� queue<int>
    void doQueue();

    // ��������� ����������� ������ list<int>
    void doList();
};
