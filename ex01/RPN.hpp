#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <climits>


int rpn_calc(std::string arg);

class BadInput : public std::exception {
			const char *what() const throw() {
				return ("Error: Bad Input.");
			}
};

class Div0 : public std::exception {
			const char *what() const throw() {
				return ("Error: Division by 0 forbidden.");
			}
};

class Operand : public std::exception {
			const char *what() const throw() {
				return ("Error: Problem operand number.");
			}
};

class BadConversion : public std::exception {
			const char *what() const throw() {
				return ("Error: Fail to conversion.");
			}
};

class Empty : public std::exception {
			const char *what() const throw() {
				return ("Error: Empty arg.");
			}
};

class Overflow : public std::exception {
			const char *what() const throw() {
				return ("Error: Overflow.");
			}
};
#endif