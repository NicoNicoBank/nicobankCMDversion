#pragma once
#include "Deposit.h"
class FixedDeposit :
	public Deposit
{
public:
	FixedDeposit();
	~FixedDeposit();
	void draw();
	void save();
private:
	static int timeCounter;
};

