#pragma once

struct mining_stats {
private:
	int healthy_count = 0;
	int corrupted_count = 0;
public:
	void increment_healthy_count();
	void increment_corrupted_count();
	void add_to_corrupted_count(const size_t& corrupted_count);
	int get_healthy_count() const;
	int get_corrupted_count() const;

	static mining_stats merge(
		const mining_stats& lhs_stats, const mining_stats& rhs_stats
	);
};
