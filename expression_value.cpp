// expression_value.cpp : �������̨Ӧ�ó������ڵ㡣
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
			cout << "��������ʽ��" << endl;
			ExpressionValue<double>::Run();
			cout << "�Ƿ������";
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

