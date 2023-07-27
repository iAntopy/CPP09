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

void	print_original_sequence(char **tab)
{
	char	**s = tab;

	while (*(++s))
		std::cout <<  *s << " ";
	std::cout << std::endl;
}

int main(int argc, char **argv)
{
	PmergeMe	sorter;
	float		vect_attribution_time;
	float		vect_sort_time;
	float		vect_total_time;
	float		list_attribution_time;
	float		list_sort_time;
	float		list_total_time;

	if (argc < 2)
	{
		std::cerr << "Error: Missing int sequence as argument." << std::endl;
		return (EXIT_FAILURE);
	}

//// VECTOR
	sorter.timer_probe();
	if (!sorter.add_sequence_from_strs(argv + 1, VECT_C))
		return (EXIT_FAILURE);
	sorter.timer_probe();
	vect_attribution_time = sorter.get_delta_time();
	sorter.sort(VECT_C);
	sorter.timer_probe();
	vect_sort_time = sorter.get_delta_time();
	vect_total_time = vect_attribution_time + vect_sort_time;


///// LISTS
	sorter.timer_probe();
	if (!sorter.add_sequence_from_strs(argv + 1, LIST_C))
		return (EXIT_FAILURE);
	sorter.timer_probe();
	list_attribution_time = sorter.get_delta_time();
	sorter.sort(LIST_C);
	sorter.timer_probe();
	list_sort_time = sorter.get_delta_time();
	list_total_time = list_attribution_time + list_sort_time;

///// VALIDATION
	if (!sorter.both_containers_equal())
	{
		std::cerr << "OOPS ! Both containers are NOT equal." << std::endl;
		return (EXIT_FAILURE);
	}
	else if (!sorter.containers_are_sorted())
	{
		std::cerr << "OOPS ! Both containers are NOT sorted." << std::endl;
		return (EXIT_FAILURE);
	}

///// CONCLUSION
	std::cout << "Before:	";
	print_original_sequence(argv);
	std::cout << "After:	";
	sorter.print_sequence(VECT_C);
	std::cout << "Time to process a range of " << sorter.size(VECT_C) << " elements with std::vector<int>:	" << vect_total_time << " us. (" << vect_attribution_time << " us for data collection. " << vect_sort_time << " us for sorting)" << std::endl;
	std::cout << "Time to process a range of " << sorter.size(LIST_C) << " elements with std::list<int>:	" << list_total_time << " us. (" << list_attribution_time << " us for data collection. " << list_sort_time << " us for sorting)" << std::endl;
	return (0);
}