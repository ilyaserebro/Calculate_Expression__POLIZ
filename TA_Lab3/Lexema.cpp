#include "Lexema.h"


Lexema::Lexema()
{
}

Lexema::Lexema(LexemaType new_type, int new_value)
	: type(new_type), value(new_value)
{
}

LexemaType Lexema::GetType() const
{
	return type;
}

int Lexema::GetValue() const
{
	return value;
}

Lexema::~Lexema()
{
}
