#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <list>
#include <algorithm>
#include <string>

class RPN
{
private:
	std::list<int> input;
	
	RPN();
	RPN(RPN const &other);
	RPN &operator=(RPN const &other);
public:
	RPN(char *str, std::string flag);
	~RPN();
	void	trim(char *str);
	void	operations(char op);
};

#endif