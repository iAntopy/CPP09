/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:21:12 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/26 23:43:15 by iamongeo         ###   ########.fr       */
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
# include <iomanip>

# define CSV_PATH   "data.csv"

class BitcoinExchange
{
	private:
		std::map<time_t, float>	_exchange_rates;
		
		int		load_exchange_rates(const std::string& db_path);
		bool	validate_date_string(const std::string& cmp, const struct tm& cmp_tm) const;
		bool	get_historical_value(const std::string& query, std::string& ex_date, float& total_value) const;

	public:
		BitcoinExchange(void);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&    operator=(const BitcoinExchange& other);
		~BitcoinExchange(void);
};

#endif