#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include "table.h"
#include "customer_info.h"

const int MAX_VOLUME = 16;	//最大桌不超过16人桌
class document 
{
public:
	std::vector<customer_info> customers;
};

class priorder //重写仿函数
{
public:
	bool operator() (customer_info a, customer_info b)
	{
		return a.arrivetime > b.arrivetime; //小顶堆
	}
};
class section
{
public:
	std::priority_queue<customer_info, std::vector<customer_info>, priorder> customers;
	bool Iswaiting()
	{
		//有人在排队，并且当前队首到达时间早于当前时间
		return !customers.empty() && customers.top().arrivetime <= globaltime;
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
	int specific_available(int k);	//k人桌是否可用，返回可用位置(不可用返回-1)
	int available(int k);	//k人以上的桌是否可用，返回可用的桌大小，如返回m，表示m人桌可用

	//对于k人桌，下一个可用座位的位置是[available()-1, specific_available(available()-1)]

	int dine();	//让等位区的顾客入座，成功返回1，失败返回0。入座信息更新到bill中

	void output1(std::ostream&);
	void output2(std::ostream&);
	void output3(std::ostream&);
};

