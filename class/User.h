#pragma once
#include <string>
#include <cstring>
#include "Date.h"
#include <windows.h>
using namespace std;
class User
{
public:
	User();
	~User();
	/*
	Date类初始化不能小于0，会变成错误数值
	*/
	User(string account, string userName, string password, string address, string IDNumber, Date openDate, bool isLost, Date lostDate, int id=-1);
	/*
	根据当前id值读取所有该id值下的user表中的数据,query是所查询的字段名,默认为id
	仅支持account, IDNumber 和 id
	*/
	bool read(string * errorMessage, string query = "id");
	/*
	将当前类中数据写入数据库, id存在则为更新，id为-1则表示更新
	*/
	bool save(string * errorMessage);
	string getAccount();
	bool verifyAccount();
private:
	int id;  //唯一标识
	string account; // 账号
	string userName;  // 姓名
	string password; // 密码
	string address;// 地址
	string IDNumber;// 身份证号码
	Date openDate;// 开户日期
	bool isLost;// 是否挂失
	Date lostDate;// 挂失日期

};

