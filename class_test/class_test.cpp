
#include "CppUnitTest.h"
#include "Staff.h"
#include "User.h"
#include "Date.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace class_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Staff staff("����", "1234", "1234");
			Date openDate(123, 123, 123);
			User user("123", "���", "123", "�ൺ", "123", openDate, false, Date(1, 1, 1));
			user.save();
			// TODO: �ڴ�������Դ���
		}

	};
}