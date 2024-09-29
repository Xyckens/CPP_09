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
	std::deque<int>		deq;
	std::vector<int>	vec;

	int					odd;

	double				deq_time;
	double				vec_time;

	PMM();
	PMM(PMM const &other);
	PMM &operator=(PMM const &other);
public:
	PMM(char **argv, std::string flag);
	~PMM();

	std::vector<std::pair<int, int> >	vector_pair(void);
	std::deque<std::pair<int, int> >	deque_pair(void);

	std::vector<std::pair<int, int> >	vector_pair_sort(std::vector<std::pair<int, int> > vec_pair, int pair_size);
	std::deque<std::pair<int, int> >	deque_pair_sort(std::deque<std::pair<int, int> > deq_pair, int pair_size);

	void								pair_to_vec(std::vector<std::pair<int, int> > vec_pair);
	void								pair_to_deq(std::deque<std::pair<int, int> > vec_pair);

	bool								arg_check(char **argv);
	void								deque_sort(void);
	void								vector_sort(void);

	void								is_vec_sorted(void);
	void								is_deq_sorted(void);

};


#endif