// ################### ilyaserebro #######################
// Вычисление выражений с помощью одностековой вычислительной машины.
// Подробно см. методичку: "POLIZ.pdf"

#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>
#include <stack>

#include "Lexema.h"
#include "TextToLexema.h"
#include "LexemaToPOLIZ.h"
#include "phase_3.h"

using namespace std;

const string expression_file = "Expression.txt";
const string state_file_ph1 = "State_Table_Phase1.txt";
const string output_file_ph1 = "Output_Table_Phase1.txt";
const string state_file_ph2 = "State_Table_Phase2.txt";
const string output_file_ph2 = "Output_Table_Phase2.txt";


string FindKeyByValue(const map<string, int>& _map, int target)
{
	for (auto kv : _map)
	{
		if (kv.second == target)
		{
			return kv.first;
		}
	}
	string error_message = "Ключ для значения '" + to_string(target) + "' не найден";
	throw domain_error(error_message);
}

int main()
{
	setlocale(LC_ALL, "Russian");

	try
	{
		ifstream input_expression(expression_file);
		if (!input_expression.is_open())
		{
			throw invalid_argument("Не удалось открыть файл: " + expression_file);
		}

		map<string, int> association_array;
		stack<Lexema> stack_shop;
		stack_shop.push(Lexema{ LexemaType::OPERATION_OR_SEPARATOR, int('@') });
		vector<int> result_array;

		string line;

		while (getline(input_expression, line))
		{
			TextToLexema sm_phase1(state_file_ph1, output_file_ph1);
			vector<Lexema> lexemes;

			istringstream s_line(line);
			char current_sym;

			while (s_line >> current_sym)
			{
				if (sm_phase1.Run(current_sym, association_array, result_array, lexemes))
				{
					LexemaToPOLIZ sm_phase2(state_file_ph2, output_file_ph2);
					vector<Lexema> POLIZ = sm_phase2.Run(lexemes, stack_shop);
					
					try
					{
						phase3(POLIZ, stack_shop, result_array);
					}
					catch (int id_unresolved_variable)
					{
						string unresolved_variable = FindKeyByValue(association_array,
							id_unresolved_variable);
						string error_message = "Переменная '" + unresolved_variable + 
							"' не была инициализирована";

						throw runtime_error(error_message);
					}
				}
			}
		}

		cout << "Значения переменных: " << endl;
		for (auto variable : association_array)
		{
			cout << variable.first << " = " << result_array[variable.second] << endl;
		}

	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}


	system("pause");
	return 0;
}