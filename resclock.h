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
	
	int print();
	bool operator<(const resclock& a) const
	{ return current < a.current; }
	bool operator==(const resclock& a) const
	{ return current == a.current;}
	bool operator>(const resclock& a) const
	{ return current > a.current; }
};
extern resclock globaltime;
