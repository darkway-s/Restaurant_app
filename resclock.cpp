#include "resclock.h"

resclock::resclock(int a, int b) 
{ current = a * 60 + b; }

int resclock::print()
{
	if (current < 0 || current > 1440)
	{
		std::cout << "Invalid clock.";
		return 1;
	}
	int hour = current / 60;
	int minute = current % 60;
	std::cout << std::setw(2) << std::setfill('0') << hour << ":"
		<< std::setw(2) << std::setfill('0') << minute;
	return 0;
}

resclock globaltime(11, 0);
