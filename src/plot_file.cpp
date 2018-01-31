#include "plot_file.h"

plot_file::plot_file() {}

plot_file::plot_file(const std::string &name) {
	this->name = name;
}

/* Merges two plot_files and their stats. */
plot_file
plot_file::merge(const plot_file& lhs, const plot_file& rhs) {
	if (lhs.name == rhs.name) {
		plot_file merged(lhs.name);
		lhs.found_deadlines;
		rhs.found_deadlines;
		merged.mining_stats = mining_stats::merge(
			lhs.mining_stats, rhs.mining_stats
		);
		return merged;
	}
}
