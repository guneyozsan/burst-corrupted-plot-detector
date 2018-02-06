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

plot_file::plot_file() {}

plot_file::plot_file(const std::string &name)
{
	this->name = name;
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
