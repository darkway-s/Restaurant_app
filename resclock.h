#pragma once
#include<iostream>
#include<iomanip>

class resclock
{
	friend std::ostream& operator << (std::ostream& output, resclock& c); //�����������<<�����غ���
private:
	int current;
public:
	resclock(): current(0){}
	resclock(int v):current(v){}
	resclock(int a, int b);
	void update()	//����Ӽ�����Ҫ�ǵ�update()
	{
		while (current < 0)
			current += 1440;
		current = current % 1440;
	}
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
	resclock operator++()
	{
		current++;
		return *this;
	}
	resclock operator++(int)
	{
		resclock temp = *this;
		current++;
		return temp;
	}
};

std::ostream& operator << (std::ostream& output, resclock& c); //�����������<<�����غ���

extern resclock globaltime;
extern resclock starttime;
extern resclock endtime;
