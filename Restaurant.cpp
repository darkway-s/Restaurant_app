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
	int k, num;	//k�����ĸ���Ϊnum
	table newtable;
	vector<table> newrow;
	intable >> num;
	for (; num != 0; intable >> num)
	{
		intable >> k;
		//k <= 0������ݲ�����
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
		incustomer.ignore(3, ':');	//ignore(2, ':')��ignore(3)������
		incustomer >> eatp;

		resclock arriv(arriv_hour, arriv_minute);
		customer_info newcustomer(siz, arriv, eatp);
		wait_section.push(newcustomer);

		incustomer >> siz;
	}
	//����id
	stack<customer_info> s;	//����ջs�洢��ʷ����
	customer_info dinner;	//dinnerΪ��ǰ�˿�
	while (!wait_section.empty())
	{
		//ȡ��
		dinner =  wait_section.top();
		wait_section.pop();
		//����
		dinner.id = nextid++;
		//�Ż�
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
void Restaurant::output1(std::ostream& outdata)	//һ����������˿��ڷ����ƽ��ͣ��ʱ�䡢ƽ����λʱ�䡣ע��һ��˿͵�ͣ��ʱ��=��λʱ��+�Ͳ�ʱ�䣻
{
	int n = bill.size();	//�˿�����
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

	
	outdata << "ƽ��ͣ��ʱ��: " << avgstay << " min" << endl;
	outdata << "ƽ����λʱ��: " << avgwait << " min" << endl;
}

void Restaurant::output2(std::ostream& outdata)
{
	resclock lastdepart = starttime;
	int n = bill.size();	//�˿�����
	for (int i = 0; i < n; i++)
	{
		if (bill[i].departime >= lastdepart)
			lastdepart = bill[i].departime;
	}
	outdata << "���һ���뿪����Ĺ˿͵��뿪ʱ��: " << lastdepart << endl;
}
void Restaurant::output3(std::ostream& outcustomer)
{
	orderbill(); //����������˵�
	outcustomer << "���" << "\t" << "�˿�����" << "\t" << "����ʱ��" << "\t"
		<< "�ȴ���ʱ" << "\t" << "�Ͳ�ʱ��" << "\t" << "�Ͳ���ʱ" << "  \t" << "�뿪ʱ��" << endl;
	int n = bill.size();	//�˿�����
	for (int i = 0; i < n; i++)
		outcustomer << bill[i];
}

//functions
int Restaurant::specific_available(int k)	//����tables[k-1]���������һ����λ���ã��Ϳ�����λ�ĺ���,���򷵻�-1
{
	if (k <= 0)	return -1;	//����0�������϶���û�е�

	typedef vector<table>::size_type vecsize;
	vecsize siz = tables[k - 1].size();
	for (vecsize i = 0; i < siz; i++)
	{
		if (tables[k - 1][i].available())
			return i;
	}
	return -1;
}
int Restaurant::available(int k)	//����m>=k��ʹ��m�������ã�����m�����򷵻�0��
{	//k<=0ʱ�����ͬk = 1��
	for (int i = k; i <= MAX_VOLUME; i++)
	{
		if (specific_available(i) != -1)
			return i;
	}
	return 0;
}
bool Restaurant::Iswaiting()
{
	//�ڵ�ǰʱ�̣��������Ŷӣ����ҵ�ǰ���׵���ʱ�����ڵ�ǰʱ��
	return !wait_section.empty() && wait_section.top().arrivetime <= globaltime;
}
void Restaurant::update_table_avail()
{
	//��������table���������ǵ�avail״̬
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

int Restaurant::dine()	//��ǰʱ��Ϊȫ�ֱ���globaltime
{
	if (available() && Iswaiting() == 0)	return 0;
	while (available() && Iswaiting())	//�����п�λ�������ڵ�
	{
		//����һ��˿�����
		customer_info newcomer = wait_section.top();
		wait_section.pop();
		int k = newcomer.size;
		int tablesiz = available(k);
		if (tablesiz == 0)	//�������п��õ�λ�˿ͣ��ҵ�available��һ�������û�У�ֱ��return 0������������
		{
			stack<customer_info> s;	//s��¼�Ѿ��������ĵ�λ����
			s.push(newcomer);
			while (Iswaiting() && tablesiz == 0)	//����ʣ��
			{
				newcomer = wait_section.top();
				wait_section.pop();
				s.push(newcomer);					//�߳��߽�
				k = newcomer.size;
				tablesiz = available(k);
			}
			//�ҵ���һ��ʹ��tablesiz��Ϊ0�Ĺ˿�newcomer
			if (tablesiz != 0)						
				s.pop();							//������ȷ��newcomer���Ͳ��ûָ���wait_section����
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
		
		//����newcomer��ŵ���,����k��������һ��������λ��λ����[available()-1, specific_available(available()-1)]
		
		//����tables״̬
		int tablenum = specific_available(tablesiz);
		tables[tablesiz - 1][tablenum].sitin(newcomer);
#ifdef DEBUG
		cout << globaltime << ", "<< setw(3) << setfill('0') <<tables[tablesiz - 1][tablenum].dinnerid() <<" ����" << char(tablesiz - 1 + 'a') << tablenum << endl;
#endif
		//����bill
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
