#pragma once
#include<iostream>
#include<iomanip>

class resclock
{
public:
	int current;
	resclock(): current(0){}
	resclock(int v):current(v){}
	resclock(int a, int b);
	void update()	//����Ӽ�����Ҫ�ǵ�update()
	{
		while (current < 0) 
			current += 1440;
		current = current % 1440;
	}
	
	int print();
	bool operator<(const resclock& a) const
	{ 
		//��Ϊ����ʱ��11:00-23:59;�賿ʱ��0:00-2:00
		//����ʱ�������賿ʱ��
		if (current >= 660 && a.current <= 120)	return 1;
		return current < a.current;
	}
	bool operator==(const resclock& a) const
	{ return current == a.current;}
	bool operator>(const resclock& a) const
	{ return !operator<(a) && !operator==(a);}
	bool operator<=(const resclock& a) const
	{ return !operator>(a);}
	bool operator>=(const resclock& a) const
	{ return !operator<(a);}
};
extern resclock globaltime;
