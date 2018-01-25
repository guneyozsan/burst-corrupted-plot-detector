#pragma once

#include <string>

struct Plot_file {
	std::string name;
	struct Stats {
		int healthy_count = 0;
		int corrupted_count = 0;
	};
	Stats stats;
	Plot_file() {}
	Plot_file(std::string name) {
		this->name = name;
	}
};