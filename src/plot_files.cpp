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

#include "plot_files.h"

/* Checks if the plot file is already in collection. */
bool
plot_files::contains(const std::string &plot_file_name) {
	if (plot_file_collection.count(plot_file_name) == 0)
		return false;
	else
		return true;
}

/* Adds a plot file to the collection if it is not already added. */
void
plot_files::add(const std::string &plot_file_name) {
	if (!contains(plot_file_name)) {
		plot_file_collection[plot_file_name] = plot_file(plot_file_name);
	}
}

/* Adds a plot file to the collection if it is not already added. */
void
plot_files::add(const plot_file &plot_file) {
	if (!contains(plot_file.name)) {
		plot_file_collection[plot_file.name] = plot_file;
	}
}

/* Returns the plot file object with given file name. */
plot_file
plot_files::get(const std::string &plot_file_name) {
	return plot_file_collection[plot_file_name];
}

/* Returns the complete plot file collection as map. */
std::map<std::string, plot_file>
plot_files::get_collection() const {
	return plot_file_collection;
}

/* Returns the complete plot file collection as vector. */
std::vector<plot_file>
plot_files::get_vector() const {
	std::vector<plot_file> plot_files_vector(plot_file_collection.size());
	int i = 0;
	for (auto &it_pf : plot_file_collection) {
		plot_files_vector[i] = it_pf.second;
		i++;
	}
	return plot_files_vector;
}

/* Adds found deadline to the confirmation queue. */
void
plot_files::add_found_deadline(
	const std::string &plot_file_name, const std::string &found_deadline)
{
	plot_file_collection[plot_file_name]
		.found_deadlines.push_back(found_deadline);
}

/* 
Checks if the confirmed deadline corresponds to a found deadline,
removes the match from confirmation queue, and return the result. 
*/
std::string
plot_files::find_plot_file_with_deadline(
	const std::string &confirmed_deadline)
{
	for (auto &it_pf : plot_file_collection) {
		auto it_fd = it_pf.second.found_deadlines.begin();
		size_t j = 0;
		while (j < it_pf.second.found_deadlines.size()) {
			if (*it_fd == confirmed_deadline) {
				return it_pf.second.name;
			}
			else {
				it_fd++;
				j++;
			}
		}
	}
	return "";
}

/* Removes the deadline from the confirmation queue. */
void
plot_files::remove_deadline(
	const std::string &plot_file_name, const std::string &deadline)
{
	auto it_fd = plot_file_collection[plot_file_name].found_deadlines.begin();
	size_t j = 0;
	while (j < plot_file_collection[plot_file_name].found_deadlines.size()) {
		if (*it_fd == deadline) {
			plot_file_collection[plot_file_name].found_deadlines.erase(it_fd);
			plot_file_collection[plot_file_name].mining_stats
				.increment_healthy_count();
			break;
		}
		else {
			it_fd++;
			j++;
		}
	}
}

/*
Counts the deadlines left in confirmation queue
and add them to corrupted plot count.
*/
void
plot_files::calculate_corrupted_count() {
	for (auto &it_pf : plot_file_collection) {
		it_pf.second.mining_stats.add_to_corrupted_count(
			it_pf.second.found_deadlines.size()
		);
	}
}

/* Merges two plot_file collections and their stats. */
plot_files
plot_files::merge(const plot_files& lhs, const plot_files& rhs) {
	plot_files merged_collection;
	std::vector<bool> has_match_lhs(lhs.get_collection().size(), false);
	std::vector<bool> has_match_rhs(rhs.get_collection().size(), false);
	int i_lhs = 0;
	for (auto &it_lhs : lhs.get_collection()) {
		int i_rhs = 0;
		for (auto &it_rhs : rhs.get_collection()) {
			if (it_lhs.first == it_rhs.first) {
				plot_file merged_plot_file;
				merged_plot_file = 
					plot_file::merge(it_lhs.second, it_rhs.second);
				merged_plot_file.name;
				merged_collection.add(merged_plot_file);
				has_match_lhs[i_lhs] = true;
				has_match_rhs[i_rhs] = true;
			}
			i_rhs++;
		}

		if (!has_match_lhs[i_lhs]) {
			merged_collection.add(it_lhs.second);
		}

		i_lhs++;
	}

	int i_rhs = 0;
	for (auto &it_rhs : rhs.get_collection()) {
		if (!has_match_rhs[i_rhs]) {
			merged_collection.add(it_rhs.second);
		}
		i_rhs++;
	}
	return merged_collection;
}
