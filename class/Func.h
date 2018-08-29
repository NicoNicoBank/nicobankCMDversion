#pragma once
#include <string>

using namespace std;
class Func
{
public:
	Func();
	~Func();
	/*
	获取当前工作路径
	*/
	string getPwd();
	/*
	获取数据库位置
	*/
	string getDataBaseLocation();
};
