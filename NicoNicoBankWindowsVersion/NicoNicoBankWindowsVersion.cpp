// NicoNicoBankWindowsVersion.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Staff.h"
#include "User.h"
#include "Func.h"
#include "Deposit.h"
#include <fstream>
using namespace std;

int staffStatu, userStatu, optTimes;
string loginUserAccount;
Date sysDate(2018, 12, 1);


int menu();
bool checkStatu();
bool verifyPwdAgain();
bool userLogin();
bool userSignIn();
bool saveMoney();
bool drawMoney();
bool staffSignIn();

int main()
{
	Func func;

	while (1) {
		cout << "请输入工作号(输入0退出程序)：";
		string jobNumber;
		if (jobNumber == "0") break;
		cin >> jobNumber;
		cout << "请输入密码:";
		string password;
		cin >> password;
		Staff staff("", jobNumber, password);
		

		if (staff.verify()) {
			cout << "欢迎回来,";
			cout << staff.getName() << endl;
			staffStatu = 1;
			int opt = 0;
			while (opt = menu()) {
				User user;
				string account, pwd,strTemp;
				if (staffStatu == 0) {
					cout << "请先登入储蓄员账户" << endl;
					break;
				}
				//登入
				if (opt == 1) {
					if (!userLogin()) continue;
				}
				//注册
				else if (opt == 2) {
					if (!userSignIn()) continue;
				}
				//查询
				else if (opt == 3) {
					cout << "请输入查询用户账户" << endl;
					cin >> account;
					user.print(account);
				}
				//存款
				else if (opt == 4) {
					if (!saveMoney()) continue;
				}
				//取款
				else if (opt == 5) {
					if (!drawMoney()) continue;
				}
				//新增储蓄员
				else if (opt == 6) {
					if (!staffSignIn()) continue;
				}
				//退出
				else if (opt == 7) {
					Deposit deposit;
					cout << "即将到期金额:" << endl;
					cout << deposit.getRecentEndDepoist(sysDate) << "元" << endl;
				}
				//当日清算
				else if (opt == 8) {
					Deposit deposit;
					cout << "明日准备金额:" << deposit.settlement(sysDate) << endl;
					sysDate++;
				}	
				else if (opt == 9) {
					cout << "设置系统日期，依次输入年月日" << endl;
					int year, month, day;
					cin >> year >> month >> day;
					sysDate.setDate(year, month, day);
				}	
				else if (opt == 11) {
					string temp;
					cin >> temp;
					cout << func.judgePasswordStrength(temp) << endl;
				}
				else{
					staffStatu = 0;
					userStatu = 0;
				}
				getchar();
				getchar();
			}
		}
		else {
			cout << "用户名或密码错误" << endl;
			continue;
		}
	}
	getchar();
}

int menu() {
	int opt;
	optTimes++;
	if (optTimes == 3) {
		system("cls");
		optTimes = 0;
	}
	cout << "当前系统日期:  " << sysDate.get(0) << "." << sysDate.get(1) << "." << sysDate.get(2) << endl;

	cout << "0.退出" << endl;
	cout << "1.用户登入\t";
	cout << "2.用户注册\t";
	cout << "3. 查询存取款情况" << endl;
	cout << "4.存款\t\t";
	cout << "5.取款" << endl;
	cout << "6.注册储蓄员\t" << endl;
	cout << "7.获取即将到期的款项\t";
	cout << "8.当日结算" << endl;
	cout << "9.日期设置" << endl;
	cout << "10.挂失 " << endl;
	cout << "11.测试" << endl;
	cin >> opt;
	return opt;
}

bool checkStatu() {
	if (staffStatu&&userStatu)
		return false;
	return true;
}

