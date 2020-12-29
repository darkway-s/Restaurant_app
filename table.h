#pragma once
#include"resclock.h"
#include"customer_info.h"
class table
{
private:
	customer_info dinner;
	bool avail;
	
public:
	table():avail(1){}
	bool available()const { return avail; }
	void update_avail()
	{
		avail =  dinner.departime.current >= globaltime.current;
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
};

