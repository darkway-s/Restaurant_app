#pragma once
#include"resclock.h"
class clock;
class customer_info
{
	friend class table;
	friend class priorder;
	friend class Restaurant;
	friend std::ostream& operator << (std::ostream& output, customer_info& c); //定义运算符“<<”重载函数
private:
	int id;					//编号
	int size;				//顾客人数
	resclock arrivetime;	//到来时刻
	int waitperiod;			//等待用时
	resclock startime;		//就餐时刻
	int eatperiod;			//就餐用时
	resclock departime;		//离开时刻
public:
	customer_info(): id(0), size(0), arrivetime(0), waitperiod(0),startime(0),eatperiod(0),departime(0){}
	customer_info(int siz, resclock arriv, int eatp):id(0), size(siz), arrivetime(arriv), waitperiod(0), startime(0), eatperiod(eatp), departime(0){}
};

std::ostream& operator << (std::ostream& output, customer_info& c); //定义运算符“<<”重载函数
