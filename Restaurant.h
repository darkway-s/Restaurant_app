#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include "table.h"
#include "customer_info.h"

const int MAX_VOLUME = 16;	//�����������16����
class document 
{
public:
	std::vector<customer_info> customers;
};

class priorder //��д�º���
{
public:
	bool operator() (customer_info a, customer_info b)
	{
		return a.arrivetime > b.arrivetime; //С����
	}
};
struct section
{
	std::priority_queue<customer_info, std::vector<customer_info>, priorder> customers;
	bool Iswaiting()
	{
		return !customers.empty();
	}
};
class Restaurant
{	
private:
	std::vector<std::vector<table>> tables;	//tables[3][2]��ʾ4�����ĵڶ�����������D2
	document bill;
	section wait_section;
public:
	Restaurant(std::istream& intable, std::istream& incustomer);	//��ʼ��tables��wait_section
	int specific_available(int k);	//k�����Ƿ���ã����ؿ���λ��(�����÷���-1)
	int available(int k);	//k�����ϵ����Ƿ���ã����ؿ��õ�����С���緵��m����ʾm��������
	//����k��������һ��������λ��λ����[available()-1, specific_available(available()-1)]

	int dine();	//�õ�λ���Ĺ˿��������ɹ�����1��ʧ�ܷ���0��������Ϣ���µ�bill��

	void output1(std::ostream&);
	void output2(std::ostream&);
	void output3(std::ostream&);
};

