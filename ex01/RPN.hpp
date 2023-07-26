/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:23:18 by marvin            #+#    #+#             */
/*   Updated: 2023/07/28 04:41:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <string>
//# include <string>

class RPN
{
	private:

		bool	add(std::stack<int>& operands);
		bool	sub(std::stack<int>& operands);
		bool	mul(std::stack<int>& operands);
		bool	div(std::stack<int>& operands);

	public:
		RPN(void);
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other);
		~RPN(void);

		int	solve(const std::string& operations);
};

#endif