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
		if (!isdigit(s[i]))
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


PmergeMe::PmergeMe(void): timer_ready(false), N(0), k(0)
{
}

PmergeMe::PmergeMe(const PmergeMe& other): timer_ready(false), N(other.N), k(other.k)
{
	L = other.L;
	V = other.V;
}

PmergeMe&	PmergeMe::operator=(const PmergeMe& other)
{
	return (*this);
}

PmergeMe::~PmergeMe(void)
{
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
	size_t			seq_len = 0;
	ssize_t			n;

	if (!strs_sequence)
		return (print_error("No sequence of integer strings given"));
	s = strs_sequence - 1;
	while (*(++s))
		++seq_len;
	V.reserve(seq_len);
	V2.reserve(seq_len);
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
			if (!validate_input_int(*s, n))
				return (false);
			V.push_back(n);
			V2.push_back(n);
		}
	}
	return (true);
}


//// SORTING METHODS (LIST)
void
PmergeMe::merge_list(int start, int mid, int end)
{
	std::list<int>::iterator	st, it, mi, ed;

	st = L.begin();
	std::advance(st, start);
	mi = st;
	std::advance(mi, mid - start);
	ed = mi;
	std::advance(ed, end - mid);

	while (!(st == mi || mi == ed))
	{
		if (*st <= *mi)
			++st;
		else
		{
			it = mi;
			++it;
			L.splice(st, L, mi);
			mi = it;
		}
	}
}

void
PmergeMe::insersion_sort_list(int start, int end)
{
	std::list<int>::iterator	st, s, si, it, ed;
	int i, n;
	int	temp;

	n = end - start - 1;
	for (int i=0; i < n; ++i)
	{
		st = L.begin();
		std::advance(st, start);
		si = st;
		std::advance(si, i);
		ed = si;
		std::advance(ed, n - i);
		it = ++si;
		temp = *si;
		while (it != st && *(--it, it++) > temp)
			--it;
		if (it == si)
			continue ;
		L.splice(it, L, si);// move container of compared elem at pos si to pos it which is the first place found in list where previous elem is smaller.
	}
}

void
PmergeMe::_sort_list(int start, int end)
{
	int	n = (end - start);
	int	mid = start + (n / 2);

	if (n > k)
	{
		_sort_list(start, mid);
		_sort_list(mid, end);
		merge_list(start, mid, end);
	}
	else
		insersion_sort_list(start, end);
}


//// SORTING METHODS (VECTOR)
void
PmergeMe::merge_vect(int start, int mid, int end)
{
	int					i, l, r;

	std::copy(V.begin() + start, V.begin() + end, V2.begin() + start);
	i = start;	// index inside real array V
	l = start;	// index inside segment copy V2.
	r = mid;	// index inside segment copy V2.
	for (i = start; i < end; ++i)
	{
		if (r == end)
			V[i] = V2[l++];
		else if (l == mid)
			V[i] = V2[r++];
		else if (V2[l] < V2[r])
			V[i] = V2[l++];
		else
			V[i] = V2[r++];
	}
}

void
PmergeMe::insersion_sort_vect(int start, int end)
{
	int	i, j;
	int	temp;

	for (i=start; i < (end - 1); ++i)
	{
		j = i + 1;
		temp = V[j];
		while (j > start && V[j - 1] > temp)
		{
			V[j] = V[j - 1];
			--j;
		}
		V[j] = temp;
	}
}

void
PmergeMe::_sort_vect(int start, int end)
{
	int	n = (end - start);
	int	mid = start + (n / 2);

	if (n > k)
	{
		_sort_vect(start, mid);
		_sort_vect(mid, end);
		merge_vect(start, mid, end);
	}
	else
		insersion_sort_vect(start, end);
}

void
PmergeMe::sort(e_container_type ctype)
{
	if (ctype == LIST_C)
	{
		N = L.size();
//		k = 1;//			run in pure merge sort mode
//		k = N;//			run in pure insert sort mode
		k = (int)log2(N);//	run in optimized merge-insert sort mode
		if (N < 2)
			return ;
		_sort_list(0, N);
	}
	else
	{
		N = V.size();
//		k = 1;//			run in pure merge sort mode
//		k = N;//			run in pure insert sort mode
		k = (int)log2(N);//	run in optimized merge-insert sort mode
		if (N < 2)
			return ;
		_sort_vect(0, N);
	}
}


uint32_t
PmergeMe::size(e_container_type ctype)
{
	if (ctype == LIST_C)
		return (L.size());
	else
		return (V.size());
}

void
PmergeMe::timer_probe(void)
{
	struct timespec	curr_time;

	if (clock_gettime(CLOCK_MONOTONIC, &curr_time) < 0)
	{
		print_error("clock_gettime() failed");
		return ;
	}
	if (!timer_ready)
		timer_ready = true;
	else
	{
		delta_time = (curr_time.tv_sec - ori_time.tv_sec) * 1000000;
		delta_time += curr_time.tv_nsec - ori_time.tv_nsec;
	}
	ori_time = curr_time;
}

float
PmergeMe::get_delta_time(void)
{
	float	ret = static_cast<float>(delta_time);
	return (ret / 1000);
}


/// VALIDATION METHODS
bool
PmergeMe::both_containers_equal(void)
{
	std::vector<int>::iterator	vi = V.begin();
	std::list<int>::iterator	li = L.begin();

	if (V.size() != L.size())
		return (false);
	while (vi != V.end())
		if (*(vi++) != *(li++))
			return (false);
	return (true);
}

bool
PmergeMe::containers_are_sorted(void)
{
	std::vector<int>::iterator	vi = V.begin();

	if (!both_containers_equal())
		return (false);
	for (; (vi + 1) != V.end(); ++vi)
		if (*vi > *(vi + 1))
			return (false);
	return (true);
}
