#include<iostream>
#include<fstream>
#include"Restaurant.h"
using namespace std;
#define DEBUG

//��ʼ��ʱ��
resclock starttime(11, 0);
resclock globaltime = starttime;	//11�㿪��
#ifdef DEBUG
resclock endtime(11, 10);	//11��10�ֹ���
#else
resclock endtime(2, 0);	//2�����
#endif

//��ʼ��δ������
int Restaurant::nextid = 1;

int main() {
	ifstream infiletable("input_table.txt");
	ifstream infilecustomer("input_customer.txt");
	ofstream outfiledata("output_data.txt");
	ofstream outfilecustomer("output_customer.txt");
	
	Restaurant restaurant(infiletable, infilecustomer);

	for (; globaltime <= endtime; globaltime++)
	{
		restaurant.update_table_avail();
		restaurant.dine();
	}

	restaurant.output1(outfiledata);
	restaurant.output2(outfiledata);
	restaurant.output3(outfilecustomer);
#ifdef DEBUG
	cout << "<outfiledata>: " << endl;
	restaurant.output1(cout);
	restaurant.output2(cout);
	cout << "<outfilecustomer>: " << endl;
	restaurant.output3(cout);				//��Ȼcout�����Ǵ�λ�ģ��������ļ�����û�������
#endif // DEBUG
	


	return 0;
}
