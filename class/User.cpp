#include "User.h"
#include "sqlite3.h"
#include "Func.h"
User::User()
{
}


User::~User()
{
}

User::User(string account, string userName, string password, string address, string IDNumber, Date openDate, bool isLost, Date lostDate, int id)
{
	this->id = id;
	this->account = account;
	this->userName = userName;
	this->password = password;
	this->address = address;
	this->IDNumber = IDNumber;
	this->openDate = openDate;
	this->isLost = isLost;
	this->lostDate = lostDate;
}

bool User::read(string * errorMessage, string query)
{	
	sqlite3 * conn = NULL;
	char * err_msg = NULL;
	char sql[200] = "";
	string sql_temp = "SELECT * From user where "+query+" =  "+ to_string(id);
	if (sqlite3_open("database\\bank.db", &conn) != SQLITE_OK) {
		return false;
	}
	char** result;
	int nrow;
	int ncolumn;
	sqlite3_get_table(conn, sql_temp.c_str(), &result, &nrow, &ncolumn, &err_msg);
	*errorMessage = err_msg;
	if (err_msg != NULL) {
		return false;
	}
	if (nrow == 0) {
		*errorMessage = "不存在该条记录";
		return false;
	}
	this->id = id;
	//读取前5行文本
	string temp(result[1 * ncolumn + 1]);
	this->account = temp;
	temp = result[1 * ncolumn + 2];
	this->userName = temp;
	temp = result[1 * ncolumn + 3];
	this->password = temp;
	temp = result[1 * ncolumn + 4];
	this->address = temp;
	temp = result[1 * ncolumn + 5];
	this->IDNumber = temp;
	//读取日期等数字, 6 7 8为开户日期, 9为是否挂失,10 11 12 为挂失日期
	sqlite3_stmt* stmt = NULL;
	sqlite3_prepare_v2(conn, sql_temp.c_str(), -1, &stmt, 0);
	int resultCode = sqlite3_step(stmt);
	int year = sqlite3_column_int(stmt, 6);
	int month = sqlite3_column_int(stmt, 7);
	int day = sqlite3_column_int(stmt, 8);
	this->openDate.setDate(year, month, day);
	int islost = sqlite3_column_int(stmt, 9);
	this->isLost = islost;
	year = sqlite3_column_int(stmt, 10);
	month = sqlite3_column_int(stmt, 11);
	day = sqlite3_column_int(stmt, 12);
	this->lostDate.setDate(year, month, day);
	sqlite3_finalize(stmt);
	return true;
}

bool User::save(string * errorMessage)
{	
	string sql = "";
	bool flag = false;
	string err_msg;
	if (read(&err_msg) && id != -1) {
		flag = true;
		sql = "update user set account = ?,userName = ?,password = ?,address = ?,IDNumber = ?,openDate_year = ?,openDate_month = ?,openDate_day = ?,isLost = ?,lostDate_year = ?,lostDate_month = ?,lostDate_day = ? where id = ?;";
	}
	else {
		sql = "insert into user (account, userName, password, address, IDNumber, openDate_year,openDate_month, openDate_day, isLost, lostDate_year, lostDate_month, lostDate_day) values  (?,?,?,?,?,?,?,?,?,?,?,?);";
	}
	
	//sqlite3_bind_blob(stat, 1, &(date), sizeof(this->openDate), NULL);
	//sqlite3_bind_int(stmt, 1, id);
	string tempStr[] = { this->account, this->userName, this->password, this->address, this->IDNumber };
	int tempInt[] = { openDate.get(0), openDate.get(1), openDate.get(2), isLost, lostDate.get(0), lostDate.get(1), lostDate.get(2) };
	
	sqlite3 * conn;
	if (sqlite3_open("database\\bank.db", &conn) != SQLITE_OK) {
		*errorMessage = "数据库打开失败";
		return false;
	}
	sqlite3_stmt * stmt = NULL;
	//sql语句准备
	//string sql = "insert into user (account, userName, password, address, IDNumber, openDate_year,openDate_month, openDate_day, isLost, lostDate_year, lostDate_month, lostDate_day) values  (?,?,?,?,?,?,?,?,?,?,?,?);";
	//(id, account, username, password, address, idnumber, opendate_year,opendate_month, opendate_day, islost, lostdate_year, lostdate_month, lostdate_day)
	//填入相关数据
	sqlite3_prepare_v2(conn, sql.c_str(), -1, &stmt, 0);
	for (int i = 1; i <= 5; i++) {
		sqlite3_bind_text(stmt, i, tempStr[i - 1].c_str(), -1, NULL);
	}
	for (int i = 6; i <= 12; i++) {
		sqlite3_bind_int(stmt, i, tempInt[i - 6]);
	}
	if (flag) {
		sqlite3_bind_int(stmt, 13, id);
	}
	//执行
	int result = sqlite3_step(stmt);
	if (result == 101) {
		*errorMessage = "成功读取";
	}
	else if (result == 20) {
		*errorMessage = "数据库操作失败";
	}
	else *errorMessage = "数据读取错误";
	sqlite3_finalize(stmt);
	return false;
}

string User::getAccount()
{
	return string(account);
}

bool User::verifyAccount()
{
	return false;
}


