#include<iostream>
#include<fstream>
#include"Restaurant.h"
using namespace std;


int test() {
	resclock now(11,26);
	now.print();
	return 0;
}

int main() {
	ifstream infiletable("input_table.txt");
	ifstream infilecustomer("input_customer.txt");
	ofstream outfiledata("output_data.txt");
	ofstream outfilecustomer("output_customer.txt");
	
	Restaurant restaurant(infiletable, infilecustomer);
	
	test();

	return 0;
}
