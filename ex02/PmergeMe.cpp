#include "PmergeMe.hpp"


PMM::PMM()
{
}

PMM::~PMM()
{
}

PMM::PMM(PMM const &other)
{
	deq = other.deq;
	vec = other.vec;
	odd = other.odd;
}

PMM &PMM::operator=(PMM const &other)
{
	deq = other.deq;
	vec = other.vec;
	odd = other.odd;
	return (*this);
}

void	PMM::is_deq_sorted(void)
{
	int stored = 0;
	for(std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
	{
		if (*it < stored)
		{
			std::cout << "NOT SORTED => " << *it << " and " << stored << "!!!\n";
			return ;
		}
		stored = *it;
	}
	std::cout << "SORTED!!!\n";
}

void	PMM::is_vec_sorted(void)
{
	int stored = 0;
	for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		if (*it < stored)
		{
			std::cout << "NOT SORTED => " << *it << " and " << stored << "!!!\n";
			return ;
		}
		stored = *it;
	}
	std::cout << "SORTED!!!\n";
}

PMM::PMM(char **argv, std::string flag)
{
	(void)flag;
	if (!arg_check(argv))
		return ;
	std::cout << "\t\t\t\tBefore: \n\nDeque:\n\t";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
		std::cout << *it << " ";
	std::cout << "\nVector:\n\t";
	for (std::vector<int>::iterator it2 = vec.begin(); it2 != vec.end(); it2++)
		std::cout << *it2 << " ";
	deque_sort();
	vector_sort();
	std::cout << "\n\n\t\t\t\tAfter: \n\nDeque:\n\t";
	for (std::deque<int>::iterator it3 = deq.begin(); it3 != deq.end(); it3++)
		std::cout << *it3 << " ";
	std::cout << "\nVector:\n\t";
	for (std::vector<int>::iterator it4 = vec.begin(); it4 != vec.end(); it4++)
		std::cout << *it4 << " ";
	std::cout << "\n\n\tTime to process a range of " << deq.size() << " elements with std::deque  : " << deq_time << " ms.";
	std::cout << "\n\tTime to process a range of " << vec.size() << " elements with std::vector : " << vec_time << " ms.\n";
	is_deq_sorted();	
	is_vec_sorted();	
}

bool	PMM::arg_check(char **argv)
{
	int	conv;
	long long temp;
	for (int i = 1; argv[i]; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				std::cerr << "Invalid Input.\n";
				return false;
			}
		}
		temp = atoll(argv[i]);
		if (temp < 2147483647)
			conv = temp;
		else
		{
			std::cerr << "Number " << temp << " is too big.\n";
			return false;
		}
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
		{
			if (*it == conv)
			{
				std::cerr << "Duplicated Number: " << conv << "!\n";
				return false;
			}
		}
		deq.push_back(conv);
		vec.push_back(conv);
	}
	odd = 0;
	return true;
}

// https://www.geeksforgeeks.org/jacobsthal-and-jacobsthal-lucas-numbers/

int jacobsthal(size_t n)
{
    if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

void	PMM::deque_sort(void)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	std::deque<std::pair<int, int> > pair = deque_pair();

	pair = deque_pair_sort(pair, pair.size());
	pair_to_deq(pair);

	gettimeofday(&end, NULL);
	deq_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}

std::deque<std::pair<int, int> >	PMM::deque_pair(void)
{
	std::deque<std::pair<int, int> > dequePair;
	size_t size = deq.size();
	if (size % 2 != 0)
	{
		odd = deq.back();
		deq.pop_back();
		size--;
	}
	for (size_t i = 0; i < size; i += 2)
	{
		if (deq[i] > deq[i + 1])
			dequePair.push_back(std::make_pair(deq[i], deq[i + 1]));
		else
			dequePair.push_back(std::make_pair(deq[i + 1], deq[i]));

	}
	return dequePair;
}

