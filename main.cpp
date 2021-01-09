#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include"Restaurant.h"
using namespace std;
//#define DEBUG
//#define RAND
//#define COUNTDOWN
//初始化时间
resclock starttime(11, 0);	//11点开门
resclock globaltime = starttime;	
resclock endtime(1, 30);	//2点0分关门， 1点30打烊

//今日customer数量
const int sum_customer = 200;
//随机数种子
unsigned seed = (unsigned int)time(NULL);

/*input_customer1.txt
2 11:00 0:05
2 11:00 0:05
2 11:01 0:05
1 11:02 0:03
0*/
void randin(ostream& output)	
{
	srand(seed);
	int cus_size, res_current, eatp;
	
	for (int i = 0; i < sum_customer; i++)
	{
		cus_size = rand() % MAX_VOLUME + 1;
		res_current = 660 + rand() % 870;	//660-1529.
		resclock res(res_current);			//11:00 - 25:29.  
		eatp = rand() % 30 + 1;				//eatp <= 30.

		output << cus_size << " " << res << " "
			<< "0:" << setw(2) << setfill('0') << eatp << endl;
	}
	output << 0;
}


int main() {

#ifdef RAND
	ofstream file_writecustomer("input_customer.txt");
	randin(file_writecustomer);	//随机初始化input_customer.txt
	file_writecustomer.close();
#ifdef DEBUG
	randin(cout);
	cout << endl;
#endif // DEBUG
#endif // RAND

	ifstream infiletable("input_table.txt");
	ifstream infilecustomer("input_customer.txt");
	ofstream outfiledata("output_data.txt");
	ofstream outfilecustomer("output_customer.txt");
	
	Restaurant restaurant(infiletable, infilecustomer);
#ifdef COUNTDOWN
	resclock countdown(23, 58);
#endif // COUNTDOWN
	
	for (; globaltime <= endtime; globaltime++)
	{
		restaurant.update_table_avail();
		restaurant.dine();
#ifdef COUNTDOWN
		if (globaltime == countdown)
			cout << "It's the final countdown";
#endif // COUNTDOWN
	}
	
	restaurant.output1(outfiledata);
	restaurant.output2(outfiledata);
	restaurant.output3(outfilecustomer);
#ifdef DEBUG
	cout << "<outfilecustomer>: " << endl;
	restaurant.output3(cout);				//虽然cout出来是错位的，但是在文件里是没有问题的
	cout << "<outfiledata>: " << endl;
	restaurant.output1(cout);
	restaurant.output2(cout);
#endif // DEBUG
	
	infiletable.close();
	infilecustomer.close();
	outfiledata.close();
	outfilecustomer.close();

	return 0;
}
