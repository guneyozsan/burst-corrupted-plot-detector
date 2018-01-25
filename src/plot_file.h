#pragma once

#include <string>

struct plot_file {
	std::string name;

	struct mining_stats {
		int healthy_count = 0;
		int corrupted_count = 0;
	};

	mining_stats mining_stats;

	plot_file(const std::string &name) {
		this->name = name;
	}
};