#ifndef LEXEMA_H
#define LEXEMA_H

enum LexemaType {
	OPERAND_DIGIT,
	OPERAND_VARIABLE,
	OPERATION_OR_SEPARATOR
};

class Lexema
{
public:
	Lexema();
	Lexema(LexemaType new_type, int new_value);

	LexemaType GetType() const;
	int GetValue() const;

	~Lexema();
private:
	LexemaType type;
	int value;
};

#endif