#pragma once

#include "stack.h"
#include <string>
#include <windows.h>
#include <vector>
#include <algorithm>

class arithmetic {
public:
	arithmetic(const std::string& _str) : expr(_str), copy_expr(_str) {};

	HANDLE hConsole				 = GetStdHandle(STD_OUTPUT_HANDLE);

	std::string					 delete_spaces();

	std::string					 convert();
	double						 compute(const std::string&);
	std::vector<std::string>	 is_expression_is_correct(const std::string&);
	size_t						 letters_counter(const std::string&);

	static int					 operators_priority(char operators);
	static bool					 is_digit(char elem);
	static bool					 is_letter(char elem);
	static bool					 is_operator(char op);
	static bool					 is_dot(char elem);

	void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
	{
		size_t pos = data.find(toSearch);
		while (pos != std::string::npos)
		{
			data.replace(pos, toSearch.size(), replaceStr);
			pos = data.find(toSearch, pos + replaceStr.size());
		}
	}

	void print() {
		if (is_expression_is_correct(copy_expr).empty()) {
			SetConsoleTextAttribute(hConsole, 15);
			if (letters_counter(expr) != 0) {
				std::string value;
				std::string character;
				for (size_t i = 0; i < expr.length(); ++i)
					if (arithmetic::is_letter(expr[i])) {
						character += expr[i];
						std::cout << "[!] Please enter the value of variable " << expr[i] << ": ";
						std::getline(std::cin >> std::ws, value);
						findAndReplaceAll(expr, character, value);
						character.clear();
					}
			}

			std::string string_after_transformig;
			string_after_transformig = convert();

			SetConsoleTextAttribute(hConsole, 14);
			std::cout << "[~] Transforming [ " << expr << " ] " << "\t-->\t[ " << string_after_transformig << "]" << '\n';

			SetConsoleTextAttribute(hConsole, 10);
			if (letters_counter(expr) == 0)
				std::cout << "\t[+] Result afrer calculations = " << compute(string_after_transformig) << '\n';
		} else std::cout << is_expression_is_correct(copy_expr).front();
		SetConsoleTextAttribute(hConsole, 15);
	}
private:
	std::string expr;
	std::string copy_expr;
};