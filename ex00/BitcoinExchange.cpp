#include "BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange(std::string data, std::string input)
{
	(void)data;
	(void)input;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &other)
{
	data_csv = other.data_csv;
	input_txt = other.input_txt;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &other)
{
	data_csv = other.data_csv;
	input_txt = other.input_txt;
	return (*this);
}

bool	BitcoinExchange::validate_date(std::string &date)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	int year, month, day;
	char dash1, dash2;

	std::istringstream iss(date);
	// Extract year, month, and day
	if (!(iss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (dash1 != '-' || dash2 != '-' || year < 1 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;

    // Check the number of days in the month
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	int daysInMonth[] = { 31, (isLeapYear ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (day > daysInMonth[month - 1])
		return false;
	return true;
}

bool	BitcoinExchange::validate_values(float value)
{
	if (value >= 0 && value <= 1000)
		return true;
	return false;
}

const char *BitcoinExchange::NoFileException::what() const throw()
{
	return "Error: Couldn't open the file.\n";
}

const char *BitcoinExchange::EmptyFileException::what() const throw()
{
	return "Error: The file was empty.\n";
}

const char *BitcoinExchange::InvalidDateException::what() const throw()
{
	return "Error: Invalid date.\n";
}

const char *BitcoinExchange::InvalidFormatException::what() const throw()
{
	return "Error: Invalid Format.\n";
}

const char *BitcoinExchange::InvalidValueException::what() const throw()
{
	return "Error: Value not between 0 and 1000\n";
}
