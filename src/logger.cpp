#include "logger.h"

#include <fstream>
#include <iostream>
#include <string>

#include "console_gui.h"

extern std::ofstream log_file;

std::string logger::log_file_name;
std::ofstream log_file;

void
logger::set_log_file_name(const std::string &file_name)
{
	logger::log_file_name = file_name;
}

std::string
logger::get_log_file_name() {
	return log_file_name;
}

void
logger::log(const std::string &content) {
	log_file.open(log_file_name, std::ios::in | std::ios::app);
	log_file << content;
	log_file.close();
}

void
logger::print(const std::string &content) {
	std::cout << content;
}

void
logger::print_and_log(const std::string &content) {
	std::cout << content;
	log(content);
}
