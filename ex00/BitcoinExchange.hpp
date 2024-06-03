#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <sstream>
#include <fstream>

class BitcoinExchange
{
private:
	std::multimap<float, float> data_csv;
	std::multimap<float, float> input_txt;
	float						data;

	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &other);
	BitcoinExchange &operator=(BitcoinExchange const &other);
public:
	BitcoinExchange(std::string data, std::string input);
	~BitcoinExchange();
	bool	validate_date(std::string &date);
	bool	validate_value(float value);
	void	validate_entry_csv(std::string line);
	void	validate_entry_txt(std::string line);
	void	find_nearest_date(std::string date, float value);


	const char * NoFileException();
	const char * EmptyFileException();
	const char * InvalidDateException();
	const char * InvalidFormatException();
	const char * InvalidValueException();
};


#endif