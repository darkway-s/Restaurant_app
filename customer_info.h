#pragma once
#include"resclock.h"
class clock;
class customer_info
{
	friend class table;
	friend class priorder;
private:
	int id;					//���
	int size;				//�˿�����
	resclock arrivetime;	//����ʱ��
	int waitperiod;			//�ȴ���ʱ
	resclock startime;		//�Ͳ�ʱ��
	int eatperiod;			//�Ͳ���ʱ
	resclock departime;		//�뿪ʱ��
public:
	customer_info(): id(0), size(0), arrivetime(0), waitperiod(0),startime(0),eatperiod(0),departime(0){}
	customer_info(int siz, resclock arriv, int eatp):id(0), size(siz), arrivetime(arriv), waitperiod(0), startime(0), eatperiod(eatp), departime(0){}
};

