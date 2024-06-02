#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Error: Could not open file.\n";
		return (1);
	}
	else if (argc > 2)
	{
		std::cout << "Error: Too many arguments.\n";
		return (1);
	}
	BitcoinExchange("data.csv", argv[1]);
	return (0);
}