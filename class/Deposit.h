#pragma once
#include <string>
#include "Date.h"

using namespace std;

class Deposit
{
public:
	Deposit();
	Deposit(string userAccount, int type, int principal, Date date);
	virtual ~Deposit();

	/*
	���������ݽ��б��棬����id���ڵ��Ӵ��ڣ���������±���
	*/
	bool save();
	/*
	���ݵ�ǰ����id��ѯ���ӣ������������
	*/
	bool readData();
	/*
	��ѯ�Ƿ��д���idֵ�ĵ��Ӵ���
	*/
	bool isExist(int id);
	/*
	�����˻��Ƿ����ȡ��;
	*/
	bool checkCanBeTake();
	/*
	��ȡ�����쵽�ڴ��
	*/
	int getRecentEndDepoist(Date now);
	/*
	���㵱����Ҫת������ж��ڣ����ҽ��ڶ�����Ҫ׼���Ľ����㷵��
	���أ� ��������ǰ׼�����
	*/
	int settlement(Date now);
	/*
	���㵱ǰ���е��ӵ���Ϣֵ
	*/
	int countProfit();
	int getID();
	void setID(int id);
	string getUserAccount();
	void setUserAccount(int userid);
	int getType();
	void setType(int type);
	int getPrincipal();
	void setPrincipal(int principle);
	Date getDate();
	void setDate(Date date);
	int getTakeTimes();
	void setTakeTimes(int takeTimes);

protected:
	int id;
	string userAccount;
	int type;
	int principal;
	Date date;	
	int takeTimes;
};

