// expression_value.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "utility.h"
#include "expression_value.h"

int main()
{
	try
	{
		bool bYes;

		do
		{
			cout << "请输入表达式：" << endl;
			ExpressionValue<double>::Run();
			cout << "是否继续？";
			bYes = UserSaysYes();
		} while (bYes);
	}
	catch (Error err)
	{
		err.Show();
	}

	system("PAUSE");
	return 0;
}

