#pragma once
#include <string>
#include "Date.h"

using namespace std;

class Deposit
{
public:
	Deposit();
	Deposit(int userid, string type, int principle, Date date);
	virtual ~Deposit();
protected:
	int userid;
	string type;
	int principle;
	Date date;	
};

