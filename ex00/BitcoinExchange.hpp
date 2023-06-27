/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleferra <aleferra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:01:04 by aleferra          #+#    #+#             */
/*   Updated: 2023/06/26 10:42:22 by aleferra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <iomanip>

void fileDataMap(std::map<std::string, float> &data);
void affMap(std::map<std::string, float> &data);
void findBitcoinValue(std::ifstream &inpuTxt, std::map<std::string, float> &data);

#endif