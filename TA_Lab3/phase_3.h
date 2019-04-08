#ifndef PHASE_3_H
#define PHASE_3_H

#include <vector>
#include <stack>

#include "Lexema.h"

using namespace std;

//	�.�. � ������� ���� ������������ ������� ��� ������, ���� ������� �������
//	����������� ��� � ������� �������, � �� � ������� ������, ������������ �� StateMachine

int GetOperand(const stack<Lexema>& stack_shop, const vector<int>& result_array);

void phase3(const vector<Lexema>& POLIZ, stack<Lexema>& stack_shop,
	vector<int>& result_array);

#endif