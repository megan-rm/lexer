#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "lexer.hpp"
using namespace std;





int main()
{
	Lexer my_lexer;
	while (my_lexer.get_token().token_value != "$")
	{
	}

	cin.get();
	return 0;
}