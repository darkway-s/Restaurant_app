#include "Restaurant.h"
using namespace std;
#define DEBUG
//input
/*
* input_table2.txt
4 1
3 2
2 3
1 4
0
***/
/*std::vector<std::vector<table>> tables*/
Restaurant::Restaurant(std::istream& intable, std::istream& incustomer):tables(MAX_VOLUME),nextid(FIRST_ID)
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
/***
* input_customer1.txt
2 11:00 0:07
2 11:01 0:07
2 11:02 0:07
1 11:03 0:03
0
***/
	//incustomer to wait_section
	int siz, arriv_hour, arriv_minute, eatp;
	incustomer >> siz;
	while (siz != 0)
	{
		incustomer >> arriv_hour;
		incustomer.ignore();
		incustomer >> arriv_minute;
		incustomer.ignore(3, ':');	//ignore(2, ':')或ignore(3)都可以
		incustomer >> eatp;

		resclock arriv(arriv_hour, arriv_minute);
		customer_info newcustomer(siz, arriv, eatp);
		wait_section.push(newcustomer);

		incustomer >> siz;
	}
	//赋予id
	stack<customer_info> s;	//工作栈s存储历史数据
	customer_info dinner;	//dinner为当前顾客
	while (!wait_section.empty())
	{
		//取出
		dinner =  wait_section.top();
		wait_section.pop();
		//更新
		dinner.id = nextid++;
		//放回
		s.push(dinner);
	}
	while (!s.empty())
	{
		dinner = s.top();
		s.pop();
		wait_section.push(dinner);
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
	avgstay = ((double)sumstay) / n;
	avgwait = ((double)sumwait) / n;

	
	outdata << "平均停留时间: " << avgstay << " min" << endl;
	outdata << "平均等位时间: " << avgwait << " min" << endl;
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
	orderbill(); //按编号排序账单
	outcustomer << "编号" << "\t" << "顾客人数" << "\t" << "到来时刻" << "\t"
		<< "等待用时" << "\t" << "就餐时刻" << "\t" << "就餐用时" << "  \t" << "离开时刻" << endl;
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
/*int Restaurant::available(int k)	//存在m>=k，使得m人桌可用，返回m，否则返回0。
{	//k<=0时，情况同k = 1。

	//4人组只能去4人桌
	if (k == MAX_VOLUME)
		if (specific_available(k) != -1)
			return k;
		else return 0;
	else //其他组不能去4人桌
	{
		for (int i = k; i <= MAX_VOLUME - 1; i++)
		{
			if (specific_available(i) != -1)
				return i;
		}
		return 0;
	}
}*/
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
	if (available() && Iswaiting() == 0)	return 0;
	while (available() && Iswaiting())	//饭店有空位且有人在等
	{
		//安排一组顾客入座
		customer_info newcomer = wait_section.top();
		wait_section.pop();
		int k = newcomer.size;
		int tablesiz = available(k);
		if (tablesiz == 0)	//遍历所有可用等位顾客，找到available的一个，如果没有，直接return 0（整个函数）
		{
			stack<customer_info> s;	//s记录已经遍历到的等位过客
			s.push(newcomer);	//建栈之前就已经pop了一个，现在存入
			while (Iswaiting() && tablesiz == 0)	//遍历剩余
			{
				newcomer = wait_section.top();
				wait_section.pop();
				s.push(newcomer);					//边出边进
				k = newcomer.size;
				tablesiz = available(k);
			}
			//找到第一个使得tablesiz不为0的顾客newcomer
			if (tablesiz != 0)						
				s.pop();							//对于正确的newcomer，就不用恢复进wait_section中了
			//restore wait_section
			customer_info lastcustomer;
			while (!s.empty())
			{
				lastcustomer = s.top();
				s.pop();
				wait_section.push(lastcustomer);
			}
			if(tablesiz == 0)
				return 0;
		}
		
		//对于newcomer组放得下,对于k人桌，下一个可用座位的位置是[available()-1, specific_available(available()-1)]
		
		//更新tables状态
		int tablenum = specific_available(tablesiz);
		tables[tablesiz - 1][tablenum].sitin(newcomer);
#ifdef DEBUG
		cout << globaltime << ", "<< setw(3) << setfill('0') <<tables[tablesiz - 1][tablenum].dinnerid() <<" 入座" << char(tablesiz - 1 + 'a') << tablenum << endl;
#endif
		//更新bill
		bill.push_back(tables[tablesiz - 1][tablenum].dinner);
	}
	return 1;
}


bool cmp_id(const customer_info& a, const customer_info& b)
{
	return a.id < b.id;
}
void Restaurant::orderbill()
{
	sort(bill.begin(), bill.end(), cmp_id);
}
