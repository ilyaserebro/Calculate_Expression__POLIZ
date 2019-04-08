#ifndef PHASE_3_H
#define PHASE_3_H

#include <vector>
#include <stack>

#include "Lexema.h"

using namespace std;

//	Т.к. в третьей фазе используется автомат без памяти, было принято решение
//	реализовать его с помощью функции, а не с помощью класса, производного от StateMachine

int GetOperand(const stack<Lexema>& stack_shop, const vector<int>& result_array);

void phase3(const vector<Lexema>& POLIZ, stack<Lexema>& stack_shop,
	vector<int>& result_array);

#endif