#pragma once
#include <string>
#include <vector>

class titles {
	static std::string separator;
public:
	static void print_title(std::vector<std::string> titles);
	static void print_opening_titles();
	static void print_end_titles();
};
