#include "RPN.hpp"

double calcul(int first, char ope, int second){
    switch (ope){
        case '+':
            return first + second;
        case '-':
            return first - second;
        case '/':
            if (second == 0)
                throw Div0();
            return first / second;
        case '*':
            return first * second;
    }
    return 0;
}

void do_op(std::stack<int> &value, std::stack<char> &ope) {
    if (value.empty())
        throw Empty();
    if (value.size() - 1 != ope.size())
        throw (Operand());
    double res = value.top();
    value.pop();
    for (size_t index = 0; index <= value.size(); index ++){
        res = calcul(res, ope.top(), value.top());
        if (res > INT_MAX || res < INT_MIN)
            throw Overflow();
        ope.pop();
        value.pop();
    }
    std::cout << res << std::endl;
}

int rpn_calc(std::string arg){
    std::stack<int> value;
    std::stack<char> ope;

    for (size_t index = arg.length() - 1 ; index + 1 > 0; index--){
        if (std::isdigit(arg[index])){
            value.push(arg[index] - '0');
        }
        else if (arg[index] == ' ')
            ;
        else if (arg[index] == '-'
        || arg[index] == '+'
        || arg[index] == '*'
        || arg[index] == '/')
            ope.push(arg[index]);
        else
            throw (BadInput());
    }
    do_op(value, ope);
    return 1;
}