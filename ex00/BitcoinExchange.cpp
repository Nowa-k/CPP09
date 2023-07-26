/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:28:53 by aleferra          #+#    #+#             */
/*   Updated: 2023/07/26 17:04:21 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int isMax(std::string line){
    if (line.size() > 10)
        return 0;
    if (line.size() == 10 && line.compare("2147483647") > 0)
        return 0;
    return 1;
}

int strIsDigit(std::string line){
    int point = 0;
    for (size_t index = 0; index < line.size(); index++)
    {
        if (!std::isdigit(line[index]) && line[index] != '.')
            return 0;
        if (line[index] == '.'){
            point++;
            if (point == 2)
                return 0;
            if (!line[index + 1])
                return 0;
        }
    }
    return 1;
}

float toFloat(std::string line){
    float value;
    line = line.substr(line.find(',') + 1);
    std::stringstream ss(line);
    ss >> value;
    return value; 
}

int findValideDate(std::string line, std::string &date){
    if (line.find('|') == std::string::npos)
        return 0;
    date = line.substr(0, line.find('|'));
    if (date.size() != 11)
        return 0;
    float dateFloat;
   
    std::string dateString = date.substr(0, 4);
    dateFloat = toFloat(dateString);
    if (!strIsDigit(dateString))
        return 0;
    if (dateFloat < 2009 || dateFloat > 2022)
        return 0;
        
    dateString = date.substr(5, 2);
    dateFloat = toFloat(dateString);
    if (dateFloat < 0 || dateFloat > 12)
        return 0;
        
    dateString = date.substr(8, 2);
    dateFloat = toFloat(dateString);
    if (dateFloat < 0 || dateFloat > 31)
        return 0;
    return 1;
}

int findNbBtc(std::string line, std::string &beforeValue, float &nbBtc){
    line = line.substr(line.find('|') + 1);
    if (line.find(' ') == 0)
        line = line.substr(line.find(' ') + 1);
    else {
        std::cout << "Error: invalid number." << std::endl;
        return 0;
    }
    if (!isMax(line)){
        std::cout << "Error: too large a number."<< std::endl;
        return 0;    
    }
    if (line.find('-') != std::string::npos){
        std::cout << "Error: not a positive number." << std::endl;
        return 0;
    }
    if (!strIsDigit(line)){
        std::cout << "Error: invalid number." << std::endl;
        return 0;
    }
    beforeValue = line;
    nbBtc = toFloat(line);
    return 1;
}

std::string datePart(std::string line){
    std::string date;
    date = line.substr(0, line.find(','));
    return date;
}

void fileDataMap(std::map<std::string, float> &data){
    std::string line;
    std::ifstream dataBase("data.csv");
    while (std::getline(dataBase, line))
    {
        data.insert(std::pair<std::string, float>(datePart(line), toFloat(line)));
    }
}

void affMap(std::map<std::string, float> &data){
    for(std::map<std::string, float>::iterator it = data.begin() ; it != data.end() ; ++it)
    {
       std::cout << "First  :"<< it->first << std::endl;
       std::cout << "Second :"<< it->second << std::endl;
    }
}

void findBitcoinValue(std::ifstream &inpuTxt, std::map<std::string, float> &data){
    std::string line;
    std::getline(inpuTxt, line);
    (void) data;
    if (line.find("date | value") == std::string::npos || line.length() != 12){
        std::cout << "Error: First line is false." << std::endl;
        return ;
    }
    while (std::getline(inpuTxt, line)){
        std::string date;
        std::string beforeValue;
        float nbBtc = 0;
        if (!findValideDate(line, date)){
            std::cout << "Error: bad input => " << line << std::endl;
            continue ;
        }
        if (!findNbBtc(line, beforeValue, nbBtc)){
            continue ;
        }
        float valueBtc;
        std::map<std::string, float>::iterator it = data.lower_bound(date);
        it--;
        valueBtc = nbBtc * (*it).second;
        std::cout << "Value mult : " << (*it).second << std::endl;
        std::cout << date << " => " << beforeValue << " = " << std::fixed << std::setprecision(2) << valueBtc << std::endl;
    }
}