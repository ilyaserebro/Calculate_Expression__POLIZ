#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <vector>
#include <map>

using namespace std;

// обозначение отсутствия перехода в таблицах состояний и выходов конечного автомата.	
const char DASH_CHAR = '-';
const int DASH_INT = -1;

template <typename InputSignal>
class StateMachine
{
public:
	StateMachine(const vector<InputSignal>& new_input_signals_set, 
		const string& file_state, const string& file_output);
	
	void Input(InputSignal input_signal);
	void Reset();

	int GetCurrentState() const;
	int GetCurrentOutput() const;

	void PrintStateTable() const;
	void PrintOutputTable() const;

	~StateMachine();
protected:
	void InitTable(const string& file, map<InputSignal, vector<int>>& table);
	void PrintTable(const map<InputSignal, vector<int>>& table) const;

	vector<InputSignal> input_signals_set;

	map<InputSignal, vector<int>> state_table;
	map<InputSignal, vector<int>> output_table;
	int current_state;
	int current_output;
};

#include "StateMachine.cpp"

#endif