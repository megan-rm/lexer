#pragma once
#include "token.hpp"

class Lexer
{
private:
	int current_state;
	int previous_state;
	int language[11][127];
	ifstream fin;
	string line;

	unsigned int line_number;
	unsigned int col;
public:
	Lexer();
	~Lexer();

	Token get_token();
};