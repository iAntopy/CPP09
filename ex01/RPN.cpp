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

/// Error handling and utils
bool	print_error(const std::string& msg)
{
	if (!msg.empty())
		std::cerr << "Error: " << msg << std::endl;
	else
		std::cerr << "Error" << std::endl;
	return (false);
}

bool	print_error(const std::string& msg, const std::string& op)
{
	if (!msg.empty())
		print_error("");
	else
	{
		std::cerr << "Error: " << msg << " " << op << std::endl;
	}
	return (false);
}

bool	extract_operands(std::stack<int>& operands, int& op1, int& op2)
{
	if (operands.empty())
		return (false);
	op2 = operands.top();
	operands.pop();
	if (operands.empty())
		return (false);
	op1 = operands.top();
	operands.pop();
	return (true);
}


////// Operator functions
bool	RPN::add(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
	operands.push(op1 + op2);
	return (true);
}

bool	RPN::sub(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
	operands.push(op1 - op2);
	return (true);
}

bool	RPN::mul(std::stack<int>& operands)
{
	int		op1, op2;

	if (!extract_operands(operands, op1, op2))
		return (print_error("Missing operands"));
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
	operands.push(op1 / op2);
	return (true);
}

bool	RPN::_exec_operator(char opr, std::stack<int>& solver_stack)
{
	switch (opr)
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
			std::cerr << "Error: Invalid operand or operator found: " << opr << std::endl;
			return (false);
	}
	return (true);
}



/// Constructors / Destructors / Copy
RPN::RPN(void)
{
}

RPN::RPN(const RPN& other)
{
	if (this != &other)
		*this = other;
}

RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
		*this = other;
	return (*this);
}

RPN::~RPN(void)
{
}


/// Solver
bool	RPN::solve(const std::string& ops, int& solution)
{
	std::stack<int>	solver_stack;
	std::string		op;
	size_t			pos1 = 0, pos2 = 0;

	while ((pos1 = ops.find_first_not_of(' ', pos2)) != ops.npos)
	{
		if ((pos2 = ops.find(' ', pos1)) == ops.npos)
			op = ops.substr(pos1);
		else
			op = ops.substr(pos1, pos2 - pos1);
		if (op.length() > 1)
			return (print_error("Error: Invalid operand or operator found: ", op));
		if (std::isdigit(op[0]))
			solver_stack.push(std::stoi(op));
		else if (!_exec_operator(op[0], solver_stack))
			return (false);
	}
	if (solver_stack.empty())
		return (print_error("Nothing to solve"));
	solution = solver_stack.top();
	return (true);
}
