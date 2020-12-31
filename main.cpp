#include<iostream>
#include<fstream>
#include"Restaurant.h"
using namespace std;
#define DEBUG

int test() {
	resclock now(11,26);
	cout << now;
	return 0;
}
resclock starttime(11, 0);
resclock globaltime = starttime;	//11点开门
#ifdef DEBUG
resclock endtime(11, 10);	//11点10分关门
#else
resclock endtime(2, 0);	//2点关门
#endif

int main() {
	ifstream infiletable("input_table.txt");
	ifstream infilecustomer("input_customer.txt");
	ofstream outfiledata("output_data.txt");
	ofstream outfilecustomer("output_customer.txt");
	
	Restaurant restaurant(infiletable, infilecustomer);

#ifdef DEBUG
	test();
#endif
	

	for (; globaltime <= endtime; globaltime++)
	{
		restaurant.dine();
	}
	restaurant.output1(outfiledata);
	restaurant.output2(outfiledata);
	restaurant.output3(outfilecustomer);

	return 0;
}

#undef DEBUG