#include "phase_3.h"
#include "TextToLexema.h"

int GetOperand(const stack<Lexema>& stack_shop, const vector<int>& result_array)
{
	int operand;
	if (stack_shop.top().GetType() == LexemaType::OPERAND_VARIABLE)
	{
		try
		{
			operand = result_array.at(stack_shop.top().GetValue());
		}
		catch (out_of_range e)
		{
			int id_unresolved_variable = stack_shop.top().GetValue();
			throw id_unresolved_variable;
		}
	}
	else
	{
		operand = stack_shop.top().GetValue();
	}

	return operand;
}

void phase3(const vector<Lexema>& POLIZ, stack<Lexema>& stack_shop,
	vector<int>& result_array)
{
	for (auto lexema : POLIZ)
	{
		if (lexema.GetType() == LexemaType::OPERAND_DIGIT ||
			lexema.GetType() == LexemaType::OPERAND_VARIABLE)
		{
			stack_shop.push(lexema);
		}
		else if (OPERATIONS.find(lexema.GetValue()) != OPERATIONS.end())
		{
			int rhs = GetOperand(stack_shop, result_array);
			stack_shop.pop();

			int lhs = GetOperand(stack_shop, result_array);
			stack_shop.pop();

			int result = 0;

			switch (lexema.GetValue())
			{
			case '+': result = lhs + rhs; break;
			case '-': result = lhs - rhs; break;
			case '*': result = lhs * rhs; break;
			case '/': result = lhs / rhs; break;
			}

			stack_shop.push(Lexema{ LexemaType::OPERAND_DIGIT, result });
		}
		else if (lexema.GetValue() == (int)';')
		{
			result_array.push_back(stack_shop.top().GetValue());
			stack_shop.pop();
		}
	}
}

