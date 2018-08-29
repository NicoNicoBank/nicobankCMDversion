#include "Func.h"
#include <direct.h>


Func::Func()
{
}


Func::~Func()
{
}

string Func::getPwd()
{
	char buff[1000];
	_getcwd(buff, 1000);
	string pwd = buff;
	return pwd;
}

string Func::getDataBaseLocation()
{
	string pwd = getPwd();
	pwd += "\\..\\database\\bank.db";
	return pwd;
}
