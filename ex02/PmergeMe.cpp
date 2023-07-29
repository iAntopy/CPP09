/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iamongeo <iamongeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 19:30:28 by iamongeo          #+#    #+#             */
/*   Updated: 2023/07/28 19:30:28 by iamongeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool	print_error()
{
	std::cerr << "Error";
	return (false);
}


bool	print_error(const std::string& msg)
{
	print_error();
	if (!msg.empty())
		std::cerr << ": " << msg;
	std::cout << std::endl;
	return (false);
}

bool
validate_all_digits(const std::string& s)
{
	const size_t	n = s.length();

	for(size_t i=0; i < n; ++i)
		if (!std::isdigit(s[i]))
			return (false);
	return (true);
}

void
PmergeMe::print_sequence(e_container_type ctype)
{
	if (ctype == LIST_C)
	{
		std::list<int>::iterator	it;

		for (it = L.begin(); it != L.end(); ++it)
			std::cout << *it << " ";
	}
	else
	{
		std::vector<int>::iterator	it;

		for (it = V.begin(); it != V.end(); ++it)
			std::cout << *it << " ";
	}
	std::cout << std::endl;
}



PmergeMe::PmergeMe(void)
{
	std::cout << "PmergeMe default constructor" << std::endl;
}

PmergeMe::PmergeMe(const PmergeMe& other)
{
	std::cout << "PmergeMe copy constructor" << std::endl;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other)
{
	std::cout << "PmergeMe copy assignment operator" << std::endl;
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
	std::cout << "PmergeMe destructor" << std::endl;
}

bool
validate_input_int(const std::string& sn, ssize_t& n)
{

	if (!validate_all_digits(sn))
		return (print_error("Non digit argument found"));
	n = std::stol(sn);
	if (n < 0)
		return (print_error("Negative integers"));
	else if (INT_MAX < n)
		return (print_error("Integer > INT_MAX"));
	return (true);
}

bool
PmergeMe::add_sequence_from_strs(char **strs_sequence, e_container_type ctype)
{
	char			**s;
	std::string		sn;
	ssize_t			n;

	if (!strs_sequence)
		return (print_error("No sequence of integer strings given"));
	s = strs_sequence - 1;
	if (ctype == LIST_C)
	{
		while (*(++s))
		{
			if (!validate_input_int(*s, n))
				return (false);
			L.push_back(n);
		}
	}
	else
	{
		while (*(++s))
		{
			std::cout << "adding: " << *s << std::endl;
			if (!validate_input_int(*s, n))
				return (false);
			V.push_back(n);
		}
	}
//	print_sequence();
	return (true);
}



void
PmergeMe::insersion_sort_list(int start, int end)
{

}


void
PmergeMe::insersion_sort_vect(int start, int end)
{
	int	i, j;
	int	temp;

	std::cout << "Big inserts. start - end: " << start << "-" << end << std::endl;

	for (i=start; i < (end - 1); ++i)
	{
		j = i + 1;
		temp = V[j];
//		std::cout << "i, j: " << i << ", " << j << ", temp: " << temp << std::endl;
		while (j > start && V[j - 1] > temp)
		{
			V[j] = V[j - 1];
			--j;
		}
///		std::cout << "Putting temp " << temp << " at j " << j << std::endl;
		V[j] = temp;
		print_sequence(VECT_C);
	}	
}

void
PmergeMe::merge_list(int start, int mid, int end)
{
	
}

void
quicky_print_vect(const std::vector<int>& v)
{
	std::vector<int>::const_iterator	it;

	std::cout << "quicky vect : ";
	for (it = v.begin(); it + 1 != v.end(); ++it)
	{
		std::cout << *it << ", ";
	}
	std::cout << *it << std::endl;
}

void
PmergeMe::merge_vect(int start, int mid, int end)
{
	int	i, l, r;
	std::vector<int>	tv(V.begin() + start, V.begin() + end);
	const int	tmid = mid - start;
	const int	tend = end - start;

	std::cout << "merge: start, mid, end : " << start << ", " << mid << ", " << end << std::endl;
	std::cout << "merge: tmid, tend : " << tmid << ", " << tend << std::endl;
	quicky_print_vect(tv);
	i = start;			// index inside real array V
	l = 0;				// index inside segment copy tv.
	r = tmid;			// index inside segment copy tv.
	std::cout << "i, l, r: " << i << ", " << l << ", " << r << std::endl;
	for (i = start; i < end; ++i)
	{
		std::cout << "tv[l] vs tv[r] : " << tv[l] << " vs " << tv[r] << std::endl;
		if (r == tend)
		{
			std::cout << "l < r => V[" << i << "] becomes : "<< tv[l] << std::endl;
			V[i] = tv[l++];
		}
		else if (l == tmid)
		{
			std::cout << "l < r => V[" << i << "] becomes : "<< tv[l] << std::endl;
			V[i] = tv[r++];
		}
		else if (tv[l] < tv[r])
		{
			std::cout << "l < r => V[" << i << "] becomes : "<< tv[l] << std::endl;
			V[i] = tv[l++];
		}
		else if (tv[r] < tv[l])
		{
			std::cout << "l < r => V[" << i << "] becomes : "<< tv[l] << std::endl;
			V[i] = tv[r++];
		}
	}
	std::cout << "vect after merge exit :" << std::endl;
	quicky_print_vect(V);
}

void
PmergeMe::_sort_list(int start, int end)
{
	int	mid = (end - start) / 2;


}

void
PmergeMe::_sort_vect(int start, int end, int depth)
{
	int	n = (end - start);
	int	mid = start + (n / 2);

	if (depth == 5)
		exit(1);
	if (n > k)
	{
		std::cout << "n > k => n: "<< n << ", k: " << k << ", depth: " << depth << std::endl;
		std::cout << std::endl << "sort1 => start " << start << ", end "<<  mid << std::endl;
		_sort_vect(start, mid, depth + 1);
		std::cout << std::endl << "sort2 => start " << mid << ", end " << end << std::endl;
		_sort_vect(mid, end, depth + 1);
		std::cout << std::endl << "merging at depth : " << depth << std::endl;
		merge_vect(start, mid, end);
	}
	else
	{
		std::cout << "n <= k => n: "<< n << ", k: " << k << ", depth: " << depth << std::endl;
		insersion_sort_vect(start, end);
	}
}

void
PmergeMe::sort(e_container_type ctype)
{
	if (ctype == LIST_C)
	{
		N = L.size();
		k = static_cast<int>(std::log2(N));
		if (N < 2)
			return ;
		_sort_list(0, N);
	}
	else
	{
		N = V.size();
		k = 1;//static_cast<int>(std::log2(N));
		if (N < 2)
			return ;
		_sort_vect(0, N, 0);
	}
}