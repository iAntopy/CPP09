/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 03:34:30 by marvin            #+#    #+#             */
/*   Updated: 2023/07/28 03:34:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	RPN math_solver;
	int solution;

	if (argc < 2)
	{
		std::cerr << "Error: Missing argument." << std::endl;
		return (EXIT_FAILURE);
	}
	solution = math_solver.solve(argv[1]);
	return (0);
}