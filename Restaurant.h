#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include "table.h"
#include "customer_info.h"

const int MAX_VOLUME = 16;	//�����������16����
struct document 
{
	std::vector<customer_info> customers;
};

struct priorder //��д�º���
{
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
};

