#include "resclock.h"



std::ostream& operator << (std::ostream& output, resclock& c) //定义运算符“<<”重载函数
{
	if (c.current < 0 || c.current > 1440)
	{
		output << "Invalid clock.";
		return output;
	}
	output << std::setw(2) << std::setfill('0') << c.current / 60 << ":"
		<< std::setw(2) << std::setfill('0') << c.current % 60;
	return output;
}
resclock operator+ (resclock c, int period)	//"+"
{
	c += period;
	return c;
}
