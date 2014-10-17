#include "token.hpp"
#include <string>

using namespace std;

Token::Token(string const t_value, unsigned short t_type)
{
	token_value = t_value;
	token_type = t_type;
}