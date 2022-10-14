#include <iostream>
#include "../include/arithmetic.h"

bool arithmetic::is_operator(char op) {
	if (op == '+' || op == '-'
		|| op == '*' || op == '/')
		return 1;
	return 0;
}

bool arithmetic::is_letter(char elem) {
	if (elem >= 'a' && elem <= 'z'
		|| elem >= 'A' && elem <= 'Z')
		return 1;
	return 0;
}

bool arithmetic::is_digit(char elem) {
	if (elem >= '0' && elem <= '9')
		return 1;
	return 0;
}

bool arithmetic::is_dot(char elem) {
	if (elem == '.')
		return 1;
	return 0;
}

int arithmetic::operators_priority(char operators) {
	if (operators == '+' || operators == '-')
		return 2;
	if (operators == '*' || operators == '/')
		return 1;
	return INT_MAX;
}

std::string arithmetic::delete_spaces() {
	expr.erase(std::remove_if(expr.begin(), expr.end(), std::isspace), expr.end());
		return expr;
}

std::vector<std::string> arithmetic::is_expression_is_correct(const std::string& _str) {
	size_t c_brackets = 0;
	size_t op_brackets = 0;
	size_t operators_counter = 0;
	std::vector<std::string> errors;
	SetConsoleTextAttribute(hConsole, 4);
	for (size_t i = 0; i < _str.length(); ++i) {
		if (!(is_dot(_str[i]) || is_digit(_str[i]) ||
			is_operator(_str[i]) || is_letter(_str[i]) || _str[i] == ' '
			|| _str[i] == '(' || _str[i] == ')')) {
			errors.push_back("[-] Incorrect symbol in " + std::to_string(i) + " position \n");
		}
		if (is_operator(_str[i])) {
			operators_counter++;
		}
		if (_str[0] == '+' || _str[0] == '*' || _str[0] == '/' || _str[0] == '.') {
			errors.push_back("[-] Expression cant start with folowing operators/dot: [+],[*],[/],[.]\n");
		}
		if (_str[0] == ')') {
			errors.push_back("[-] Expression cant start with closing bracket\n");
		}
		if (!(is_digit(_str[0]) || is_letter(_str[0]) || _str[0] == '(' || _str[0] == '-')) {
			errors.push_back("[-] Expression can start only with digits or opening bracket or unary minus\n");
		}
		if (_str[0] == '-' && is_operator(_str[1])) {
			errors.push_back("[-] There are should not be an operator afrer unary minus: invalid position - " + std::to_string(1) + "\n");
		}
		if (is_operator(_str[i]) && i != 0) {
			if (_str[i + 1] == '+' || _str[i + 1] == '*' || _str[i + 1] == '/') {
				errors.push_back("[-] There are should not be an operator afrer operator: invalid position - " + std::to_string(i + 2) + "\n");
			}
			else if (is_dot(_str[i + 1])) {
				errors.push_back("[-] There are should not be a dot afrer operator: invalid position - " + std::to_string(i + 2) + "\n");
			}
			else if (is_dot(_str[i - 1])) {
				errors.push_back("[-] There are should not be a dot before operator: invalid position - " + std::to_string(i) + "\n");
			}
			continue;
		}
		if (is_digit(_str[i]) && is_letter(_str[i + 1]) || is_letter(_str[i]) && is_digit(_str[i+1])) {
			errors.push_back("[-] Missing operator between digit and variable: invalid position - " + std::to_string(i) + "\n");
		}
		if (is_letter(_str[i]) && is_letter(_str[i + 1])) {
			errors.push_back("[-] Missing operator between variables: invalid position - " + std::to_string(i) + "\n");
		}
		if (_str[i] == '(' && _str[i + 1] == ')') {
			errors.push_back("[-] There are should not be an opening bracket before closing bracket: invalid position - " + std::to_string(i + 1) + "\n");
		}
		if (_str[i] == ')' && _str[i + 1] == '(') {
			errors.push_back("[-] Did not expect opening bracket after a closing bracker: invalid position - " + std::to_string(i + 1) + "\n");
		}
		if (is_dot(_str[_str.length() - 1])) {
			 errors.push_back("[-] Expression shoud be ended with a digit or a closing bracket\n");
		}
		if (is_operator(_str[_str.length() - 1])) {
			errors.push_back("[-] Expect a number after the last operator: invalid position - " + std::to_string(_str.length()) + "\n");
		}
		if (_str[_str.length() - 1] == '(') {
			errors.push_back("[-] Expect a number after the opening bracket: invalid position - " + std::to_string(_str.length()) + "\n");
		}
		if (_str[i] == '(' && (_str[i + 1] == '+' || _str[i + 1] == '/' || _str[i+1] == '*')) {
			errors.push_back(" [-] Didn't expect '+' or '/' or '*' after opening bracket \n");
		}

		if (is_dot(_str[i])) {
			if (is_dot(_str[i + 1])) {
				errors.push_back("[-] There are should not be a dot afrer a dot: invalid position - " + std::to_string(i + 2) + "\n");
			}
		}
		if (is_dot(_str[i])) {
			for (size_t k = i + 1; is_digit(_str[k]) && k < _str.length(); ++k)
			{
				if (is_dot(_str[k + 1])) {
					errors.push_back("[-] There are should not be two dots in number: invalid position - " + std::to_string(k + 2) + "\n");
				}
			}
		}

		if (_str[i] == '(') {
			op_brackets++;
		}
		if (_str[i] == ')') {
			c_brackets++;
		}
		if (is_digit(_str[i]) && _str[i + 1] == '(') {
			errors.push_back("[-] Opening bracket after a digit were not expected\n");
		}
	}
	if (op_brackets > c_brackets) {
		errors.push_back("[-] Missing closing bracket\n");
	}
	else if (op_brackets < c_brackets) {
		errors.push_back("[-] Missing opening bracket\n");
	}
	if (operators_counter == 0) {
		errors.push_back("[-] There are no operators in your expression \n");
	}
	return errors;
}

