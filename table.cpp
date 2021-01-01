#include "table.h"
//入座后，waitperiod, startime, departime都要更新
int table::sitin(customer_info c)	//此时应当有avail = 1
{
	//更新dinner信息
	dinner = c;
	dinner.startime = globaltime;
	dinner.waitperiod = (globaltime.current - dinner.arrivetime.current + 1440)% 1440;
	dinner.departime = globaltime + dinner.eatperiod;	//记得重载+

	//更新avail信息
	avail = 0;
	return 0;
}