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

//���� ������� �������� ��� ������ ����
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

	void AddSymbolToCurrentId(char symbol);								// y1: ���������� ��������� ��� ����������
	void AddVariableToMap(map<string, int>& association_array);			// y2: ��������� ��� ���������� � ������������� ������
		
	void CreateSeparatorLexema(char symbol, vector<Lexema>& lexemes);	// y3: ������� � ��������� ������� ���� 2 � ������ ������
	void AddSymbolToCurrentDigit(char symbol);							// y4: ���������� ��������� �����
	void CreateVariableAndSeparatorLexemes(char symbol,					// y5: ������� � ��������� ������� ���� 1 � ������ ������,
		map<string, int>& association_array,							//	   ������� � ��������� ������� ���� 2 � ������ ������										
		vector<Lexema>& lexemes);
	void CreateDigitAndSeparatorLexemes(char symbol,					// y7: ������� � ��������� ������� ���� 0 � ������ ������,
		vector<Lexema>& lexemes);										//	   ������� � ��������� ������� ���� 2 � ������ ������
																		// ��. ���������
	string current_id;
	string current_digit;
};

#endif
