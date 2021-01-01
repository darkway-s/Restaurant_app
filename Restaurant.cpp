#include "Restaurant.h"
using namespace std;
#define DEBUG
//input
/***
* input_customer1.txt
2 11:00 0:05
2 11:00 0:05
2 11:01 0:05
1 11:02 0:03
0
* input_table1.txt
4 1
2 2
0
***/
/*std::vector<std::vector<table>> tables*/
Restaurant::Restaurant(std::istream& intable, std::istream& incustomer):tables(MAX_VOLUME)
{
	//intable to tables
	int k, num;	//k人桌的个数为num
	table newtable;
	vector<table> newrow;
	intable >> num;
	for (; num != 0; intable >> num)
	{
		intable >> k;
		//k <= 0的情况暂不考虑
		vector<table> newrow(num);
		tables[k - 1] = newrow;
	}

	//incustomer to wait_section
	string ins;
	getline(incustomer, ins);
	for (; ins[0] != '0'; getline(incustomer, ins))
	{
		int siz = ins[0] - '0';
		resclock arriv((ins[2] - '0') * 10 + ins[3] - '0', (ins[5] - '0') * 10 + ins[6] - '0');
		int eatp = (ins[8] - '0') * 60 + (ins[10]-'0')* 10 + ins[11] -'0';
		customer_info newcustomer(siz, arriv, eatp);
		wait_section.push(newcustomer);
	} 
}

//output
void Restaurant::output1(std::ostream& outdata)	//一天中所有组顾客在饭店的平均停留时间、平均等位时间。注：一组顾客的停留时间=等位时间+就餐时间；
{
	int n = bill.size();	//顾客组数
	int sumwait = 0, sumstay = 0,  sumdine = 0;
	double avgwait = 0, avgstay = 0, avgdine = 0;
	for (int i = 0; i < n; i++)
	{
		sumwait += bill[i].waitperiod;
		sumdine += bill[i].eatperiod;
	}
	sumstay = sumwait + sumdine;
	avgstay = sumstay / n;
	avgwait = sumwait / n;

	
	outdata << "平均停留时间: " << avgstay << "秒" << endl;
	outdata << "平均等位时间: " << avgwait << "秒" << endl;
}

void Restaurant::output2(std::ostream& outdata)
{
	resclock lastdepart = starttime;
	int n = bill.size();	//顾客组数
	for (int i = 0; i < n; i++)
	{
		if (bill[i].departime >= lastdepart)
			lastdepart = bill[i].departime;
	}
	outdata << "最后一组离开饭店的顾客的离开时间: " << lastdepart << endl;
}
void Restaurant::output3(std::ostream& outcustomer)
{
	outcustomer << "编号" << "\t" << "顾客人数" << "\t" << "到来时刻" << "\t"
		<< "等待用时" << "\t" << "就餐时刻" << "\t" << "就餐用时" << "\t" << "离开时刻" << endl;
	int n = bill.size();	//顾客组数
	for (int i = 0; i < n; i++)
		outcustomer << bill[i];
}

//functions
int Restaurant::specific_available(int k)	//遍历tables[k-1]，如果存在一桌座位可用，就可用座位的号码,否则返回-1
{
	if (k <= 0)	return -1;	//对于0人桌，肯定是没有的

	typedef vector<table>::size_type vecsize;
	vecsize siz = tables[k - 1].size();
	for (vecsize i = 0; i < siz; i++)
	{
		if (tables[k - 1][i].available())
			return i;
	}
	return -1;
}
int Restaurant::available(int k)	//存在m>=k，使得m人桌可用，返回m，否则返回0。
{	//k<=0时，情况同k = 1。
	for (int i = k; i <= MAX_VOLUME; i++)
	{
		if (specific_available(i) != -1)
			return i;
	}
	return 0;
}
bool Restaurant::Iswaiting()
{
	//在当前时刻，有人在排队，并且当前队首到达时间早于当前时间
	return !wait_section.empty() && wait_section.top().arrivetime <= globaltime;
}
void Restaurant::update_table_avail()
{
	//遍历所有table，更新他们的avail状态
	int bigsiz = tables.size();
	for (int i = 0; i < bigsiz; i++)
	{
		int smlsiz = tables[i].size();
		for (int j = 0; j < smlsiz; j++)
		{
			tables[i][j].update_avail();
		}
	}
}

int Restaurant::dine()	//当前时刻为全局变量globaltime
{
	while (available() && Iswaiting())	//饭店有空位且有人在等
	{
		//安排入座
		customer_info newcomer = wait_section.top();
		int k = newcomer.size;
		int tablesiz = available(k);
		if (tablesiz == 0)//否则继续等着,后续优化再做 TODO
		{
			return 0;
		}
		else	//对于newcomer组放得下,对于k人桌，下一个可用座位的位置是[available()-1, specific_available(available()-1)]
		{
			//赋予id
			newcomer.id = nextid++;
			//更新等待区
			wait_section.pop();
			//更新tables状态
			int tablenum = specific_available(tablesiz);
			tables[tablesiz - 1][tablenum].sitin(newcomer);
#ifdef DEBUG
			cout << globaltime << ", 入座" << tablesiz << "人桌 " << tablenum << "号桌" << endl;
#endif
			//更新bill
			bill.push_back(tables[tablesiz - 1][tablenum].dinner);
		}
	}
	return 0;
}
