/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:21:12 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/27 04:50:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <map>
#include <ctime>

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <cstring>
# include <iomanip>

# define CSV_PATH   "data.csv"

class BitcoinExchange
{
	private:
		std::map<time_t, float>	_exchange_rates;
		
		int		load_exchange_rates(const std::string& db_path);
//		bool	validate_date_string(const std::string& cmp, const struct tm& cmp_tm) const;
		bool	exchange_rate_lookup(struct tm& date_tm, float& rate_found) const;
		//bool	exchange_rate_lookup(struct tm& date_tm, time_t& ex_time, float& rate_found) const

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&    operator=(const BitcoinExchange& other);
		~BitcoinExchange(void);
		
		bool	get_historical_value(const std::string& query, std::string& init_date, std::string& ex_date, std::string& value, float& ex_rate, float& total_value) const;
};

#endif