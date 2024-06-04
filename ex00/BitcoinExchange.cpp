#include "BitcoinExchange.hpp"

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

BitcoinExchange::BitcoinExchange(std::string data, std::string input)
{
	this->data = 0;
	std::ifstream file1(data.c_str());
	if (!file1.is_open())
	{
		std::cerr << NoFileException() << std::endl;
		return ;
	}
	std::string line;
	std::getline(file1, line);
	while (std::getline(file1, line))
		validate_entry_csv(line);
	file1.close();
	std::ifstream file2(input.c_str());
	if (!file2.is_open())
	{
		std::cerr << NoFileException() << std::endl;
		return ;
	}
	std::getline(file2, line);
	if (line != "date | value")
	{
		std::cerr << InvalidFormatException() << " => " << line << std::endl;
		return ;
	}
	while (std::getline(file2, line))
		validate_entry_txt(line);
	file2.close();
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
	std::string year2 = date.substr(0, 4);
    std::string month2 = date.substr(5, 2);
    std::string day2 = date.substr(8, 2);
	std::string yyyymmdd = year2 + month2 + day2;
	this->data = atof(yyyymmdd.c_str());
	return true;
}

bool	BitcoinExchange::validate_value(float value)
{
	if (value >= 0 && value <= 1000)
		return true;
	return false;
}

void	BitcoinExchange::validate_entry_csv(std::string line)
{
	unsigned long	pos = line.find(",");
	if (pos != 10 || pos + 1 >= line.length())
	{
		std::cout << InvalidFormatException() << " => " << line << std::endl;
		return ;
	}

	std::string	date = line.substr(0, pos);
	if (!validate_date(date))
	{
		std::cout << InvalidDateException() << " => " << date << std::endl;
		return ;
	}

	std::string v = line.substr(pos + 1);
	int			p = 0; //ponto
	unsigned long i = 0;
	for (; i < v.length(); i++)
	{
		if (v[i] == '.')
			p++;
		else if ((v[i] == '+' || v[i] == '-') && i > 0)
			break ;
		else if ((v[i] < '0' || v[i] > '9') && v[i] != '-' && v[i] != '+')
			break ;
	}
	if (i < v.length() || p > 1)
	{
		std::cout << InvalidValueException() << " => " << v << std::endl;
		return ;
	}
	float	value = static_cast<float>(atof(v.c_str()));
	data_csv.insert(std::pair<float, float>(this->data, value));
}

void	BitcoinExchange::validate_entry_txt(std::string line)
{
	unsigned long	pos = line.find(" | ");
	if (pos != 10 || pos + 3 >= line.length())
	{
		std::cout << InvalidFormatException() << " => " << line << std::endl;
		return ;
	}
	std::string	date = line.substr(0, pos);
	if (!validate_date(date))
	{
		std::cout << InvalidDateException() << " => " << date << std::endl;
		return ;
	}
	float	value = static_cast<float>(atof(line.substr(pos + 3).c_str()));

	if (!validate_value(value))
	{
		std::cout << InvalidValueException() <<  " => " << value << std::endl;
		return ;
	}
	find_nearest_date(date, value);
}

void	BitcoinExchange::find_nearest_date(std::string date, float value)
{
	if (data_csv.find(data) != data_csv.end())
		std::cout << date  << " => " << value << " = " << value * data_csv.find(data)->second << std::endl;
	else
	{
		std::multimap<float, float>::iterator it2 = data_csv.end();
		for(std::multimap<float, float>::iterator it = data_csv.begin(); it != data_csv.end(); it++)
		{
			if (std::abs(it->first - data) < std::abs(it2->first - data))
				it2 = it;
		}
		std::cout << date  << " => " << value << " = " << value * it2->second << std::endl;
	}
}

const char *BitcoinExchange::NoFileException()
{
	return "Error: Couldn't open the file.";
}

const char *BitcoinExchange::EmptyFileException()
{
	return "Error: The file was empty.";
}

const char *BitcoinExchange::InvalidDateException()
{
	return "Error: Invalid date.";
}

const char *BitcoinExchange::InvalidFormatException()
{
	return "Error: Invalid Format.";
}

const char *BitcoinExchange::InvalidValueException()
{
	return "Error: Value not between 0 and 1000.";
}
