#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include "table.h"
#include "customer_info.h"

const int MAX_VOLUME = 16;	//最大桌不超过16人桌
struct document 
{
	std::vector<customer_info> customers;
};

struct priorder //重写仿函数
{
	bool operator() (customer_info a, customer_info b)
	{
		return a.arrivetime > b.arrivetime; //小顶堆
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
	std::vector<std::vector<table>> tables;	//tables[3][2]表示4人桌的第二号桌，记作D2
	document bill;
	section wait_section;
public:
	Restaurant(std::istream& intable, std::istream& incustomer);	//初始化tables和wait_section
};

