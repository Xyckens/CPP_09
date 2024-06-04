#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Nah\n";
		return 1;
	}
	RPN(argv[1], "ola");
	return 0;
	
}