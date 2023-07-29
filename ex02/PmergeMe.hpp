/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:29:29 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/28 22:19:34 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef P_MERGE_ME_HPP
# define P_MERGE_ME_HPP

# include <stack>
# include <iostream>
# include <string>
# include <list>
# include <vector>
# include <exception>
# include <cmath>
//# include <string>

enum	e_container_type
{
	LIST_C,
	VECT_C,
};

class PmergeMe
{
	private:
		std::list<int>		L;
		std::vector<int>	V;

		int					N, k;
		
		void	insersion_sort_list(int start, int end);
		void	insersion_sort_vect(int start, int end);
		void	merge_vect(int start, int mid, int end);
		void	merge_list(int start, int mid, int end);
	
		void	_sort_list(int start, int end);
		void	_sort_vect(int start, int end, int depth);



	public:
		PmergeMe(void);
		PmergeMe(const PmergeMe& other);
		PmergeMe&	operator=(const PmergeMe& other);
		~PmergeMe(void);

		bool	add_sequence_from_strs(char **strs_sequence, e_container_type ctype);
		void	print_sequence(e_container_type ctype);
		void	sort(e_container_type ctype);
};

#endif