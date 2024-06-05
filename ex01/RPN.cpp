#include "RPN.hpp"

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(RPN const &other)
{
	input = other.input;
}

RPN &RPN::operator=(RPN const &other)
{
	input = other.input;
	return (*this);
}

RPN::RPN(char *str, std::string flag)
{
	(void)flag;
	trim(str);
}

void	RPN::trim(char *str)
{
	std::string s = std::string(str) + " ";
	std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
    	token = s.substr(0, pos);
		if (token.length() > 1)
		{

			std::cout << "Error\n";
			return ;
		}
		if ((token[0] < '0' || token[0] > '9') && token[0] != '-' && token[0] != '+'
			&& token[0] != '/' && token[0] != '*')
		{
			std::cout << "Error\n";
			return ;
		}
		else
		{
			if (token[0] >= '0' && token[0] <= '9')
    			input.push_back(token[0] - '0');
			else if ((token[0] == '-' || token[0] == '+' || token[0] == '/'
				|| token[0] == '*') && input.size() >= 2)
				operations(token[0]);
			else
			{
				std::cout << "Error\n";
				return ;
			}

		}
    	s.erase(0, pos + delimiter.length());
	}
	if (input.size() > 1)
	{
		std::cout << "Error\n";
		return ;
	}
	else
		std::cout << input.front() << std::endl;
}

void	RPN::operations(char op)
{
	int	v2 = input.back();
	input.pop_back();
	int	v1 = input.back();
	input.pop_back();
	switch (op)
	{
		case '*':
			input.push_back(v1 * v2);
			break;
		case '/':
			if (v2 == 0)
			{
				std::cout << "Error\n";
				exit(1);
			}
			else
				input.push_back(v1 / v2);
			break;
		case '+':
			input.push_back(v1 + v2);
			break;
		case '-':
			input.push_back(v1 - v2);
			break;
	}

}