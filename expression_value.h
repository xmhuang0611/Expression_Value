#pragma once
#ifndef EXPRESSION_VALUE_H
#define EXPRESSION_VALUE_H

#include "lk_stack.h"

//表达式求值类
template<class ElemType>
class ExpressionValue
{
private:
	static bool IsOperator(char ch);  //判断ch是否为运算符
	static int LeftPri(char op);      //左边运算符的优先级
	static int RightPri(char op);     //右边运算符的优先级
	static void Get2Operand(LinkStack<ElemType>&opnd, ElemType&a1, ElemType&a2);
	//从opnd中获取两个运算数
	static void DoOperator(LinkStack<ElemType>&opnd, const ElemType&a1, char op, const ElemType&a2);
	//形成运算指令（a1）op（a2） 结果进入opnd栈
	static void PostfixExpression(ofstream&outFile);
	//将键盘中输入的中缀表达式转换为后缀表达式，再存入输出流文件outFile中
	static void PostfixExpressionValue(ifstream&inFile);
	//从输入文件inFile中输入后缀表达式，并求后缀表达式的值
public:
	ExpressionValue() {};
	virtual~ExpressionValue() {};
	static void Run();       //求从键盘中输入的中缀表达式之值
};
template<class ElemType>
bool ExpressionValue<ElemType>::IsOperator(char ch)
{
	if (ch == '=' || ch == '(' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == ')')
		return true;
	else return false;
}
template<class ElemType>
int ExpressionValue<ElemType>::LeftPri(char op)
{
	int result;
	if (op == '=')result = 0;
	else if (op == '(')result = 1;
	else if (op == '*' || op == '/')result = 5;
	else if (op == '+' || op == '-')result = 3;
	else if (op == ')')result = 6;
	return result;
}
template<class ElemType>
int ExpressionValue<ElemType>::RightPri(char op)
{
	int result;
	if (op == '=')result = 0;
	else if (op == '(')result = 6;
	else if (op == '*' || op == '/')result = 4;
	else if (op == '+' || op == '-')result = 2;
	else if (op == ')')result = 1;
	return result;
}
template<class ElemType>
void ExpressionValue<ElemType>::Get2Operand(LinkStack<ElemType>&opnd, ElemType&a1, ElemType&a2)
{
	if (opnd.Pop(a2) == UNDER_FLOW)throw Error("表达式异常！");
	if (opnd.Pop(a1) == UNDER_FLOW)throw Error("表达式异常！");
}
template<class ElemType>
void ExpressionValue<ElemType>::DoOperator(LinkStack<ElemType>&opnd, const ElemType&a1, char op, const ElemType&a2)
{
	switch (op)
	{
	case'+':
		opnd.Push(a1 + a2);
		break;
	case'-':
		opnd.Push(a1 - a2);
		break;
	case'*':
		opnd.Push(a1*a2);
		break;
	case'/':
		if (a2 == 0)throw Error("除数为0！");
		opnd.Push(a1 / a2);
		break;
	}
}
template<class ElemType>
void ExpressionValue<ElemType>::PostfixExpression(ofstream&outFile)
//操作结果：将键盘中输入的中缀表达式转换为后缀表达式，再存入输出流文件outFile中
{
	LinkStack<char>optr;     //操作符栈 
	char ch, optrTop, op;    //输入的字符，操作符栈的栈顶操作符，操作符op
	ElemType operand;        //操作数
	optr.Push('=');
	optr.Top(optrTop);       //取出操作符栈栈顶
	ch = GetChar();          //从输入流cin中跳过空格与制表符取出一个字符
	while (optrTop != '=' || ch != '=')
	{
		if (isdigit(ch) || ch == '.')
		{	//ch为数字或句点时的操作
			cin.putback(ch);
			cin >> operand;
			outFile << operand << " ";
			ch = GetChar();
		}
		else if (!IsOperator(ch))
		{
			throw Error("非法字符！");
		}
		else
		{

			if (LeftPri(optrTop)<RightPri(ch))
			{

				optr.Push(ch);
				ch = GetChar();

			}
			else if (LeftPri(optrTop)>RightPri(ch))
			{

				optr.Pop(op);
				outFile << op << " ";
			}
			else if (LeftPri(optrTop) == RightPri(ch) && ch == ')')
			{
				optr.Pop(ch);          //从optr栈退出栈顶的'('
				ch = GetChar();
			}
		}
		optr.Top(optrTop);    // 取出操作符栈栈顶     
	}
	outFile << '=';           //输出流文件outFile以'='结束
}
template<class ElemType>
void ExpressionValue<ElemType>::PostfixExpressionValue(ifstream&inFile)
//操作结果：从输入文件inFile中输入后缀表达式，并求后缀表达式的值
{
	LinkStack<ElemType>opnd;             //操作数栈
	char ch;                             //当前字符
	double operand;                      //操作数

	while (inFile >> ch, ch != '=')
	{
		if (IsOperator(ch))
		{
			ElemType a1, a2;
			Get2Operand(opnd, a1, a2);
			DoOperator(opnd, a1, ch, a2); // （a1）op（a2），结果进opnd栈
		}
		else
		{
			inFile.putback(ch);
			inFile >> operand;
			opnd.Push(operand);
		}
	}
	opnd.Top(operand);
	cout << operand << endl;
}
template<class ElemType>
void ExpressionValue<ElemType>::Run()
//操作结果：求从键盘输入的中缀表达式之值
{
	ofstream outFile("temp");  //定义输出流文件
	PostfixExpression(outFile);
	//将从键盘所输入的中缀表达式转换为后缀表达式，结果存入输出流文件中，以‘=’结束
	outFile.close();               //关闭输出流文件

	ifstream inFile("temp");   //定义输入流文件
	PostfixExpressionValue(inFile);
	//计算从输入流文件中输入的后缀表达式，将结果在屏幕上显示出来
	inFile.close();                //关闭输出流文件 

	remove("temp");            //删除临时文件temp
}
#endif
