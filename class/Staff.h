#pragma once
#include <string>
using namespace std;
//储蓄员
class Staff
{
public:
	Staff();
	Staff(string name, string jobNumber, string password, int id = -1);
	~Staff();
	bool read(string * errorMessage, string query="id");
	bool save(string * errorMessage);
	/*
	验证正确返回true, 验证错误返回false,并且errorMessge为""
	数据库错误返回false, erroMessage;
	*/
	bool verify(string * errorMessage);

	string getName();
private:
	int id;
	string name; //姓名
	string jobNumber; // 工号
	string password; //staff密码
};