std::deque<std::pair<int, int> > PMM::deque_pair_sort(std::deque<std::pair<int, int> > deq_pair, int pair_size)
{
	if (pair_size == 1)
		return deq_pair;
	deq_pair = deque_pair_sort(deq_pair, pair_size - 1);
	std::pair<int, int> back = deq_pair[pair_size - 1];
	int i = pair_size - 2;
	for (; i >= 0 && deq_pair[i].first > back.first; i--)
	{
		deq_pair[i + 1].first = deq_pair[i].first;
		deq_pair[i + 1].second = deq_pair[i].second;

	}
	deq_pair[i + 1] = back;
	return deq_pair;
}

void PMM::pair_to_deq(std::deque<std::pair<int, int> > deq_pair)
{
	std::deque<std::pair<int, int> >::iterator it = deq_pair.begin();

	deq.clear();
    deq.push_back(it->second);
    deq.push_back(it->first);
	it++;
    for (; it != deq_pair.end(); it++)
	{
        deq.push_back(it->first);
	}

	size_t	last_index = 0;
    size_t	old_dist = 0;
    size_t 	dist = 0;
	int 	value = 0;
	
    for (size_t i = 2; last_index < deq_pair.size() - 1; i++)
	{
        dist = std::abs(jacobsthal(i) - jacobsthal(i + 1));
        // Iteration from the distance with the jacobsthal
        for (size_t j = dist; j > 0; j--)
		{
            if (j + old_dist < deq_pair.size())
			{
                value = deq_pair[j + old_dist].second;
                deq.insert(std::lower_bound(deq.begin(), deq.end(), value), value);
            }
        }
        last_index = dist + old_dist;
        old_dist += dist;
    }
	if (odd != 0)
        deq.insert(std::lower_bound(deq.begin(), deq.end(), odd), odd);
}

std::vector<std::pair<int, int> >	PMM::vector_pair(void)
{
	std::vector<std::pair<int, int> > vectorPair;
	size_t size = vec.size();
	if (size % 2 != 0)
	{
		odd = vec.back();
		vec.pop_back();
		size--;
	}
	for (size_t i = 0; i < size; i += 2)
	{
		if (vec[i] > vec[i + 1])
			vectorPair.push_back(std::make_pair(vec[i], vec[i + 1]));
		else
			vectorPair.push_back(std::make_pair(vec[i + 1], vec[i]));

	}
	return vectorPair;
}

std::vector<std::pair<int, int> > PMM::vector_pair_sort(std::vector<std::pair<int, int> > vec_pair, int pair_size)
{
	if (pair_size == 1)
		return vec_pair;
	vec_pair = vector_pair_sort(vec_pair, pair_size - 1);
	std::pair<int, int> back = vec_pair[pair_size - 1];
	int i = pair_size - 2;
	for (; i >= 0 && vec_pair[i].first > back.first; i--)
	{
		vec_pair[i + 1].first = vec_pair[i].first;
		vec_pair[i + 1].second = vec_pair[i].second;
	}
	vec_pair[i + 1] = back;
	return vec_pair;
}

void PMM::pair_to_vec(std::vector<std::pair<int, int> > vec_pair)
{
	std::vector<std::pair<int, int> >::iterator it = vec_pair.begin();

	vec.clear();
    vec.push_back(it->second);
    vec.push_back(it->first);
	it++;
    for (; it != vec_pair.end(); it++)
	{
        vec.push_back(it->first);
	}

	size_t	last_index = 0;
    size_t	old_dist = 0;
    size_t 	dist = 0;
	int 	value = 0;
	
    for (size_t i = 2; last_index < vec_pair.size() - 1; i++)
	{
        dist = std::abs(jacobsthal(i) - jacobsthal(i + 1));
        // Iteration from the distance with the jacobsthal
        for (size_t j = dist; j > 0; j--)
		{
            if (j + old_dist < vec_pair.size())
			{
                value = vec_pair[j + old_dist].second;
                vec.insert(std::lower_bound(vec.begin(), vec.end(), value), value);
            }
        }
        last_index = dist + old_dist;
        old_dist += dist;
    }
	if (odd != 0)
        vec.insert(std::lower_bound(vec.begin(), vec.end(), odd), odd);
}

void	PMM::vector_sort(void)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	std::vector<std::pair<int, int> > pair = vector_pair();

	pair = vector_pair_sort(pair, pair.size());
	pair_to_vec(pair);

	gettimeofday(&end, NULL);
	vec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}
