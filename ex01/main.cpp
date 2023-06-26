#include "RPN.hpp"

int main(int av, char **ac)
{
    if (av != 2)  {
        std::cerr << "Need only one arg ./RPN '0 + 0'" << std::endl;
    }
    try {
        rpn_calc(ac[1]);
    }
    catch (std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}