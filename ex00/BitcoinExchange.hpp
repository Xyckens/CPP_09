#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <algorithm>
#include <algorithm>
#include <set>
#include <sstream>

class BitcoinExchange
{
private:
	std::multiset<std::string, float> data_csv;
	std::multiset<std::string, float> input_txt;
	BitcoinExchange();
	BitcoinExchange(BitcoinExchange const &other);
	BitcoinExchange &operator=(BitcoinExchange const &other);
public:
	BitcoinExchange(std::string data, std::string input);
	~BitcoinExchange();
	bool	validate_date(std::string &date);
	bool	validate_values(float value);


	class NoFileException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class EmptyFileException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class InvalidDateException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class InvalidFormatException : public std::exception
	{
	public:
		const char* what() const throw();
	};

	class InvalidValueException : public std::exception
	{
	public:
		const char* what() const throw();
	};
};


#endif