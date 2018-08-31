#pragma once
#include <string>
#include "Date.h"

using namespace std;

class Deposit
{
public:
	Deposit();
	Deposit(int userid, int type, int principle, Date date);
	virtual ~Deposit();

	bool save();
	bool isExist(int id);

	int getID();
	void setID(int id);
	int getUserid();
	void setUserid(int userid);
	int getType();
	void setType(int type);
	int getPrinciple();
	void setPrinciple(int principle);
	Date getDate();
	void setDate(Date date);

protected:
	int id;
	int userid;
	int type;
	int principle;
	Date date;	
};

