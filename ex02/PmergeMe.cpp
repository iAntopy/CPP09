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



PmergeMe::PmergeMe(void): timer_ready(false)
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
//			std::cout << "adding: " << *s << std::endl;
			if (!validate_input_int(*s, n))
				return (false);
			V.push_back(n);
			V2.push_back(n);
		}
	}
//	print_sequence();
	return (true);
}



void
PmergeMe::insersion_sort_list(int start, int end)
{
	std::list<int>::iterator	st, s, si, it, ed;
	int i;
	int n;
	int	temp;
//	std::cout << "Big inserts. start - end: " << start << "-" << end << std::endl;
//	std::cout << "*st at begining : " << *st << " vs L[0] : " << *L.begin() << std::endl;

//	std::cout << "start, end values : " << *st << ", " << *ed << std::endl;
//	si = st;
	n = end - start - 1;
//	for (int i=start; i < (end - 1); ++i)
	for (int i=0; i < n; ++i)
//	for (int n=(end - start); n; ++n)
//	for (si=st; si != ed;)
	{
//		print_sequence(LIST_C);
/*
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
*/
		st = L.begin();
		std::advance(st, start);
		si = st;
		std::advance(si, i);
		ed = si;
		std::advance(ed, n - i);//end - start - 1);
		it = ++si;
		//std::advance(si, i + 1);
		temp = *si;
		while (it != st && *(--it, it++) > temp)//V[j - 1] > temp)
			--it;
		if (it == si)
			continue ;
//		std::cout << "*it end: " << *it<< std::endl;;
		L.splice(it, L, si);// move container of compared elem at pos si to pos it which is the first place found in list where previous elem is smaller.
//		L.erase(si);
//		L.insert(it, temp);
//		*it = temp;
	}
}


void
PmergeMe::insersion_sort_vect(int start, int end)
{
	int	i, j;
	int	temp;

//	std::cout << "Big inserts. start - end: " << start << "-" << end << std::endl;
//	print_sequence(VECT_C);

	for (i=start; i < (end - 1); ++i)
	{
		j = i + 1;
		temp = V[j];
//		std::cout << "i, j: " << i << ", " << j << ", temp: " << temp << std::endl;
		while (j > start && V[j - 1] > temp)
		{
//			V[j--] = V[j - 1];
			V[j] = V[j - 1];
			--j;
		}
///		std::cout << "Putting temp " << temp << " at j " << j << std::endl;
		V[j] = temp;
//		print_sequence(VECT_C);


/*
		std::vector<int>::iterator	s, si, it;
		s = (V.begin() + start);
		si = V.begin() + i + 1;
		temp = *si;
		it = si;
		while (it != s && *(it - 1) > temp)//V[j - 1] > temp)
			--it;
		//std::copy(V.begin() + start, V.begin() + end, V2.begin() + start);
		std::copy(it, si, it + 1);
		*it = temp;
*/	
	}	
//	print_sequence(VECT_C);
}

void
quicky_print_vect(const std::vector<int>& v)
{
	std::vector<int>::const_iterator	it;

	std::cout << "quicky vect (size "<<v.size()<<"): ";
	for (it = v.begin(); it + 1 != v.end(); ++it)
	{
		std::cout << *it << ", ";
	}
	std::cout << *it << std::endl;
}

void
PmergeMe::merge_list(int start, int mid, int end)
{
	std::list<int>::iterator	st, it, mi, ed;
//	std::list<int>	tl(L.begin() + start, L.begin() + end);
//	int				i, l, r;
//	const int		tmid = mid - start;
//	const int		tend = end - start;

//	std::cout << "Pretend merge list" << std::endl;
	st = L.begin();
	std::advance(st, start);
	mi = st;
	std::advance(mi, mid - start);
	ed = mi;
	std::advance(ed, end - mid);


//	std::cout << "*st, *mi, *ed before while : " << *st << ", " << *mi << ", " << *ed << std::endl;
	while (!(st == ed || mi == ed))
	{
//		if (mi == ed)
//			++st;
//		else if (st == mi)
//		print_sequence(LIST_C);
		if (*st <= *mi)
			++st;
		else
		{
			it = mi;
			++it;
//			std::cout << "*st and *mi before splice : " << *st << ", " << *mi << std::endl;
			L.splice(st, L, mi);
			mi = it;
//			std::cout << "*st and *mi after splice : " << *st << ", " << *mi << std::endl;
			//L.splice(it, L, si);			
		}
	}


/*
//	std::cout << "merge: start, mid, end : " << start << ", " << mid << ", " << end << std::endl;
//	std::cout << "merge: tmid, tend : " << tmid << ", " << tend << std::endl;
//	quicky_print_vect(tv);
	i = start;			// index inside real array V
	l = 0;				// index inside segment copy tv.
	r = tmid;			// index inside segment copy tv.
//	std::cout << "i, l, r: " << i << ", " << l << ", " << r << std::endl;
	for (i = start; i < end; ++i)
	{
//		std::cout << "tv[l="<<l<<"] vs tv[r="<<r<<"] : " << tv[l] << " vs " << tv[r] << std::endl;
		if (r == tend)
		{
//			std::cout << "r == tend => V[" << i << "] becomes : "<< tv[l] << std::endl;
			L[i] = tl[l++];
		}
		else if (l == tmid)
		{
//			std::cout << "l == tmid => V[" << i << "] becomes : "<< tv[r] << std::endl;
			L[i] = tl[r++];
		}
		else if (tl[l] < tl[r])
		{
//			std::cout << "l < r => V[" << i << "] becomes : "<< tv[l] << std::endl;
			L[i] = tl[l++];
		}
		else
		{
//			std::cout << "r < l => V[" << i << "] becomes : "<< tv[r] << std::endl;
			L[i] = tl[r++];
		}
	}
//	std::cout << "vect after merge exit :" << std::endl;
//	quicky_print_vect(V);
*/
}

