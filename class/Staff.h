#pragma once
#include <string>
using namespace std;
//����Ա
class Staff
{
public:
	Staff();
	Staff(string name, string jobNumber, string password, int id = -1);
	~Staff();
	bool read(string * errorMessage, string query="id");
	bool save(string * errorMessage);
	/*
	��֤��ȷ����true, ��֤���󷵻�false,����errorMessgeΪ""
	���ݿ���󷵻�false, erroMessage;
	*/
	bool verify(string * errorMessage);

	string getName();
private:
	int id;
	string name; //����
	string jobNumber; // ����
	string password; //staff����
};

