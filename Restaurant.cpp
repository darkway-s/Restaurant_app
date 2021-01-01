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
	avgstay = sumstay / n;
	avgwait = sumwait / n;

	
	outdata << "ƽ��ͣ��ʱ��: " << avgstay << "��" << endl;
	outdata << "ƽ����λʱ��: " << avgwait << "��" << endl;
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
	outcustomer << "���" << "\t" << "�˿�����" << "\t" << "����ʱ��" << "\t"
		<< "�ȴ���ʱ" << "\t" << "�Ͳ�ʱ��" << "\t" << "�Ͳ���ʱ" << "\t" << "�뿪ʱ��" << endl;
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
	while (available() && Iswaiting())	//�����п�λ�������ڵ�
	{
		//��������
		customer_info newcomer = wait_section.top();
		int k = newcomer.size;
		int tablesiz = available(k);
		if (tablesiz == 0)//�����������,�����Ż����� TODO
		{
			return 0;
		}
		else	//����newcomer��ŵ���,����k��������һ��������λ��λ����[available()-1, specific_available(available()-1)]
		{
			//����id
			newcomer.id = nextid++;
			//���µȴ���
			wait_section.pop();
			//����tables״̬
			int tablenum = specific_available(tablesiz);
			tables[tablesiz - 1][tablenum].sitin(newcomer);
#ifdef DEBUG
			cout << globaltime << ", ����" << tablesiz << "���� " << tablenum << "����" << endl;
#endif
			//����bill
			bill.push_back(tables[tablesiz - 1][tablenum].dinner);
		}
	}
	return 0;
}
