// NicoNicoBankWindowsVersion.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "Staff.h"
#include "User.h"
#include "Func.h"
using namespace std;
int staffStatu, userStatu;
int menu();
bool checkStatu();
int main()
{
	Func func;
	cout << "欢迎登入NicoNicobank" << endl;
	Staff sta("你好", "123", "123");
	sta.save();
	sta.setID(2);
	sta.readData();
	//cout << errorMessage << endl;
	while (1) {
		cout << "请输入工作号：";
		string jobNumber;
		cin >> jobNumber;
		cout << "请输入密码:";
		string password;
		cin >> password;
		Staff staff("", jobNumber, password);
		string errorMessage;
		if (staff.verify(&errorMessage)) {
			cout << "欢迎回来,";
			cout << staff.getName() << endl;
			staffStatu = 1;
			int opt = 0;
			while (opt = menu()) {
				User user;
				string account, pwd,strTemp;
				if (staffStatu == 0) {
					cout << "请先登入" << endl;
					break;
				}
				switch (opt) {
				//登入
				case 1:
					cout << "请输入用户账户" << endl;
					cin >> account;
					cout << "请输入密码" << endl;
					cin >> pwd;
					if (!user.verify(account, pwd)) {
						cout << "用户账户密码错误" << endl;
						break;
					}
					cout << "欢迎回来"<< user.getUserName() << endl;
					break;

				//注册
				case 2:
					cout << "输入希望的用户账户(需要自动生成请输入0)" << endl;
					user.setId(-1);
					cin >> strTemp;
					if (strTemp == "0" || strTemp == "") {
						while (1) {
							strTemp = func.getRandomstring(5);
							if (!user.isExist(strTemp)) break;
						}
					}
					else {
						while (1) {
							if (!user.isExist(strTemp)) break;
							cout << "账户已被使用,请再次输入" << endl;
							cin >> strTemp;
						}
					}
					cout << "账户为：" << strTemp << endl;
					user.setAccount(strTemp);
					cout << endl;

					cout << "输入密码(若密码输入为0则重置用户名)：";
					cin >> pwd;
					while (pwd == "0") {
						while (1) {
							strTemp = func.getRandomstring(5);
							if (!user.isExist(strTemp)) break;
						}
						cout << "账户为：" << strTemp << endl;
						user.setAccount(strTemp);
						cout << "输入密码(若密码输入为0则重置用户名)：";
						cin >> pwd;
					}
					
					user.setPassword(pwd);
					cout << endl;

					cout << "输入地址：";
					cin >> strTemp;
					user.setAddress(strTemp);
					cout << endl;

					cout << "输入身份证号：";
					cin >> strTemp;
					user.setIDNumber(strTemp);
					cout << endl;

					cout << "输入姓名" << endl;
					cin >> strTemp;
					user.setUserName(strTemp);
					cout << endl;

					user.initDate();
					user.save();
					cout << "注册成功" << endl;
					break;
				case 3:
					cout << "请输入查询用户账户" << endl;
					cin >> account;
					user.print(account);
					break;
				default:
					staffStatu = 0;
					userStatu = 0;
				}
			}
		}
		else {
			if (errorMessage == "") {
				cout << "用户名或密码错误" << endl;
			}
			else {
				cout << "出现错误,错误信息如下" << endl;
				cout << errorMessage << endl;
			}
			continue;
		}
	}
	getchar();
	getchar();
	getchar();
}

int menu() {
	int opt;
	cout << "0.退出\
	1.用户登入\
	2.用户注册\
	3. 查询存取款情况\
	4.存款\
	5.取款" << endl;
	cin >> opt;
	return opt;
}


bool checkStatu() {
	if (staffStatu&&userStatu)
		return false;
	return true;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
