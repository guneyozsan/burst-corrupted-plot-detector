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

#include "mining_log_analyzer.h"

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "console_gui.h"
#include "cursor_animator.h"

/*
* Find Burst plots with deadlines different from server's deadline.
*/
std::vector<plot_file> analyze_plot_files_in_log(const char *file_name) {
	// Plot information
	std::string found_deadline;
	std::string confirmed_deadline;
	std::string plot_file_name;
	std::map<std::string, plot_file> plot_files;

	// Crawling utility
	const std::string found_deadline_keyword = "found deadline=";
	const std::string found_deadline_end_keyword = " nonce";
	const std::string confirmed_deadline_keyword = "confirmed deadline: ";
	const std::string file_keyword = "file: ";
	std::size_t start_position = 0;
	std::size_t end_position = 0;
	std::size_t current_position = 0;
	std::size_t plot_file_position = 0;

	// File utility
	std::ifstream file(file_name);
	std::string line;

	// User feedback
	std::cout << std::endl;
	std::cout << "CHECKING FILE -> " << file_name << std::endl;
	std::cout << "DEADLINES -> ";

	cursor_animator busy_cursor_animator(
		{ "\'", "\'", ":", ".", ":" }, 0.004f);

	// Main loop
	while (std::getline(file, line)) {
		busy_cursor_animator.update_animation();

		// Extract found deadline.
		current_position = line.find(
			found_deadline_keyword, current_position + 1
		);
		if (current_position != std::string::npos) {
			end_position = line.find(
				found_deadline_end_keyword, current_position + 1
			);
			start_position = current_position + found_deadline_keyword.size();
			found_deadline = line.substr(
				start_position, end_position - start_position
			);
			// Extract file name.
			plot_file_position = line.find(
				file_keyword, end_position
				+ found_deadline_end_keyword.size()
			) + file_keyword.size();
			plot_file_name = line.substr(plot_file_position, line.size());
			if (plot_files.count(plot_file_name) == 0) {
				plot_files[plot_file_name] = plot_file(plot_file_name);
			}
		}

		// Extract confirmed deadline.
		current_position = line.find(
			confirmed_deadline_keyword, current_position + 1
		);
		if (current_position != std::string::npos) {
			end_position = line.size();
			start_position = current_position
				+ confirmed_deadline_keyword.size();
			confirmed_deadline = line.substr(
				start_position, end_position - start_position
			);
		}

		// Check if found deadline and confirmed deadline conflict.
		if (found_deadline != "" && confirmed_deadline != "") {
			if (found_deadline == confirmed_deadline) {
				plot_files[plot_file_name].mining_stats.healthy_count++;
				busy_cursor_animator.print(".");
			}
			else {
				plot_files[plot_file_name].mining_stats.corrupted_count++;
				busy_cursor_animator.print("X");
			}
			// Reset.
			found_deadline = "";
			confirmed_deadline = "";
		}
	}
	busy_cursor_animator.finalize();
	std::vector<plot_file> plot_files_array(plot_files.size());
	int i = 0;
	for (auto const &it : plot_files) {
		plot_files_array[i] = it.second;
		i++;
	}
	return plot_files_array;
}

/*
* Display the stats of the given plot file in a nice format.
*/
void print_plot_file_stats(const std::vector<plot_file> &plot_files) {
	const std::string corrupted_title = "CONFLICTING";
	const std::string healthy_title = "HEALTHY";
	const std::string plot_file_title = "PLOT FILE";
	const std::string title_gap = "   ";

	if (plot_files.size() > 0) {
		std::cout << std::endl;
		std::cout << corrupted_title << title_gap
			<< healthy_title << title_gap
			<< plot_file_title << std::endl;
		std::cout << underline(corrupted_title) << title_gap
			<< underline(healthy_title) << title_gap
			<< underline(plot_file_title) << std::endl;
		std::string corrupted_count;
		std::string healthy_count;
		for (size_t i = 0; i < plot_files.size(); i++) {
			if (plot_files[i].mining_stats.corrupted_count == 0) {
				corrupted_count = "-";
			}
			else {
				corrupted_count = std::to_string(
					plot_files[i].mining_stats.corrupted_count);
			}

			print_right_aligned(corrupted_count, corrupted_title.length());
			std::cout << title_gap;

			if (plot_files[i].mining_stats.healthy_count == 0) {
				healthy_count = "-";
			}
			else {
				healthy_count = std::to_string(
					plot_files[i].mining_stats.healthy_count);
			}

			print_right_aligned(healthy_count, healthy_title.length());
			std::cout << title_gap;
			std::cout << plot_files[i].name;
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "No deadlines detected." << std::endl;
	}
}