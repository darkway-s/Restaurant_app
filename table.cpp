#include "table.h"
//������waitperiod, startime, departime��Ҫ����
int table::sitin(customer_info c)	//��ʱӦ����avail = 1
{
	//����dinner��Ϣ
	dinner = c;
	dinner.startime = globaltime;
	dinner.waitperiod = globaltime.current - dinner.arrivetime.current;
	dinner.departime = globaltime + dinner.eatperiod;	//�ǵ�����+
	//����avail��Ϣ
	avail = 0;
	return 0;
}