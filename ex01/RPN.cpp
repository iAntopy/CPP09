/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:24:31 by marvin            #+#    #+#             */
/*   Updated: 2023/07/28 03:24:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool	print_error(const std::string& msg)
{
	if (!msg.empty())
		std::cerr << "Error: " << msg << std::endl;
	else
		std::cerr << "Error" << std::endl;
	return (false);
}

bool	print_error(void)
{
	return (print_error(""));
}

bool	extract_operands(std::stack<int>& operands, int& op1, int& op2)
{
	if (operands.empty())
		return (false);//print_error("Operands empty"));
	op2 = operands.top();
	operands.pop();
	if (operands.empty())
		return (false);//print_error("Operands empty"));
	op1 = operands.top();
	operands.pop();
	return (true);
}

bool	RPN::add(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
//	std::cout << "+ extracted operands : op1 " << op1 << ", op2 " << op2 << std::endl;
	operands.push(op1 + op2);
	return (true);
}

bool	RPN::sub(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
//	std::cout << "- extracted operands : op1 " << op1 << ", op2 " << op2 << std::endl;
	operands.push(op1 - op2);
	return (true);
}

bool	RPN::mul(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
//	std::cout << "* extracted operands : op1 " << op1 << ", op2 " << op2 << std::endl;
	operands.push(op1 * op2);
	return (true);
}

bool	RPN::div(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
	if (op2 == 0)
		return (print_error("Div by zero"));
//	std::cout << "/ extracted operands : op1 " << op1 << ", op2 " << op2 << std::endl;
	operands.push(op1 / op2);
	return (true);
}




RPN::RPN(void)
{
//	std::cout << "RPN default constructor" << std::endl;
}

RPN::RPN(const RPN& other)
{
//	std::cout << "RPN copy constructor" << std::endl;
}

RPN&	RPN::operator=(const RPN& other)
{
//	std::cout << "RPN copy assignment operator" << std::endl;
	return (*this);
}

RPN::~RPN(void)
{
//	std::cout << "RPN destructor" << std::endl;
}

bool	RPN::solve(const std::string& operations, int& solution)
{
	std::stack<int>	solver_stack;
	std::string		ops = operations;
	std::string		op;
	int				iop;
	size_t			pos;

	while (!ops.empty())
	{
		pos = ops.find(' ');
		if (pos == ops.npos)
		{
			op = ops;
			ops = "";			
		}
		else
		{
			op = ops.substr(0, pos);
			ops = ops.substr(ops.find_first_not_of(' ', pos));
		}
		if (op.length() > 1)
		{
			std::cerr << "Error: Invalid operand or operator found: " << op << std::endl;
			return (false);
		}
		if (std::isdigit(op[0]))
		{
			iop = std::stoi(op);
			solver_stack.push(iop);
			continue ;
		}
		switch (op[0])
		{
			case '+':
				if (!add(solver_stack))
					return (false);
				break ;
			case '-':
				if (!sub(solver_stack))
					return (false);
				break ;
			case '*':
				if (!mul(solver_stack))
					return (false);
				break ;
			case '/':
				if (!div(solver_stack))
					return (false);
				break ;
			default:
				std::cerr << "Error: Invalid operand or operator found: " << op << std::endl;
				return (false);//: encountered invalid operator"));
		}
	}

	if (solver_stack.empty())
		return (print_error());
//	std::cout << "top at exit: " << solver_stack.top() << std::endl;
//	if (solver_stack.size() > 1)
//		return (print_error("Stack still holding some operands"));
	solution = solver_stack.top();
	return (true);
}
