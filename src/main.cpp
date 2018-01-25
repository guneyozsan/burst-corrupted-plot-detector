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

#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#ifdef _MSC_VER
#include "dirent.h"
#else
#include <dirent.h>
#endif // _MSC_VER

#include "console_gui.h"

struct Plot_file_result {
	int healthy_count;
	int corrupted_count;
};

static std::vector<dirent> get_files_in_directory(const char *dirname);
static std::map<std::string, Plot_file_result> find_corrupted_plots(const char *file_name);
static void print_results(std::map<std::string, Plot_file_result> plot_file_result);

int main(int argc, char *argv[]) {
	int i;
	std::vector<dirent> files_in_dir;

	/* For each directory in command line */
	i = 1;
	while (i < argc) {
		files_in_dir = get_files_in_directory(argv[i]);
		i++;
	}

	/* List current working directory if no arguments on command line */
	if (argc == 1) {
		files_in_dir = get_files_in_directory(".");
	}

	for (int i = 0; i < files_in_dir.size(); i++) {
		std::cout << std::endl;
		std::cout << "CHECKING FILE -> " << files_in_dir[i].d_name << std::endl;

		std::map<std::string, Plot_file_result> plot_file_result;
		plot_file_result = find_corrupted_plots(files_in_dir[i].d_name);
		print_results(plot_file_result);
	}

	return EXIT_SUCCESS;
}

/*
* List files within a directory.
*/
static std::vector<dirent> get_files_in_directory(const char *dir_name) {
	DIR *dir;
	struct dirent *dir_entry;
	std::vector<struct dirent> file_entries;

	/* Open directory stream */
	dir = opendir(dir_name);
	if (dir != NULL) {
		/* Print all files within the directory */
		while ((dir_entry = readdir(dir)) != NULL) {
			if (dir_entry->d_type == DT_REG) {
				file_entries.push_back(*dir_entry);
			}
		}

		closedir(dir);
		return file_entries;
	}
	else {
		/* Could not open directory */
		printf("Cannot open directory %s\n", dir_name);
		exit(EXIT_FAILURE);
	}
}

/*
* Find Burst plots with deadlines different from server's deadline.
*/
static std::map<std::string, Plot_file_result> find_corrupted_plots(const char *file_name) {
	std::string found_deadline;
	std::string confirmed_deadline;
	std::string plot_file;
	std::map<std::string, Plot_file_result> plot_file_result;
	const std::string found_deadline_keyword = "found deadline=";
	const std::string found_deadline_end_keyword = " nonce";
	const std::string confirmed_deadline_keyword = "confirmed deadline: ";
	const std::string file_keyword = "file: ";
	std::size_t position = 0;
	std::size_t end_position = 0;
	std::size_t start_position = 0;
	std::size_t plot_file_position = 0;

	std::ifstream file(file_name);
	std::string line;

	std::cout << "DEADLINES -> ";

	std::string busy_icon[] = { "\'", "\'", ":", ".", ":" };

	size_t busy_icon_animation_length = sizeof(busy_icon) / sizeof(busy_icon[0]);
	float i = 0;
	float update_speed = 0.002f;
	int last_update = 0;
	std::string current_frame = busy_icon[0];
	std::cout << whitespace(current_frame.length());
	while (std::getline(file, line))
	{
		// Print busy icon
		if (i > last_update) {
			current_frame = busy_icon[(int)i % busy_icon_animation_length];
			std::cout << backspace(current_frame.length()) << current_frame;
			last_update++;
		}
		i += update_speed;

		// Extract found deadlines.
		position = line.find(found_deadline_keyword, position + 1);
		if (position != std::string::npos) {
			end_position = line.find(found_deadline_end_keyword, position + 1);
			start_position = position + found_deadline_keyword.size();
			found_deadline = line.substr(start_position, end_position - start_position);
			// Extract file name.
			plot_file_position = line.find(file_keyword, end_position + found_deadline_end_keyword.size()) + file_keyword.size();
			plot_file = line.substr(plot_file_position, line.size());
			if (plot_file_result.count(plot_file) == 0) {
				plot_file_result[plot_file] = Plot_file_result{ 0, 0 };
			}
		}

		// Extract confirmed deadlines.
		position = line.find(confirmed_deadline_keyword, position + 1);
		if (position != std::string::npos) {
			end_position = line.size();
			start_position = position + confirmed_deadline_keyword.size();
			confirmed_deadline = line.substr(start_position, end_position - start_position);
		}

		// Corrupted plot condition:
		if (found_deadline != "" && confirmed_deadline != "") {
			if (found_deadline == confirmed_deadline) {
				plot_file_result[plot_file].healthy_count++;
				std::cout << backspace(current_frame.length()) << "." << busy_icon[(int)i % busy_icon_animation_length];
			}
			else {
				plot_file_result[plot_file].corrupted_count++;
				std::cout << backspace(current_frame.length()) << "X" << busy_icon[(int)i % busy_icon_animation_length];
			}
			found_deadline = "";
			confirmed_deadline = "";
		}
	}
	std::cout << backspace(current_frame.length()) << whitespace(current_frame.length());
	return plot_file_result;
}

static void print_results(std::map<std::string, Plot_file_result> plot_file_result) {
	const std::string corrupted_title = "CONFLICTING";
	const std::string healthy_title = "HEALTHY";
	const std::string plot_file_title = "PLOT FILE";
	const std::string title_gap = "   ";

	if (plot_file_result.size() > 0) {
		std::cout << std::endl;
		std::cout << corrupted_title << title_gap << healthy_title << title_gap << plot_file_title << std::endl;
		std::cout << underline(corrupted_title) << title_gap << underline(healthy_title) << title_gap << underline(plot_file_title) << std::endl;
		std::string corrupted_count;
		std::string healthy_count;
		for (auto const& it : plot_file_result) {
			if (it.second.corrupted_count == 0) {
				corrupted_count = "-";
			}
			else {
				corrupted_count = std::to_string(it.second.corrupted_count);
			}

			print_right_aligned(corrupted_count, corrupted_title.length());
			std::cout << title_gap;

			if (it.second.healthy_count == 0) {
				healthy_count = "-";
			}
			else {
				healthy_count = std::to_string(it.second.healthy_count);
			}

			print_right_aligned(healthy_count, healthy_title.length());
			std::cout << title_gap;
			std::cout << it.first;
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "No deadlines detected." << std::endl;
	}
}
