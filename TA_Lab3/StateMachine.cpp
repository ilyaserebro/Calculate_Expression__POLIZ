#ifndef STATEMACHINE_CPP
#define STATEMACHINE_CPP

#include <fstream>
#include <sstream>
#include <exception>
#include <iostream>

#include "StateMachine.h"

// public Методы

template <typename InputSignal>
StateMachine<InputSignal>::StateMachine(const vector<InputSignal>& new_input_signals_set,
	const string& file_state, const string& file_output)
	: input_signals_set(new_input_signals_set)
{
	InitTable(file_state, state_table);
	InitTable(file_output, output_table);
	Reset();
}

template <typename InputSignal>
void StateMachine<InputSignal>::Input(InputSignal input_signal)
{
	try
	{
		current_output = output_table.at(input_signal).at(current_state);
		current_state = state_table.at(input_signal).at(current_state);
	}
	catch (out_of_range e)
	{
		throw logic_error("Невозмжно перейти в указанное состояние.");
	}
}

template <typename InputSignal>
void StateMachine<InputSignal>::Reset()
{
	current_state = 0;
	current_output = 1;
}

template <typename InputSignal>
int StateMachine<InputSignal>::GetCurrentState() const
{
	return current_state;
}

template <typename InputSignal>
int StateMachine<InputSignal>::GetCurrentOutput() const
{
	return current_output;
}

template <typename InputSignal>
void StateMachine<InputSignal>::PrintStateTable() const
{
	PrintTable(state_table);
}

template <typename InputSignal>
void StateMachine<InputSignal>::PrintOutputTable() const
{
	PrintTable(output_table);
}

template <typename InputSignal>
StateMachine<InputSignal>::~StateMachine()
{
}

// private Методы

template <typename InputSignal>
void StateMachine<InputSignal>::InitTable(const string& file, map<InputSignal, vector<int>>& table)
{
	ifstream input(file);
	if (!input.is_open())
	{
		throw invalid_argument("Ошибка при создании объекта класса StateMachine: Не удалось открыть файл " + file);
	}

	string line;
	for (auto input_signal : input_signals_set)
	{
		getline(input, line);

		istringstream s_line(line);
		vector<int> line_table;

		char current_sym;
		while (s_line >> current_sym)
		{
			int value = 0;
			if (current_sym == DASH_CHAR)
			{
				value = DASH_INT;
			}
			else
			{
				value = current_sym - '0';
			}

			line_table.push_back(value);
		}

		table[input_signal] = line_table;
		line_table.clear();
	}

	input.close();
}

template <typename InputSignal>
void StateMachine<InputSignal>::PrintTable(const map<InputSignal, vector<int>>& table) const
{
	for (auto kv : table)
	{
		auto input_signal = kv.first;
		auto values = kv.second;
		cout << input_signal;

		for (auto value : values)
		{
			if (value == DASH_INT)
			{
				cout << " " << DASH_CHAR;
			}
			else
			{
				cout << " " << value;
			}
		}
		cout << endl;
	}
}

#endif