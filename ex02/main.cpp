/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 11:10:10 by aleferra          #+#    #+#             */
/*   Updated: 2023/06/27 18:56:16 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void printList(std::list<int> &theList){
    std::list<int>::iterator ite;
    std::cout << "Before:  ";
    for (ite = theList.begin(); ite != theList.end(); ite++)
        std::cout << *ite << " ";
    std::cout << std::endl;
}

void printDeque(std::deque<int> &theQue){
    std::deque<int>::iterator ite;
    std::cout << "After:   ";
    for (ite = theQue.begin(); ite != theQue.end(); ite++)
        std::cout << *ite << " ";
    std::cout << std::endl;
}

int check_double(std::list<int> &theList, int num){
    std::list <int>::iterator ite;
    for (ite = theList.begin(); ite != theList.end(); ite++){
        if (*ite == num){
            std::cout << "COmp " << (*ite) << " " << (num) <<std::endl;
            return 0;
        }
    }
    return 1;
}

int stdIsDigit(std::string num){
    if (num.size() > 10)
        return 0;
    if (num.size() == 10 && num.compare("2147483647") > 0)
        return 0;
    for (size_t index = 0; index < num.size(); index++){
        if(!std::isdigit(num[index]))
            return 0;
    }
    return 1;
}

int fileContainers(int argc, char **argv, std::list<int> &theList, std::deque<int> &theDeque){
    for (int index = 1; index < argc; index++){
        if (!stdIsDigit(argv[index])){
            std::cerr << "Error: Isn't digit."; 
            return 0;
        }
        int num = std::atoi(argv[index]);
        if (!check_double(theList, num))
        {
            std::cerr << "Error: Identique argument."; 
            return 0;
        }
        theList.push_back(num);
        theDeque.push_back(num);
    }
    return 1;
}

int main (int argc, char **argv){
    if (argc == 1){
        std::cerr << "Need arguments ./PmergeMe number...";
    }
    std::list<int> theList;
    std::deque<int> theDeque;
    if(!fileContainers(argc, argv, theList, theDeque))
        return 1;
    printList(theList);
    std::clock_t start_L = std::clock();
    sortingList(theList);
    std::clock_t end_L = std::clock();
    std::clock_t start_D = std::clock();
    sortingDeque(theDeque);
    std::clock_t end_D = std::clock();
    printDeque(theDeque);
    std::cout << "Time to process a range of " << theDeque.size() << " elements with std::list : "
        << std::fixed << std::setprecision(5) << (double)(end_L - start_L) * 100 / CLOCKS_PER_SEC << "ms" << std::endl;
    std::cout << "Time to process a range of " << theDeque.size() << " elements with std::dque : "
        << std::fixed << std::setprecision(5) << (double)(end_D - start_D) * 100 / CLOCKS_PER_SEC << "ms" << std::endl;
    return 0;
}