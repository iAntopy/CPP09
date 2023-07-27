/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:24:35 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/26 23:54:14 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool
BitcoinExchange::validate_date_string(const std::string& cmp, const struct tm& cmp_tm) const
{
	std::ostringstream	os;
	std::string			conv_date;

	os << std::put_time(&cmp_tm, "%Y-%m-%d");
	conv_date = os.str();
	std::cout << "conv date : " << conv_date << std::endl;
	
	return (cmp == conv_date);
}

int
BitcoinExchange::load_exchange_rates(const std::string& db_path) 
{
	std::ifstream	csv_file;
	std::string		next_line;
	std::string		date_str;
	std::string		amount_str;
	size_t			pos;
	struct tm		date_tm;
	time_t			t;
	float			ex_rate;

	std::cout << "Loady McLoadington" << std::endl;
	csv_file.open(db_path, std::ios::in);
	if (!csv_file.is_open())
		return (-1);

	if (!std::getline(csv_file, next_line, '\n').good())
	{
		std::cerr << "Failed to read exchange rates history file." << std::endl;
		return (-1);
	}
	
	while (!std::getline(csv_file, next_line, '\n').eof())
	{
		pos = next_line.find(',');
		date_str = next_line.substr(0, pos);
		amount_str = next_line.substr(pos + 1, next_line.length() - pos);
		
//		std::cout << "date: " << date_str << " | value: " << amount_str << std::endl;
		if (strptime(date_str.c_str(), "%Y-%m-%d", &date_tm) == NULL)
		{
        	std::cerr << " - strptime failed" << std::endl;
			continue ;
		}
		if (!validate_date_string(date_str, date_tm))
		{
			std::cerr << "WOW ! date string INVALID !" << std::endl;
			return (-1);
		}
		
		t = mktime(&date_tm);
		try { ex_rate = std::stof(amount_str); }
		catch (std::exception &e)
		{
			std::cerr << "Failed to convert database exchange rate to float " << std::endl;
			continue ;
		}

		// Exchange rate extracted and validated. Finally put in map of exchange rates.
		_exchange_rates[t] = ex_rate;
	}
	std::cout << "Parsed database SUCCESSFULLY." << next_line << std::endl;

	csv_file.close();
	return (0);
}

bool
BitcoinExchange::get_historical_value(const std::string& query,
	std::string& ex_date, float& total_value) const
{
	size_t		pos, end_pos;
//	std::string	date_str;
	struct tm	date_tm;

	pos = query.find_first_of(" \n");
	if (pos == query.npos)
	{
		std::cerr << "query string empty" << std::endl;
		return (false);
	}
	ex_date = query.substr(pos);
	if (strptime(ex_date.c_str(), "%Y-%m-%d", &date_tm) == NULL
		|| !validate_date_string(ex_date, date_tm))
	{
		std::cerr << "Error: bad input => " << ex_date << std::endl;
		return (false);
	}
	pos = query.find_first_not_of(" |", pos);
	end_pos = query.find('\n', pos);
		
}


BitcoinExchange::BitcoinExchange(void)
{
	std::cout << "BitcoinExchange constructor" << std::endl;
	if (load_exchange_rates(CSV_PATH) < 0)
		throw std::invalid_argument("Failed to load exchange rates database.");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	std::cout << "BitcoinExchange copy constructor" << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other)
{
	std::cout << "BitcoinExchange copy assignment operator" << std::endl;
	_exchange_rates.clear();
	_exchange_rates = other._exchange_rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
	std::cout << "BitcoinExchange destructor" << std::endl;
}