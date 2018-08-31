#include "Deposit.h"
#include "CppSQLite3.h"
#include "Func.h"
Deposit::Deposit()
{
	this->userid = -1;
	this->type = 0;
	this->principle = 0;
	this->date = 0;
}

Deposit::Deposit(int userid, int type, int principle, Date date)
{
	this->userid = userid;
	this->type = type;
	this->principle = principle;
	this->date = date;
}


Deposit::~Deposit()
{
}

bool Deposit::save()
{
	if (this->isExist(this->id)) {

	}
	else {
		string sql = "insert into Deposit (userid, type, principal, year, month, day) values (";
		sql += 
	}
	return false;
}

bool Deposit::isExist(int id)
{
	Func func;
	string sql = "select * from Deposit where id = " + id + ';';
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	CppSQLite3Query q = db.execQuery(sql.c_str());
	if (q.eof()) return false;
	return true;
}

int Deposit::getID()
{
	return id;
}

void Deposit::setID(int id)
{
	this->id = id;
}

int Deposit::getUserid() {
	return userid;
}

void Deposit::setUserid(int _userid) {
	userid = _userid;
}

int Deposit::getType() {
	return type;
}

void Deposit::setType(int _type) {
	type = _type;
}

int Deposit::getPrinciple() {
	return principle;
}

void Deposit::setPrinciple(int _principle) {
	principle = _principle;
}

Date Deposit::getDate() {
	return date;
}

void Deposit::setDate(Date _date) {
	date = _date;
}


