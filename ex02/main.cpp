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

#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	PmergeMe sorter;

	if (argc < 2)
	{
		std::cerr << "Error: Missing int sequence as argument." << std::endl;
		return (EXIT_FAILURE);
	}
//	const int arr[] = {1, 2, 3, 4};
//	std::vector<int> 	v(arr, arr + sizeof(arr) / sizeof(arr[0]) );
//	std::vector<int>	tv(v.begin() + 1, v.begin() + 3);
//	std::cout << tv[0] << ", " << tv[1];
	sorter.add_sequence_from_strs(argv + 1, VECT_C);
	sorter.print_sequence(VECT_C);
	sorter.sort(VECT_C);
	sorter.print_sequence(VECT_C);

	return (0);
}