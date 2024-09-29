#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "No arguments provided.\n";
	}
	else if (argc == 2)
	{
		std::cerr << "Bruh...\n";
	}
	else
	{
		PMM(argv, "ola");		
	}
	return (0);
}