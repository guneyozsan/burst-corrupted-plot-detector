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

struct plot_file {
	struct mining_stats {
	private:
		int healthy_count = 0;
		int corrupted_count = 0;
	public:
		void increment_healthy_count();
		void increment_corrupted_count();
		void add_to_corrupted_count(const size_t& corrupted_count);
		int get_healthy_count();
		int get_corrupted_count();
	};
	
	std::string name;
	std::list<std::string> found_deadlines;
	mining_stats mining_stats;

	plot_file();
	plot_file(const std::string &name);
};