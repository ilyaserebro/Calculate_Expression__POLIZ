#ifndef TEXTTOLEXEMA_H
#define TEXTTOLEXEMA_H

#include <vector>
#include <map>
#include <string>
#include <set>

#include "StateMachine.h"
#include "Lexema.h"

using namespace std;

enum SignalType {
	VARIABLE,
	DIGIT,
	ASSIGMENT,
	LEFT_BRACKET,
	OPERATION,
	RIGHT_BRACKET,
	SEPARATOR,
};

//“ипы входных сигналов дл€ первой фазы
const vector<SignalType> INPUT_SIGNAL_SET_PH1 = { 
	VARIABLE,
	DIGIT,
	ASSIGMENT,
	LEFT_BRACKET,
	OPERATION,
	RIGHT_BRACKET,
	SEPARATOR
};

const set<char> OPERATIONS = { '+', '-', '/', '*' };

class TextToLexema : public StateMachine<SignalType>
{
public:
	TextToLexema(const string& file_state, const string& file_output);
	
	bool Run(char symbol, map<string, int>& association_array, 
		vector<int>& result_array, vector<Lexema>& lexemes);

	~TextToLexema();
private:
	SignalType CharToSignalType(char symbol) const;

	void AddSymbolToCurrentId(char symbol);								// y1: ѕродолжаем считывать им€ переменной
	void AddVariableToMap(map<string, int>& association_array);			// y2: ƒобавл€ем им€ переменной в ассоциативный массив
		
	void CreateSeparatorLexema(char symbol, vector<Lexema>& lexemes);	// y3: —оздаем и добавл€ем лексему типа 2 в массив лексем
	void AddSymbolToCurrentDigit(char symbol);							// y4: ѕродолжаем считывать число
	void CreateVariableAndSeparatorLexemes(char symbol,					// y5: —оздаем и добавл€ем лексему типа 1 в массив лексем,
		map<string, int>& association_array,							//	   создаем и добавл€ем лексему типа 2 в массив лексем										
		vector<Lexema>& lexemes);
	void CreateDigitAndSeparatorLexemes(char symbol,					// y7: —оздаем и добавл€ем лексему типа 0 в массив лексем,
		vector<Lexema>& lexemes);										//	   создаем и добавл€ем лексему типа 2 в массив лексем
																		// см. ћетодичку
	string current_id;
	string current_digit;
};

#endif