std::string arithmetic::convert() {
	/* std::string expression is an output(operands) stack */
	/* stack<char> _operators_stack is an operators stack */
	stack<char> _operators_stack;
	std::string expression;
	std::string entered_string = delete_spaces();
		for (size_t i = 0; i < entered_string.length(); ++i) {
			if (entered_string[i] == '(')
				_operators_stack.push(entered_string[i]);
			else if (entered_string[i] == ')') {
				while (_operators_stack.top() != '(') {
					expression.push_back(_operators_stack.top());
					expression.push_back(' ');
					_operators_stack.pop();
				}
				_operators_stack.pop();
			}
			else if (is_digit(entered_string[i]) || is_letter(entered_string[i]) || is_dot(entered_string[i])) {
				for (; i < entered_string.length() && (is_digit(entered_string[i]) || is_letter(entered_string[i]) || is_dot(entered_string[i])); ++i) 
					expression.push_back(entered_string[i]);
				--i;
				expression.push_back(' ');
			}

			else if (entered_string[i] == '-' && (i == 0 || entered_string[i - 1] == '(' || is_operator(entered_string[i - 1])))
				_operators_stack.push('_');
			else {
				while (!_operators_stack.empty() && (_operators_stack.top() == '_' || operators_priority(entered_string[i]) >= operators_priority(_operators_stack.top()))) {
					expression.push_back(_operators_stack.top());
					expression.push_back(' ');
					_operators_stack.pop();
				}
				_operators_stack.push(entered_string[i]);
			}
		}
		while (!_operators_stack.empty()) {
			expression.push_back(_operators_stack.top());
			expression.push_back(' ');
			_operators_stack.pop();
		}
		return expression;
}

size_t arithmetic::letters_counter(const std::string& expr) {
	size_t letters = 0;
	for (size_t i = 0; i < expr.length(); ++i)
		if (is_letter(expr[i])) {
			letters++;
			return letters;
		}
	return 0;
}


 double arithmetic::compute(const std::string& postfix_expression) {
	stack<double> _operands_stack;
		for (size_t i = 0; i < postfix_expression.length(); ++i) {
			if (is_digit(postfix_expression[i]) || is_dot(postfix_expression[i])) {
				double temp = 0;
				for (; i < postfix_expression.length() && is_digit(postfix_expression[i]); ++i)
					temp = temp * 10 + (postfix_expression[i] - '0');
				if (postfix_expression[i] == '.') {
					double divide = 1;
					for (i++; i < postfix_expression.length() && is_digit(postfix_expression[i]); ++i) {
						temp = temp * 10 + (postfix_expression[i] - '0');
						divide *= 10;
					}
					temp /= divide;
				}
				_operands_stack.push(temp);
				--i;
			}
			else if (is_operator(postfix_expression[i])) {
				double operand_1 = _operands_stack.pop();
				double operand_2 = _operands_stack.pop();
				if (postfix_expression[i] == '+')
					_operands_stack.push(operand_1 + operand_2);
				if (postfix_expression[i] == '-')
					_operands_stack.push(operand_2 - operand_1);
				if (postfix_expression[i] == '*')
					_operands_stack.push(operand_1 * operand_2);
				if (postfix_expression[i] == '/')
					_operands_stack.push(operand_2 / operand_1);
			}
			else if (postfix_expression[i] == '_')
				_operands_stack.push(_operands_stack.pop() * (-1));
		}
		return _operands_stack.pop();
 }
