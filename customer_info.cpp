#include "customer_info.h"
using namespace std;
std::ostream& operator << (std::ostream& output, customer_info& c) //定义运算符“<<”重载函数
{
	output << std::setw(3) << std::setfill('0') << c.id << "\t"
		<< "    " << c.size << "\t\t"
		<< "  " << c.arrivetime << "\t\t"
		<< "  " << c.waitperiod/60 << ":" << setw(2) << std::setfill('0') <<c.waitperiod % 60 << "\t\t"
		<< "  " << c.startime << "\t\t"
		<< "  " << c.eatperiod / 60 << ":" << setw(2) << std::setfill('0') << c.eatperiod % 60 << "\t\t"
		<< "  " << c.departime << endl;
	return output;
}