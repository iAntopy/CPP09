/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:24:35 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/28 03:14:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

void	time_to_date_str(const struct tm& t, std::string& ret_date_str)
{
	std::ostringstream	os;
	std::string			conv_date;

	os << std::put_time(&t, "%Y-%m-%d");
	ret_date_str = os.str();
}

bool
validate_date_string(const std::string& cmp, struct tm& cmp_tm)
{
	std::ostringstream	os;
	std::string			conv_date;
	time_t				t = mktime(&cmp_tm);
	struct tm*			temp_tm;

	temp_tm = std::localtime(&t);

//	os << std::put_time(temp_tm, "%Y-%m-%d");
//	conv_date = os.str();
//	std::cout << "conv date : " << conv_date << std::endl;
	time_to_date_str(*temp_tm, conv_date);
	if (cmp != conv_date)
		return (false);
	cmp_tm = *temp_tm;
	//std::cout << "Validating date string : " << cmp << " == converted date string : " << conv_date << std::endl;
	return (true);
}

bool
validate_amount_float(float value)
{
	if (value < 0.0f)
	{
		std::cerr << "Error: not a positive number." << std::endl;
		return (false);
	}
	else if (value > 1000.0f)
	{
		std::cerr << "Error: too large a number." << std::endl;
		return (false);
	}
	return (true);
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

//	std::cout << "Loady McLoadington" << std::endl;
	csv_file.open(db_path, std::ios::in);
	if (!csv_file.is_open())
		return (-1);

	if (!std::getline(csv_file, next_line, '\n').good())
	{
		std::cerr << "Failed to read exchange rates history file." << std::endl;
		return (-1);
	}
	
	while (!std::getline(csv_file, next_line, '\n').fail())
	{
		pos = next_line.find(',');
		date_str = next_line.substr(0, pos);
		amount_str = next_line.substr(pos + 1, next_line.length() - pos);
		
		std::memset(&date_tm, 0, sizeof(date_tm));

//		std::cout << "date: " << date_str << " | value: " << amount_str << std::endl;
		if (strptime(date_str.c_str(), "%Y-%m-%d", &date_tm) == NULL
			|| !validate_date_string(date_str, date_tm))
		{
			std::cerr << "Error: Invalid Date" << date_str << std::endl;
			continue ;
		}
		
		t = mktime(&date_tm);
		try { ex_rate = std::stof(amount_str); }
		catch (std::exception &e)
		{
			std::cerr << "Error: Failed to convert exchange rate to float " << std::endl;
			continue ;
		}

		// Exchange rate extracted and validated. Finally put in map of exchange rates.
		_exchange_rates[t] = ex_rate;
	}
//	std::cout << "Parsed database SUCCESSFULLY." << next_line << std::endl;

	csv_file.close();
	return (0);
}

bool
BitcoinExchange::exchange_rate_lookup(struct tm& date_tm, float& rate_found) const
{
	std::map<time_t, float>::const_iterator	it;
	time_t		q_time = mktime(&date_tm), t;
	//struct tm	*ex_time;
	//std::cout << "q_time lookup : " << q_time << std::endl; 

	it = _exchange_rates.lower_bound(q_time);
//	if (it == _exchange_rates.end())
//	{
//		std::cerr << "Exchange lookup couldn't eaven find a lower bound date. What a shame." << std::endl;
//		return (false);
//	}
	t = it->first;
	
	if (t != q_time && it != _exchange_rates.begin())
		t = (--it)->first;
	date_tm = *std::localtime(&t);
	rate_found = it->second;
	return (true);
}

bool
BitcoinExchange::get_historical_value(const std::string& query,
	std::string& init_date, std::string& ex_date, std::string& value,
	float& ex_rate, float& total_value) const
{
	size_t		pos, end_pos;
	std::string	amount_str;
	struct tm	date_tm{};
	time_t		t;
	float		amount;

	//std::memset(&date_tm, 0, sizeof(date_tm));
	ex_date = "";
	value = "";
	ex_rate = 0;
	total_value = 0;
//	std::cout << "query string : " << query << std::endl;
	pos = query.find_first_of(' ');
	if (pos == query.npos)
	{
		pos = query.length();
//		std::cerr << "query string empty : " << query << std::endl;
//		return (false);
	}
	init_date = query.substr(0, pos);
//	std::cout << "Converting ex_date " << ex_date << " to date_tm." << std::endl;
	if (strptime(init_date.c_str(), "%Y-%m-%d", &date_tm) == NULL
		|| !validate_date_string(init_date, date_tm))
	{
		std::cerr << "Error: bad input => " << init_date << std::endl;
		return (false);
	}


	pos = query.find_first_not_of(" |", pos);
	amount_str = query.substr(pos);
	try	{ amount = std::stof(amount_str); }
	catch (std::exception &e)
	{
		std::cerr << "Error: Failed to convert database exchange rate to float " << std::endl;
		return (false);
	}
	if (!validate_amount_float(amount) || !exchange_rate_lookup(date_tm, ex_rate))
		return (false);
	time_to_date_str(date_tm, ex_date);
	value = amount_str;
	total_value = amount * ex_rate;
	return (true);
}


BitcoinExchange::BitcoinExchange(void)
{
//	std::cout << "BitcoinExchange constructor" << std::endl;
	if (load_exchange_rates(CSV_PATH) < 0)
		throw std::invalid_argument("Failed to load exchange rates database.");
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): _exchange_rates(other._exchange_rates)
{
//	std::cout << "BitcoinExchange copy constructor" << std::endl;
}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& other)
{
//	std::cout << "BitcoinExchange copy assignment operator" << std::endl;
	_exchange_rates.clear();
	_exchange_rates = other._exchange_rates;
	return (*this);
}

BitcoinExchange::~BitcoinExchange(void)
{
//	std::cout << "BitcoinExchange destructor" << std::endl;
}