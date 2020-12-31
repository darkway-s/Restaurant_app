#include "Restaurant.h"
using namespace std;

//input
/***
* input_customer.txt
1 11:00 0:02
1 11:05 0:03
0
* input_table.txt
4 1
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
		int eatp = ins[8] * 60 + ins[10] + 10 + ins[11];
		customer_info newcustomer(siz, arriv, eatp);
		wait_section.customers.push(newcustomer);
	} 
}

//output
void Restaurant::output1(std::ostream& outdata)	//һ����������˿��ڷ����ƽ��ͣ��ʱ�䡢ƽ����λʱ�䡣ע��һ��˿͵�ͣ��ʱ��=��λʱ��+�Ͳ�ʱ�䣻
{
	int n = bill.customers.size();	//�˿�����
	int sumwait = 0, sumstay = 0,  sumdine = 0;
	double avgwait = 0, avgstay = 0, avgdine = 0;
	for (int i = 0; i < n; i++)
	{
		sumwait += bill.customers[i].waitperiod;
		sumdine += bill.customers[i].eatperiod;
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
	int n = bill.customers.size();	//�˿�����
	for (int i = 0; i < n; i++)
	{
		if (bill.customers[i].departime >= lastdepart)
			lastdepart = bill.customers[i].departime;
	}
	outdata << "���һ���뿪����Ĺ˿͵��뿪ʱ��: " << lastdepart << endl;
}
void Restaurant::output3(std::ostream& outcustomer)
{
	outcustomer << "���" << "\t" << "�˿�����" << "\t" << "����ʱ��" << "\t"
		<< "�ȴ���ʱ" << "\t" << "�Ͳ�ʱ��" << "\t" << "�Ͳ���ʱ" << "\t" << "�뿪ʱ��" << endl;
	int n = bill.customers.size();	//�˿�����
	for (int i = 0; i < n; i++)
		outcustomer << bill.customers[i];
}

//functions
int Restaurant::specific_available(int k)	//����tables[k-1]���������һ����λ���ã��Ϳ�����λ�ĺ���,���򷵻�-1
{
	typedef vector<table>::size_type vecsize;
	vecsize siz = tables[k - 1].size();
	for (vecsize i = 0; i < siz; i++)
	{
		if (tables[k - 1][i].available())
			return i;
	}
	return -1;
}
int Restaurant::available(int k)	//����m>=k��ʹ��m�������ã�����m�����򷵻�0
{
	for (int i = k; i <= MAX_VOLUME; i++)
	{
		if (available(i) != -1)
			return i;
	}
	return 0;
}
int Restaurant::dine()	//��ǰʱ��Ϊȫ�ֱ���globaltime
{
	return 0;
}

