#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace User_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: �ڴ�������Դ���
			std::cout << "hello" << std::endl;
			getchar();
			getchar();
		}

	};
}