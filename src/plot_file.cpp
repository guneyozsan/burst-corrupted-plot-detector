#include "plot_file.h"

plot_file::plot_file() {}

plot_file::plot_file(const std::string &name) {
	this->name = name;
}

void
plot_file::mining_stats::increment_healthy_count() {
	healthy_count++;
}

void
plot_file::mining_stats::increment_corrupted_count() {
	corrupted_count++;
}

void
plot_file::mining_stats::add_to_corrupted_count(
	const size_t& corrupted_count
)
{
	this->corrupted_count += (int)corrupted_count;
}

int
plot_file::mining_stats::get_healthy_count() {
	return healthy_count;
}

int 
plot_file::mining_stats::get_corrupted_count() {
	return corrupted_count;
}