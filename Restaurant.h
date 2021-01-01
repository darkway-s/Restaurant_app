#pragma once
#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include "table.h"
#include "customer_info.h"

const int MAX_VOLUME = 16;	//�����������16����

class priorder //��д�º���
{
public:
	bool operator() (customer_info a, customer_info b)	//С����
	{
		if (a.arrivetime > b.arrivetime)
			return 1;
		else if (a.arrivetime == b.arrivetime)
		{
			return a.size > b.size;
		}
		else
			return 0;
	}
};

class Restaurant
{	
private:
	std::vector<std::vector<table>> tables;	//tables[3][2]��ʾ4�����ĵڶ�����������D2
	std::vector<customer_info> bill;
	std::priority_queue<customer_info, std::vector<customer_info>, priorder> wait_section;
public:
	Restaurant(std::istream& intable, std::istream& incustomer);	//��ʼ��tables��wait_section
	int specific_available(int k = 1);	//k�����Ƿ���ã����ؿ���λ��(�����÷���-1)
	int available(int k = 1);	//k�����ϵ����Ƿ���ã����ؿ��õ�����С���緵��m����ʾm��������
	//����k��������һ��������λ��λ����[available()-1, specific_available(available()-1)]
	bool Iswaiting();	//�ȴ����������Ŷ�
	void update_table_avail();	//��������table��avail״̬

	int dine();	//�õ�λ���Ĺ˿��������ɹ�����1��ʧ�ܷ���0��������Ϣ���µ�bill��

	void output1(std::ostream&);
	void output2(std::ostream&);
	void output3(std::ostream&);
};

