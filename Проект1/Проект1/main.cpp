#include <iostream>
#include <stack>
#include <string>
#include <list>
#include "bool_ext.h";

//using namespace std;




int priority(char sym)
{
	switch (sym)
	{
	case '!':
		return 10;
		break;
	case '*':
		return 3;
		break;
	case '/':
		return 3;
		break;
	case '+':
		return 2;
		break;
	case '-':
		return 2;
		break;
	case'>':
		return 1;
		break;
	case '(':
		return -1;
	case ')':
		return -2;
	default:
		return 0;
		break;
	}
}


stack <char> RPN(string s)
{

	stack <char> op;
	stack <char> output;
	for (int i = 0; i < s.length(); i++)
	{
		switch (priority(s[i]))
		{
		case 0:
			output.push(s[i]);
			break;
		case -1:
			op.push(s[i]);
			break;
		case -2:
			while (op.top() != '(')
			{
				char RPN_List = op.top();
				output.push(op.top());
				op.pop();
			}
			op.pop();
			break;
		default:
			if (op.empty() == true)
			{
				op.push(s[i]);
			}
			else {
				if (priority(op.top()) >= priority(s[i]))
				{
					output.push(op.top());
					op.pop();
					op.push(s[i]);
				}
				else
				{
					op.push(s[i]);
				}
			}
			break;
		}
	}
	while (op.empty() == false)
	{
		output.push(op.top());
		op.pop();
	}

	return output;
}
bool_ext SymToVar(char Sym, bool_ext a, bool_ext b, bool_ext c, bool_ext d)
{
	switch (Sym)
	{
	case 'a':
		return a;
		break;
	case 'b':
		return b;
		break;
	case 'c':
		return c;
		break;
	case 'd':
		return d;
		break;
	case '1':
		return 1;
	case '0':
		return 0;
	}
}

char CalcRPN_Expr(list <char> RPN_Expr, bool_ext a, bool_ext b, bool_ext c, bool_ext d)
{
	stack <char> result_stack;
	bool_ext current_res;
	char current_res_char;
	while (RPN_Expr.size()>0)
	{
		switch (priority(RPN_Expr.front()))
		{
		case 0:
			result_stack.push(RPN_Expr.front());
			break;
		case 3: // *
			current_res = SymToVar(result_stack.top(), a, b, c, d);
			result_stack.pop();
			current_res = current_res*SymToVar(result_stack.top(), a, b, c, d);
			result_stack.pop();
			current_res_char = current_res == 1 ? '1' : '0';
			result_stack.push(current_res_char);
			break;
		case 2: // +
			current_res = SymToVar(result_stack.top(), a, b, c, d);
			result_stack.pop();
			current_res = current_res + SymToVar(result_stack.top(), a, b, c, d);
			result_stack.pop();
			current_res_char = current_res == 1 ? '1' : '0';
			result_stack.push(current_res_char);
			break;
		case 1: //  > 
			current_res = SymToVar(result_stack.top(), a, b, c, d);
			result_stack.pop();
			current_res = current_res < SymToVar(result_stack.top(), a, b, c, d); // їз-за использовани§ стека обратна§ имплекаци§. Цеазиловать через лучший костыль! 
			result_stack.pop();
			current_res_char = current_res == 1 ? '1' : '0';
			result_stack.push(current_res_char);
			break;
		case 10:
			current_res = SymToVar(result_stack.top(), a, b, c, d);
			result_stack.pop();
			current_res_char = current_res == 1 ? '0' : '1';
			result_stack.push(current_res_char);
		}
		RPN_Expr.pop_front();
	}
	return result_stack.top();

}


void PrintTable(list <char> RPN_Expr)
{
	bool_ext a = 1;
	bool_ext b = 0;
	bool_ext c = 0;
	bool_ext d = 0;
	cout << endl;
	cout << "TABLE OF TRUTH (TRUESH TABLE):\n";
	for (int i = 0; i < 16; i++)
	{
		a = (i >> 3) & 0xF1;
		b = (i >> 2) & 0xF1;
		c = (i >> 1) & 0xF1;
		d = i & 0xF1;
		cout << a << " " << b << " " << c << " " << d << "|" << CalcRPN_Expr(RPN_Expr, a, b, c, d) << "\n";
	}
	cout << endl;
	// cout << CalcRPN_Expr(RPN_Expr, a, b, c, d);

}






int main()
{
	string s;
	stack <char> RPN_Stack;
	int i = 0;
	cin >> s;
	RPN_Stack = RPN(s);
	list <char> RPN_List;

	while (RPN_Stack.empty() == false)
	{
		RPN_List.push_front(RPN_Stack.top());
		RPN_Stack.pop();
	}
	list <char> RPN_List_Output = RPN_List;
	cout << "Reverse Polish notation:\n";
	while (RPN_List_Output.empty() == false)
	{
		cout << RPN_List_Output.front();
		RPN_List_Output.pop_front();
	}
	cout << "\n";
	PrintTable(RPN_List);
	system("pause");
	return 0;
}