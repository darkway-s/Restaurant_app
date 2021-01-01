#pragma once
#include<iostream>
#include<iomanip>

class resclock
{
	friend std::ostream& operator << (std::ostream& output, resclock& c); //�����������<<�����غ���
	friend resclock operator + (resclock c, int period);	//"+"
	friend class table;
private:
	int current;
public:
	resclock(): current(0){}
	resclock(int v) :current(v) { update(); }
	resclock(int a, int b) { current = a * 60 + b; update(); }
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
		//�賿ʱ����������ʱ��
		if (current <= 120 && a.current >= 660)	return 0;
		//ͬһʱ�������Ƚ�
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
		update();
		return *this;
	}
	resclock operator++(int)
	{
		resclock temp = *this;
		current++;
		update();
		return temp;
	}
	resclock operator+=(int period)
	{
		current += period;
		update();
		return *this;
	}
};

std::ostream& operator << (std::ostream& output, resclock& c); //�����������<<�����غ���
resclock operator + (resclock c, int period);	//"+"

extern resclock globaltime;
extern resclock starttime;
extern resclock endtime;
