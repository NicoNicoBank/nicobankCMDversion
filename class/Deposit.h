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
	对类中内容进行保存，若该id所在单子存在，则仅仅更新本金
	*/
	bool save();
	/*
	根据当前类中id查询单子，并存入该类中
	*/
	bool readData();
	/*
	查询是否有传入id值的单子存在
	*/
	bool isExist(int id);
	/*
	检测该账户是否可以取款;
	*/
	bool checkCanBeTake();
	/*
	获取近三天到期存款
	*/
	int getRecentEndDepoist(Date now);
	/*
	结算当日需要转存的所有定期，并且将第二天需要准备的金额计算返回
	返回： 明日需提前准备金额
	*/
	int settlement(Date now);
	/*
	计算当前类中单子的利息值
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

