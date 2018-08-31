#include "Staff.h"
#include "sqlite3.h"
#include "CppSQLite3.h"
#include "Func.h"
#include "md5.h"
#include <iostream>
using namespace std;
Staff::Staff()
{
	this->id = -1;
	this->jobNumber = "";
	this->name = "";
	this->password = "";
}

Staff::Staff(string name, string jobNumber, string password, int id)
{
	this->name = name;
	this->jobNumber = jobNumber;
	this->password = password;
	this->id = id;
}


Staff::~Staff()
{
}

bool Staff::readData(string query)
{
	Func func;
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	string sql_temp = "select * from staff where " + query + " =  ";
	if (query == "id") {
		sql_temp += to_string(id);
		sql_temp += ";";
	}
	else if (query == "jobNumber") {
		sql_temp += "\"" + jobNumber + "\";";
	}
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	if (q.fieldValue(1) == NULL)
		this->jobNumber = "";
	else
		this->jobNumber = q.fieldValue(1);
	if (q.fieldValue(2) == NULL)
		this->password = "";
	else
		this->password = q.fieldValue(2);
	if (q.fieldValue(3) == NULL)
		this->name = "";
	else {
		string temp = q.fieldValue(3);
		this->name = func.UTF_82ASCII(temp);
	}
	db.close();
	return true;
}

//bool Staff::read(string query)
//{
//	Func func;
//	CppSQLite3DB db;
//	db.open(func.getDataBaseLocation().c_str());
//	string sql_temp = "select * from staff where " + query + " =  ";
	/*if (query == "id") {
		sql_temp += to_string(id);
	}
	else if (query == "jobnumber") {
		sql_temp += "\"" + jobNumber + "\"";
	}
	CppSQLite3Query q = db.execQuery(sql_temp.c_str());
	this->jobNumber = q.fieldValue(1);
	cout << jobNumber;

	db.close();*/
//	/*sqlite3 * conn = null;
//	char * err_msg = null;
//	char sql[200] = "";
//	
//	string sql_temp = "select * from staff where " + query + " =  ";
//	if (query == "id") {
//		sql_temp += to_string(id);
//	}
//	else if(query == "jobnumber"){
//		sql_temp += "\"" + jobnumber + "\"";
//	}
//	func func;
//	if (sqlite3_open(func.getdatabaselocation().c_str(), &conn) != sqlite_ok) {
//		*errormessage = "数据库打开失败";
//		return false;
//	}
//	char** result;
//	int nrow;
//	int ncolumn;
//	sqlite3_get_table(conn, sql_temp.c_str(), &result, &nrow, &ncolumn, &err_msg);
//	if (err_msg == null) {
//		*errormessage = "";
//	}
//	else {
//		*errormessage = err_msg;
//		return false;
//	}
//	if (nrow == 0) {
//		*errormessage = "不存在该条记录";
//		return false;
//	}
//	string temp(result[1 * ncolumn + 1]);
//	this->jobnumber = temp;
//	cout << result[1 * ncolumn + 2] << endl;
//	temp = result[1 * ncolumn + 3];
//	temp = func.utf_82ascii(temp);
//	this->name = temp;
//	temp = result[1 * ncolumn + 2];
//	this->password = temp;
//	return true;*/
//}

bool Staff::save()
{
	Func func;
	string sql = "";
	bool flag = false;
	string err_msg;
	if (id != -1) {
		flag = true;
		sql = "update Staff set ";
		sql += "jobNumber = '" + this->jobNumber + "',";
		sql += "name = '" + this->name +"',";
		sql += "password = '" + this->password + "' ";
		sql += "where id = " + to_string(this->id) + ";";

	}
	else {
		sql = "insert into Staff (jobNumber, name, password) values ";
		sql += "('" + this->jobNumber + "','" + this->name + "','" + MD5(this->password).toStr() + "');";
	}
	CppSQLite3DB db;
	db.open(func.getDataBaseLocation().c_str());
	db.execDML(sql.c_str());
	db.close();
	//sqlite3 * conn;
	//sqlite3_stmt * stmt = NULL;
	//if (sqlite3_open(func.getDataBaseLocation().c_str(), &conn) != SQLITE_OK) {
	//	*errorMessage = "数据库打开失败";
	//	return false;
	//}
	//sqlite3_prepare_v2(conn, sql.c_str(), -1, &stmt, 0);
	//sqlite3_bind_text(stmt, 1, this->jobNumber.c_str(), -1, NULL);
	//sqlite3_bind_text(stmt, 2, func.ASCII2UTF_8(this->name).c_str(), -1, NULL);
	////sqlite3_bind_text(stmt, 3, func.ASCII2UTF_8(this->password).c_str(), -1, NULL);
	////执行
	//
	//int result = sqlite3_step(stmt);
	//if (result == 101) {
	//	*errorMessage = "成功读取";
	//}
	//else if (result == 20) {
	//	*errorMessage = "数据库操作失败";
	//}
	//else {
	//	*errorMessage = "数据读取错误";
	//}

	//cout << id << endl;
	//cout << name << endl;

	//sqlite3_finalize(stmt);

	//
	//return false;
}

bool Staff::verify(string * errorMessage)
{
	string enterJobNumber = this->jobNumber;
	string enterPassword = this->password;
	if (!readData("jobNumber")) {
		return false;
	}
	if (this->password == MD5(enterPassword).toStr()) {
		return true;
	}
	else *errorMessage = "";
	return false;
}

void Staff::setID(int id)
{
	this->id = id;
}

int Staff::getId() {
	return id;
}

void Staff::setId(int _id) {
	id = _id;
}

string Staff::getName() {
	return name;
}

void Staff::setName(string _name) {
	name = _name;
}

string Staff::getJobNumber() {
	return jobNumber;
}

void Staff::setJobNumber(string _jobNumber) {
	jobNumber = _jobNumber;
}

