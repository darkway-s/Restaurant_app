#pragma once
#include"resclock.h"
#include"customer_info.h"
class table
{
	friend class Restaurant;
private:
	customer_info dinner;
	bool avail;
	
public:
	table():avail(1){}
	bool available()const { return avail; }
	void update_avail()
	{
		//仅当原来不可用（有人在吃饭）时更新
		if(avail == 0)
			avail =  dinner.departime <= globaltime;
	}
	int dinnerid()
	{
		if(avail == 1)
			return -1;
		else
			return dinner.id;
	}
	resclock& startime() { return dinner.startime; }
	resclock& depatime() { return dinner.departime; }
	int sitin(customer_info c);
};

