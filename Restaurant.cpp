#include "Restaurant.h"
using namespace std;
/***
* input_customer.txt
1 11:00 0:10
1 11:30 0:20
0
* input_table.txt
4 1
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
		int eatp = ins[8] * 60 + ins[10] + 10 + ins[11];
		customer_info newcustomer(siz, arriv, eatp);
		wait_section.customers.push(newcustomer);
	} 

}