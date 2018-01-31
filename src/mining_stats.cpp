#include "mining_stats.h"

void
mining_stats::increment_healthy_count() {
	healthy_count++;
}

void
mining_stats::increment_corrupted_count() {
	corrupted_count++;
}

void
mining_stats::add_to_corrupted_count(
	const size_t& corrupted_count
)
{
	this->corrupted_count += (int)corrupted_count;
}

int
mining_stats::get_healthy_count() const {
	return healthy_count;
}

int
mining_stats::get_corrupted_count() const {
	return corrupted_count;
}

/* Merges two stats objects by calculating total counts. */
mining_stats
mining_stats::merge(
	const mining_stats& lhs, const mining_stats& rhs)
{
	mining_stats merged_stats;
	merged_stats.healthy_count =
		lhs.get_healthy_count() + rhs.get_healthy_count();
	merged_stats.corrupted_count =
		lhs.get_corrupted_count() + rhs.get_corrupted_count();
	return merged_stats;
}
