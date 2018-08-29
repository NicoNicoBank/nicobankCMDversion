#include "Staff.h"
#include "sqlite3.h"
#include "Func.h"
#include <iostream>
using namespace std;
Staff::Staff()
{
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

bool Staff::read(string * errorMessage, string query)
{
	sqlite3 * conn = NULL;
	char * err_msg = NULL;
	char sql[200] = "";
	
	string sql_temp = "SELECT * From Staff where " + query + " =  ";
	if (query == "id") {
		sql_temp += to_string(id);
	}
	else if(query == "jobNumber"){
		sql_temp += "\"" + jobNumber + "\"";
	}
	Func func;
	if (sqlite3_open(func.getDataBaseLocation().c_str(), &conn) != SQLITE_OK) {
		*errorMessage = "数据库打开失败";
		return false;
	}
	char** result;
	int nrow;
	int ncolumn;
	sqlite3_get_table(conn, sql_temp.c_str(), &result, &nrow, &ncolumn, &err_msg);
	if (err_msg == NULL) {
		*errorMessage = "";
	}
	else {
		*errorMessage = err_msg;
		return false;
	}
	if (nrow == 0) {
		*errorMessage = "不存在该条记录";
		return false;
	}
	string temp(result[1 * ncolumn + 1]);
	this->jobNumber = temp;
	temp = result[1 * ncolumn + 2];
	this->name = temp;
	temp = result[1 * ncolumn + 3];
	this->password = temp;
	return true;
}

bool Staff::save(string * errorMessage)
{
	string sql = "";
	bool flag = false;
	string err_msg;
	if (read(&err_msg) && id != -1) {
		flag = true;
		sql = "update Staff set jobNumber = ?, name = ? where id = ?;";
	}
	else {
		sql = "insert into Staff (jobNumber, name) values  (?,?);";
	}
	sqlite3 * conn;
	sqlite3_stmt * stmt = NULL;
	if (sqlite3_open("database\\bank.db", &conn) != SQLITE_OK) {
		*errorMessage = "数据库打开失败";
		return false;
	}
	sqlite3_prepare_v2(conn, sql.c_str(), -1, &stmt, 0);
	sqlite3_bind_text(stmt, 1, this->jobNumber.c_str(), -1, NULL);
	sqlite3_bind_text(stmt, 2, this->name.c_str(), -1, NULL);
	//执行
	int result = sqlite3_step(stmt);
	if (result == 101) {
		*errorMessage = "成功读取";
	}
	else if (result == 20) {
		*errorMessage = "数据库操作失败";
	}
	else {
		*errorMessage = "数据读取错误";
	}
	sqlite3_finalize(stmt);
	return false;
}

bool Staff::verify(string * errorMessage)
{
	string enterJobNumber = this->jobNumber;
	string enterPassword = this->password;
	string query = "jobNumber";
	if (!read(errorMessage, query)) {
		return false;
	}
	if (this->password == enterPassword) {
		return true;
	}
	else *errorMessage = "";
	return false;
}

string Staff::getName()
{
	return string(name);
}


