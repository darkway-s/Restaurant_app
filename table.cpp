#include "table.h"
//������waitperiod, startime, departime��Ҫ����
int table::sitin(customer_info c)	//��ʱӦ����avail = 1
{
	//����dinner��Ϣ
	dinner = c;
	dinner.startime = globaltime;
	dinner.waitperiod = (globaltime.current - dinner.arrivetime.current + 1440)% 1440;
	dinner.departime = globaltime + dinner.eatperiod;	//�ǵ�����+

	//����avail��Ϣ
	avail = 0;
	return 0;
}