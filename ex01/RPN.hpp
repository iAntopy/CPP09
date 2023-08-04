/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:23:18 by marvin            #+#    #+#             */
/*   Updated: 2023/08/03 20:59:25 by iamongeo         ###   ########.fr       */
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
		
		bool	_exec_operator(char opr, std::stack<int>& solver_stack);

	public:
		RPN(void);
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other);
		~RPN(void);

		bool	solve(const std::string& operations, int& solution);
};

#endif