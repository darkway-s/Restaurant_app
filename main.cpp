#include<iostream>
#include<fstream>
#include"Restaurant.h"
using namespace std;
//#define DEBUG

int test() {
	resclock now(11,26);
	cout << now << endl;
	return 0;
}
resclock starttime(11, 0);
resclock globaltime = starttime;	//11�㿪��
#ifdef DEBUG
resclock endtime(11, 10);	//11��10�ֹ���
#else
resclock endtime(2, 0);	//2�����
#endif

int main() {
	ifstream infiletable("input_table.txt");
	ifstream infilecustomer("input_customer.txt");
	ofstream outfiledata("output_data.txt");
	ofstream outfilecustomer("output_customer.txt");
	
	Restaurant restaurant(infiletable, infilecustomer);

#ifdef DEBUG
	test();
#endif //DEBUG
	

	for (; globaltime <= endtime; globaltime++)
	{
		restaurant.update_table_avail();
		restaurant.dine();
	}
#ifdef DEBUG
	cout << "<outfiledata>: " << endl;
	restaurant.output1(cout);
	restaurant.output2(cout);
	cout << "<outfilecustomer>: " << endl;
	restaurant.output3(cout);				//��Ȼcout�����Ǵ�λ�ģ��������ļ�����û�������
#endif // DEBUG

	restaurant.output1(outfiledata);
	restaurant.output2(outfiledata);
	restaurant.output3(outfilecustomer);

	return 0;
}
