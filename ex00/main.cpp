/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:20:49 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/27 05:03:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	clean_exit(const std::string& err_msg, std::fstream& ifile, int status)
{
	if (!err_msg.empty())
		std::cerr << err_msg << std::endl;

	if (ifile.is_open())
		ifile.close();
	return (status);
}

int main(int argc, char **argv)
{
	BitcoinExchange	ftx;
	std::fstream	input_file;
	std::string		query;// = "2014-04-28 | 1.25";
	std::string		init_data, ex_date, value;
	float			ex_rate, total_value;

	if (argc < 2)
		return (clean_exit("Error: Missing input file.", input_file, EXIT_FAILURE));

	input_file.open(argv[1], std::ios::in);
	if (!input_file.is_open())
		return (clean_exit("Error: Failed to open input file.", input_file, EXIT_FAILURE));

	while (!std::getline(input_file, query, '\n').fail())
	{
		if (query == "date | value")
			continue ;
		if (!ftx.get_historical_value(query, init_data, ex_date, value, ex_rate, total_value))
			continue ;
			//return (clean_exit("", input_file, EXIT_FAILURE));
		std::cout << init_data << " => " << value << " = " << total_value << std::endl;
	//	std::cout << "ex_date : " << ex_date << ", ex_rate : " << ex_rate << ", total value : " << total_value << std::endl;	
	}
	input_file.close();
	//if (!ftx.get_historical_value(query, ex_date, ex_rate, total_value))
	//	return (1);
	//std::cout << "ex_date : " << ex_date << ", ex_rate : " << ex_rate << ", total value : " << total_value << std::endl;
	return (0);
}