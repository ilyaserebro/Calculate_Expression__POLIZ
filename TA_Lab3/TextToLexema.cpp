#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

#include "TextToLexema.h"

// public Методы

TextToLexema::TextToLexema(const string& file_state, const string& file_output)
	: StateMachine<SignalType>(INPUT_SIGNAL_SET_PH1, file_state, file_output), 
		current_id(""), current_digit("") {}

bool TextToLexema::Run(char symbol, map<string, int>& association_array,
	vector<int>& result_array, vector<Lexema>& lexemes)
{
	Input(CharToSignalType(symbol));

	bool go_to_phase2 = false;

	switch (current_output)
	{
	case 1: AddSymbolToCurrentId(symbol);						break;	//y1
	case 2: AddVariableToMap(association_array);				break;	//y2
	case 3: CreateSeparatorLexema(symbol, lexemes);				break;	//y3
	case 4: AddSymbolToCurrentDigit(symbol);					break;	//y4
	case 5: CreateVariableAndSeparatorLexemes(symbol, 
			association_array, lexemes);						break;	//y5
	case 6: CreateVariableAndSeparatorLexemes(symbol, 
			association_array, lexemes);
			go_to_phase2 = true;								break;	//y6
	case 7: CreateDigitAndSeparatorLexemes(symbol, lexemes);	break;	//y7
	case 8: CreateDigitAndSeparatorLexemes(symbol, lexemes);
			go_to_phase2 = true;								break;	//y8
	case 9: CreateSeparatorLexema(symbol, lexemes);
			go_to_phase2 = true;								break;	//y9
	}

	return go_to_phase2;
}

TextToLexema::~TextToLexema()
{}

// private Методы

SignalType TextToLexema::CharToSignalType(char symbol) const
{
	if (symbol >= 'A' && symbol <= 'Z' ||
		symbol >= 'a' && symbol <= 'z')
	{
		return SignalType::VARIABLE;
	}
	else if (symbol >= '0' && symbol <= '9')
	{
		return SignalType::DIGIT;
	}
	else if (symbol == '=')
	{
		return SignalType::ASSIGMENT;
	}
	else if (symbol == '(')
	{
		return SignalType::LEFT_BRACKET;
	}
	else if (OPERATIONS.find(symbol) != OPERATIONS.end())
	{
		return SignalType::OPERATION;
	}
	else if (symbol == ')')
	{
		return SignalType::RIGHT_BRACKET;
	}
	else if (symbol == ';')
	{
		return SignalType::SEPARATOR;
	}
	else
	{
		string error_message = "Ошибка: невозможно выполнить преобразование к SignalType. Неизвестный символ: " 
			+ string(1,symbol);
		throw invalid_argument(error_message);
	}
}

void TextToLexema::AddSymbolToCurrentId(char symbol)
{
	current_id += symbol;
}

void TextToLexema::AddVariableToMap(map<string, int>& association_array)
{
	if (association_array.count(current_id) == 0)
	{
		int count = association_array.size();
		association_array[current_id] = count;
	}
	current_id = "";
}

void TextToLexema::CreateSeparatorLexema(char symbol, vector<Lexema>& lexemes)
{
	Lexema lexema(LexemaType::OPERATION_OR_SEPARATOR, symbol);
	lexemes.push_back(lexema);
}

void TextToLexema::AddSymbolToCurrentDigit(char symbol)
{
	current_digit += symbol;
}

void TextToLexema::CreateVariableAndSeparatorLexemes(char symbol, 
	map<string, int>& association_array, vector<Lexema>& lexemes)
{
	string id = current_id;

	AddVariableToMap(association_array);
	int index = association_array.at(id);

	Lexema lexema(LexemaType::OPERAND_VARIABLE, index);
	lexemes.push_back(lexema);

	CreateSeparatorLexema(symbol, lexemes);
}

void TextToLexema::CreateDigitAndSeparatorLexemes(char symbol, 
	vector<Lexema>& lexemes)
{
	Lexema lexema(LexemaType::OPERAND_DIGIT, stoi(current_digit));
	lexemes.push_back(lexema);
	current_digit = "";

	CreateSeparatorLexema(symbol, lexemes);
}
