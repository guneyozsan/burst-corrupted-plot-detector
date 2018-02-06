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

#include <list>
#include <string>

#include "mining_stats.h"

struct plot_file {
	std::string name;
	std::list<std::string> found_deadlines;
	mining_stats mining_stats;

	plot_file();
	plot_file(const std::string &name);
	static plot_file merge(
		const plot_file &lhs, const plot_file &rhs);
};
