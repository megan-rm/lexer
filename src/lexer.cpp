#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "lexer.hpp"
#include "token.hpp"
using namespace std;

Lexer::Lexer()
{
	line_number = 0;
	col = 0;
	current_state = previous_state = 0;

	fin.open("DFA_LANGUAGE.txt");
	if (fin.is_open() == false)
		cout << "error loading language, check to see if DFA_LANGUAGE.txt is present..." << endl;

	for (int i = 0; i < 127; i++)
	for (int j = 0; j < 11; j++)
		fin >> language[j][i];


	fin.close();

	fin.open("sample_pascal.txt");
	if (fin.is_open() == false)
		cout << "error loading pascal code, check to see if sample_pascal.txt is present..." << endl;

};

Lexer::~Lexer(){};


Token Lexer::get_token()
{
	// initialize the reading information
	// will need to re-init only at eof when we make parser

	current_state = previous_state = 0;

	// read until the end of pascal program
	while (!fin.eof())
	{
		string token;

		if (col == line.size())
		{
			getline(fin, line);
			col = 0;
			line_number++;
		}

		char token_eval = ' ';

			for (int i = col; i <= line.size(); i++, col++)
			{
				if (i < line.size())
					token_eval = line.at(i);
				
				if (token_eval == '\t')
					token_eval = ' ';

				if (line.size() == 0)
				{
					cout << "BLANK LINE" << endl;
					continue;
				}

				previous_state = current_state;
				current_state = language[current_state][(int)token_eval];

				// Found an accept state
				if (current_state == 55 || col == line.size())
				{

					Token new_token("",0);
					switch (previous_state)
					{
					case 0:
						current_state = previous_state = 0;
						//Spaces
						token.clear();
						// Do nothing?
						break;
					case 1:
						current_state = previous_state = 0;
						cout << "WORD:\t" << token << endl;
						new_token.token_value = token;
						new_token.token_type = 1;
						return new_token;
						break;
					case 2:
						current_state = previous_state = 0;
						cout << "INT:\t" << token << endl;
						new_token.token_type = 2;
						new_token.token_value = token;
						return new_token;
						break;
					case 3:
						current_state = previous_state = 0;
						cout << "SPEC:\t" << token << endl;
						new_token.token_type = 3;
						new_token.token_value = token;
						return new_token;
						break;
					case 5:
						current_state = previous_state = 0;
						cout << "REAL:\t" << token << endl;
						new_token.token_type = 4;
						new_token.token_value = token;
						return new_token;
						break;
					case 10:
						current_state = previous_state = 0;
						cout << "REAL:\t" << token << endl;
						new_token.token_type = 4;
						new_token.token_value = token;
						return new_token;
						break;
					default:
						break;
					}
				}

				// Dead state
				else if (current_state == 99)
				{
					cout << "Error with token <<" << token
						<< ">>" << "at line: " << line_number << ", column: " << col+1
						<< "." << endl;
					Token dead("Dead", 99);
					return dead;
				}
				else
				{
					token.push_back(token_eval);
				}
			}
		}
		line_number++;
		col = 0;
	//fin.close();
	Token new_token("$", 55);
	return new_token;
};