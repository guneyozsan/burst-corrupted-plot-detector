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

#include "plot_file.h"

#include <cctype>

plot_file::plot_file() {}

plot_file::plot_file(const std::string &name)
{
	this->name = name;
}

bool
plot_file::suits_file_name_format(const std::string plot_file_name)
{
	if (plot_file_name.size() == 0)
		return false;

	const char separator = '_';
	const int number_of_separators = 3;
	int separator_count = 0;
	int previous_separator_index = 0;

	for (size_t i = 0; i < plot_file_name.size(); i++) {
		if (plot_file_name[i] == separator) {
			if (i == 0 || i == plot_file_name.size() - 1)
				return false;

			if (i == previous_separator_index + 1)
				return false;
			else
				previous_separator_index = i;
			
			separator_count++;
			
			if (separator_count > number_of_separators)
				return false;
		}
		else if (!std::isdigit(plot_file_name[i])) {
			return false;
		}
	}

	if (separator_count != number_of_separators)
		return false;

	return true;
}

/*
Merges stats of two plot_file's with the same name
and returns a new plot_file.
If names don't match, returns an empty plot_file.
*/
plot_file
plot_file::merge(const plot_file &lhs, const plot_file &rhs)
{
	if (lhs.name == rhs.name) {
		plot_file merged(lhs.name);
		lhs.found_deadlines;
		rhs.found_deadlines;
		merged.mining_stats = mining_stats::merge(
			lhs.mining_stats, rhs.mining_stats
		);
		return merged;
	}
	else {
		return plot_file();
	}
}
