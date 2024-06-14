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
}

PMM &PMM::operator=(PMM const &other)
{
	deq = other.deq;
	vec = other.vec;
	return (*this);
}

PMM::PMM(char **argv, std::string flag)
{
	(void)flag;
	if (!arg_check(argv))
		return ;
	std::cout << "Before: ";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
		std::cout << *it << " ";
	deque_sort();
	vector_sort();
	std::cout << "\nAfter: ";
	for (std::vector<int>::iterator it2 = vec.begin(); it2 != vec.end(); it2++)
		std::cout << *it2 << " ";
	std::cout << "\nTime to process a range of " << deq.size() << " elements with std::deque  : " << deq_time << " ms.";
	std::cout << "\nTime to process a range of " << vec.size() << " elements with std::vector : " << vec_time << " ms.\n";
			
}

bool	PMM::arg_check(char **argv)
{
	int	conv;
	for (int i = 1; argv[i]; i++)
	{
		for (int j = 0; argv[i][j]; j++)
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				std::cout << "Invalid Input.\n";
				return false;
			}
		}
		conv = atoi(argv[i]);
		for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
		{
			if (*it == conv)
			{
				std::cout << "Duplicated Number: " << conv << "!\n";
				return false;
			}
		}
		deq.push_back(conv);
		vec.push_back(conv);
	}
	return true;
}

void	PMM::deque_sort(void)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	gettimeofday(&end, NULL);
	deq_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}

void	PMM::vector_sort(void)
{
	struct timeval start, end;
	gettimeofday(&start, NULL);

	gettimeofday(&end, NULL);
	vec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;
}