void
PmergeMe::_sort_list(int start, int end)
{
	int	n = (end - start);
	int	mid = start + (n / 2);

	if (n > k)
	{
//		std::cout << "n > k => n: "<< n << ", k: " << k << ", depth: " << depth << std::endl;
//		std::cout << std::endl << "sort1 => start " << start << ", end "<<  mid << std::endl;
		_sort_list(start, mid);//, depth + 1);
//		std::cout << std::endl << "sort2 => start " << mid << ", end " << end << std::endl;
		_sort_list(mid, end);//, depth + 1);
//		std::cout << std::endl << "merging at depth : " << depth << std::endl;
		merge_list(start, mid, end);
	}
	else
	{
//		std::cout << "n <= k => n: "<< n << ", k: " << k << ", depth: " << depth << std::endl;
		insersion_sort_list(start, end);
	}
}

void
PmergeMe::merge_vect(int start, int mid, int end)
{
	int					i, l, r;
//	std::vector<int>	tv(V.begin() + start, V.begin() + end);
	//std::vector<int>::iterator
//	const int			tmid = mid - start;
//	const int			tend = end - start;

//	std::cout << "V2 before copy ("<<start<<" to "<<end<<")" << std::endl;
//	quicky_print_vect(V2);
	std::copy(V.begin() + start, V.begin() + end, V2.begin() + start);
//	std::cout << "V2 after copy" << std::endl;
//	quicky_print_vect(V2);

//	std::cout << "merge: start, mid, end : " << start << ", " << mid << ", " << end << std::endl;
//	std::cout << "merge: tmid, tend : " << tmid << ", " << tend << std::endl;
	i = start;			// index inside real array V
	l = start;				// index inside segment copy tv.
	r = mid;//tmid;			// index inside segment copy tv.
//	std::cout << "i, l, r: " << i << ", " << l << ", " << r << std::endl;
	for (i = start; i < end; ++i)
	{
//		std::cout << "tv[l="<<l<<"] vs tv[r="<<r<<"] : " << tv[l] << " vs " << tv[r] << std::endl;
		if (r == end)//tend)
		{
//			std::cout << "r == tend => V[" << i << "] becomes : "<< tv[l] << std::endl;
			V[i] = V2[l++];
		}
		else if (l == mid)//tmid)
		{
//			std::cout << "l == tmid => V[" << i << "] becomes : "<< tv[r] << std::endl;
			V[i] = V2[r++];
		}
		else if (V2[l] < V2[r])
		{
//			std::cout << "l < r => V[" << i << "] becomes : "<< tv[l] << std::endl;
			V[i] = V2[l++];
		}
		else
		{
//			std::cout << "r < l => V[" << i << "] becomes : "<< tv[r] << std::endl;
			V[i] = V2[r++];
		}
	}
//	std::cout << "vect after merge exit :" << std::endl;
//	quicky_print_vect(V);
}

void
PmergeMe::_sort_vect(int start, int end)//, int depth)
{
	int	n = (end - start);
	int	mid = start + (n / 2);

	if (n > k)
	{
//		std::cout << "n > k => n: "<< n << ", k: " << k << ", depth: " << depth << std::endl;
//		std::cout << std::endl << "sort1 => start " << start << ", end "<<  mid << std::endl;
		_sort_vect(start, mid);//, depth + 1);
//		std::cout << std::endl << "sort2 => start " << mid << ", end " << end << std::endl;
		_sort_vect(mid, end);//, depth + 1);
//		std::cout << std::endl << "merging at depth : " << depth << std::endl;
		merge_vect(start, mid, end);
	}
	else
	{
//		std::cout << "n <= k => n: "<< n << ", k: " << k << ", depth: " << depth << std::endl;
		insersion_sort_vect(start, end);
	}
}

void
PmergeMe::sort(e_container_type ctype)
{
	if (ctype == LIST_C)
	{
		N = L.size();
//		k = 1;
//		k = N;
		k = static_cast<int>(std::log2(N));
		if (N < 2)
			return ;
		_sort_list(0, N);
	}
	else
	{
		N = V.size();
//		k = 1;
//		k = N;
		k = static_cast<int>(std::log2(N));
		if (N < 2)
			return ;
		_sort_vect(0, N);//, 0);
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
		print_error("clock_gettime failed");
		return ;
	}
	if (!timer_ready)
		timer_ready = true;
	else
	{
//		std::cout << "delta sec : " << curr_time.tv_sec - ori_time.tv_sec << std::endl;
//		std::cout << "delta nsec : " << curr_time.tv_nsec - ori_time.tv_nsec << std::endl;
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
