#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <sys/time.h>

class PMM
{
private:
	std::deque<int>					deq;
	std::vector<int>				vec;
	double	deq_time;
	double	vec_time;

	PMM();
	PMM(PMM const &other);
	PMM &operator=(PMM const &other);
public:
	PMM(char **argv, std::string flag);
	~PMM();

	bool	arg_check(char **argv);
	void	deque_sort(void);
	void	vector_sort(void);

};


#endif