#ifndef LEXEMATOPOLIZ_H
#define LEXEMATOPOLIZ_H

#include <vector>
#include <stack>

#include "Lexema.h"
#include "StateMachine.h"

using namespace std;

enum XType {
	X1,
	X2,
	X3,
	X4,
	X5,
};

const vector<XType> INPUT_SIGNAL_SET_PH2 = {
	X1,
	X2,
	X3,
	X4,
	X5,
};

class LexemaToPOLIZ : public StateMachine<XType>
{
public:
	LexemaToPOLIZ(const string& file_state, const string& file_output);

	vector<Lexema> Run(const vector<Lexema>& conveyor, stack<Lexema>& stack_shop);
	
	~LexemaToPOLIZ();
private:
	XType LexemaToXType(Lexema lexema) const;
	
	void SetCurrentConveyorRank(int lexema_value);
	void SetCurrentStackRank(int lexema_value);

	int current_conveyor_rank;
	int current_stack_rank;
};

#endif

