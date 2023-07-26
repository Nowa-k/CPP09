#include "RPN.hpp"

long int calcul(long int first, char ope, long int second){
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

void do_op(std::stack<char> &rpn) {
    long int res = 0;
    long int ope = 0;

    if (rpn.top() >= '0' && rpn.top() <= '9')
        res = rpn.top() - '0';
    else
        throw (BadInput());
    rpn.pop();
    while (!rpn.empty()){
        if (rpn.top() != ' ')
            throw (BadInput());
        rpn.pop();

        if (rpn.empty()) throw BadInput();
        if (rpn.top() >= '0' && rpn.top() <= '9')
            ope = rpn.top() - '0';
        else
            throw BadConversion();
        rpn.pop();

        if (rpn.empty()) throw BadInput();
        if (rpn.top() != ' ')
            throw (BadInput());
        rpn.pop();

        if (rpn.empty()) throw BadInput();
        if (rpn.top() != '-' && rpn.top() != '+'
            && rpn.top() != '*' && rpn.top() != '/')
            throw (Operand());

        if (rpn.empty()) throw BadInput();
        res = calcul(res, rpn.top(), ope);
        if (res > INT_MAX || res < INT_MIN)
            throw (Overflow()); 
        if (rpn.empty()) break;
        rpn.pop();
    }
    std::cout << res << std::endl;
}

int rpn_calc(std::string arg){
    std::stack<char> rpn;
    
    for (size_t index = arg.length() - 1 ; index + 1 > 0; index--){
            rpn.push(arg[index]);
    }
    do_op(rpn);
    return 1;
}