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

#pragma once

#include <map>
#include <string>
#include <vector>

#include "plot_file.h"

struct plot_files {
private:
	std::map<std::string, plot_file> plot_file_collection;
public:
	/* Checks if the plot file is already in collection. */
	bool contains(const std::string &plot_file_name);

	/* Adds a plot file to collection. Allows duplicates. */
	void add(const std::string &plot_file_name);

	/* Returns the plot file object with given file name. */
	plot_file get(const std::string &plot_file_name);

	/* Returns the complete plot file collection as map. */
	std::map<std::string, plot_file> get_collection();

	/* Returns the complete plot file collection as vector. */
	std::vector<plot_file> get_vector();

	/* Adds found deadline to the confirmation queue. */
	void add_found_deadline(const std::string &plot_file_name, const std::string &found_deadline);
	
	/* Checks if the confirmed deadline corresponds to a found deadline, removes the match from confirmation queue, and return the result. */
	std::string find_plot_file_with_deadline(const std::string &confirmed_deadline);

	void remove_deadline(const std::string &plot_file_name, const std::string &deadline);

	void calculate_corrupted_count();
};