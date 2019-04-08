#include <fstream>
#include <sstream>

#include "LexemaToPOLIZ.h"
#include "TextToLexema.h"


LexemaToPOLIZ::LexemaToPOLIZ(const string& file_state, const string& file_output)
	: StateMachine<XType>(INPUT_SIGNAL_SET_PH2, file_state, file_output),
		current_conveyor_rank(0), current_stack_rank(-2)
{
	
}

vector<Lexema> LexemaToPOLIZ::Run(const vector<Lexema>& conveyor, stack<Lexema>& stack_shop)
{
	vector<Lexema> POLIZ;
	bool go_to_phase3 = false;

	for (int i = 0; i < conveyor.size() && !go_to_phase3; ++i)
	{
		Lexema lexema = conveyor[i];

		if (lexema.GetType() == LexemaType::OPERATION_OR_SEPARATOR)
		{
			SetCurrentConveyorRank(lexema.GetValue());
		}

		Input(LexemaToXType(lexema));

		switch (current_output)
		{
		case 1: 
			{
				POLIZ.push_back(lexema);
				break;
			}
		case 2:
			{
				stack_shop.push(lexema);
				SetCurrentStackRank(lexema.GetValue());
				break;
			}
		case 3:
			{
				POLIZ.push_back(stack_shop.top());
				stack_shop.pop();
				SetCurrentStackRank(stack_shop.top().GetValue());
				i--;
				break;
			}
		case 4:
			{
				stack_shop.pop();
				SetCurrentStackRank(stack_shop.top().GetValue());
				break;
			}
		case 5:
			{
				POLIZ.push_back(lexema);
				go_to_phase3 = true;
				break;
			}
		}
	}

	return POLIZ;
}

LexemaToPOLIZ::~LexemaToPOLIZ()
{
}

// private

XType LexemaToPOLIZ::LexemaToXType(Lexema lexema) const
{
	LexemaType lexema_type = lexema.GetType();
	if (lexema_type == OPERAND_DIGIT || 
		lexema_type == OPERAND_VARIABLE)
	{
		return XType::X1;
	}
	else
	{
		if (current_conveyor_rank <= current_stack_rank)
		{
			return XType::X3;
		}
		else if (lexema.GetValue() == (int)')')
		{
			return XType::X4;
		}
		else if (lexema.GetValue() == (int)';')
		{
			return XType::X5;
		}
		else
		{
			return XType::X2;
		}
	}
}

void LexemaToPOLIZ::SetCurrentConveyorRank(int lexema_value)
{
	switch (lexema_value)
	{
	case '(': current_conveyor_rank = 3; break;
	case ')': current_conveyor_rank = 0; break;
	case '+':
	case '-': current_conveyor_rank = 1; break;
	case '*':
	case '/': current_conveyor_rank = 2; break;
	case ';': current_conveyor_rank = -1; break;
	}
}

void LexemaToPOLIZ::SetCurrentStackRank(int lexema_value)
{
	switch (lexema_value)
	{
	case '(': current_stack_rank = -1; break;
	case '+':
	case '-': current_stack_rank = 1; break;
	case '*':
	case '/': current_stack_rank = 2; break;
	case '@': current_stack_rank = -2; break;
	}
}