bool verifyPwdAgain() {
	User user;
	int times = 3;
	while (times) {
		cout << "请再次输入该账户的用户密码" << endl;
		string pwd_temp;
		cin >> pwd_temp;
		times--;
		if (!user.verify(loginUserAccount, pwd_temp)) {
			cout << "密码不匹配，认证密码失败,还有" << times << "次机会" << endl;
		}
		else return true;
	}
	return false;
}
bool userLogin()
{
	User user;
	string account, pwd;
	cout << "请输入用户账户,输入0退出" << endl;
	cin >> account;
	if (account == "0") return false;
	cout << "请输入密码" << endl;
	cin >> pwd;
	if (!user.verify(account, pwd)) {
		cout << "用户账户密码错误" << endl;
		return false;
	}
	loginUserAccount = account;
	userStatu = true;
	cout << "欢迎回来" << user.getUserName() << endl;
	return true;
}

bool userSignIn()
{
	Func func;
	User user;
	string strTemp, pwd;
	cout << "输入希望的用户账户(需要自动生成请输入1,退出输入0)" << endl;
	user.setId(-1);
	cin >> strTemp;
	if (strTemp == "0") return false;
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
	user.setOpenDate(sysDate);
	user.save();
	cout << "注册成功" << endl;
	return true;
}

bool saveMoney()
{
	if (!userStatu) {
		cout << "请先登入用户账户" << endl;
		return false;
	}
	int type, principal, opt = 1;
	while (opt) {
		Date date(0, 0, 0);
		cout << "输入存储类型（月份数）" << endl;
		cin >> type;
		cout << "输入本金数" << endl;
		cin >> principal;
		cout << "核对信息" << endl;
		cout << "用户账户:" << loginUserAccount << endl;
		cout << "储蓄类型:" << type << "月" << endl;
		cout << "金额：" << principal << endl;
		cout << "输入0确定" << endl;
		cin >> opt;
	}
	if (!verifyPwdAgain()) return false;
	Deposit deposit(loginUserAccount, type, principal, sysDate);
	deposit.save();
	cout << "存款成功" << endl;
	return true;
}

bool drawMoney()
{
	if (!userStatu) {
		return false;
	}
	cout << "请输入需要取款的存款工单号" << endl;
	int id_temp;
	cin >> id_temp;
	Deposit deposit;
	deposit.setID(id_temp);
	deposit.readData();
	cout << "核对信息" << endl;
	cout << "用户账户:" << loginUserAccount << endl;
	cout << "储蓄类型:" << deposit.getType() << "月" << endl;
	cout << "金额：" << deposit.getPrincipal() << endl;
	cout << "输入0确定" << endl;

	if (deposit.checkCanBeTake()) {
		int money;
		while (1) {
			cout << "输入取钱数量" << endl;

			char opt[100];
			cin >> money;
			if (money >= deposit.getPrincipal()) {
				cout << "取款金额应该小于等于本金,请重新输入" << endl;
				continue;
			}
			cout << "取钱数为：" << money << endl;
			cout << "确定输入y,重新输入键入n" << endl;
			cin >> opt;

			if (opt[0] == 'Y' || opt[0] == 'y') break;
		}
		if (!verifyPwdAgain()) return false;

		deposit.setPrincipal(deposit.getPrincipal() - money);
		deposit.setTakeTimes(1);
		deposit.save();
		cout << "取款成功，已更新相关数据" << endl;
	}
	else {
		cout << "该账户已经曾经取过部分款项且为定期，无法再次取款" << endl;
	}
	return false;
}

bool staffSignIn()
{
	string staffAccount, staffPwd, staffPwd_2, staffName;
	cout << "输入储蓄员姓名" << endl;
	cin >> staffName;
	cout << "输入储蓄员账户" << endl;
	cin >> staffAccount;
	while (1) {
		cout << "输入储蓄员密码" << endl;
		cin >> staffPwd;
		cout << "再次输入储蓄员密码" << endl;
		cin >> staffPwd_2;
		if (staffPwd == staffPwd_2) {
			break;
		}
		else {
			cout << "两次密码不匹配" << endl;
		}
	}
	Staff newStaff(staffName, staffAccount, staffPwd);
	newStaff.save();
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


/// 日期更新函数