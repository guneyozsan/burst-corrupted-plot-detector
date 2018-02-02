#pragma once

#include <iostream>
#include <string>

class logger {
	static std::string log_file_name;
public:
	static void set_log_file_name(const std::string &file_name);
	static std::string get_log_file_name();
	static void log(const std::string &content);
	static void print(const std::string &content);
	static void print_and_log(const std::string &content);
	static void print_and_log_title(const std::string &content);
};
