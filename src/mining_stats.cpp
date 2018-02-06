/* Burst Corrupted Plot Detector - Scans Burst mining logs and reports
* possible corrupt plot files.
* Copyright(C) 2018 Guney Ozsan
*
* This program is free software : you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.If not, see <https://www.gnu.org/licenses/>.
*/

#include "mining_stats.h"

#include <climits>
#include <stdexcept>

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
	const size_t &corrupted_count)
{
	if (corrupted_count > INT_MAX) {
		throw std::overflow_error(
			"corrupted_count cannot be greater than INT_MAX.");
	}
	
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
	const mining_stats &lhs, const mining_stats &rhs)
{
	mining_stats merged_stats;
	merged_stats.healthy_count =
		lhs.get_healthy_count() + rhs.get_healthy_count();
	merged_stats.corrupted_count =
		lhs.get_corrupted_count() + rhs.get_corrupted_count();
	return merged_stats;
}
