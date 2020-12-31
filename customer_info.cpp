#include "customer_info.h"
using namespace std;
std::ostream& operator << (std::ostream& output, customer_info& c) //�����������<<�����غ���
{
	resclock wait(c.waitperiod);
	resclock eat(c.eatperiod);
	output << std::setw(3) << std::setfill('0') << c.id << "\t"
		<< c.size << "\t"
		<< c.arrivetime << "\t"
		<< wait << "\t"
		<< c.startime << "\t"
		<< eat << "\t"
		<<c.departime << endl;
	return output;
}