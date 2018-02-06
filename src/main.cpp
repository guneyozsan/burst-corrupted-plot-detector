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

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "console_gui.h"
#include "file_utility.h"
#include "logger.h"
#include "mining_log_analyzer.h"
#include "plot_files.h"
#include "string_utility.h"
#include "time_utility.h"
#include "titles.h"

int main(int argc, char *argv[]) {
	std::string formatted_time =
		time_utility::format_time(time_utility::now(), "%F-%T");
	// Replace characters not suitable for a file name.
	string_utility::replace_all(':', '_', formatted_time);
	const std::string log_file_prefix = "Burst-mining-log-analysis-";
	logger::set_log_file_name(log_file_prefix + formatted_time + ".log");
	titles::print_opening_titles();

	// Get the list of files in directory or arguments.
	std::map<std::string /* Dir path */,
		std::vector<std::string /* File names */>> files_in_dirs;
	std::string dir_path;

	/* List current working directory if no arguments on command line */
	if (argc == 1) {
		dir_path = ".\\";
		files_in_dirs[dir_path] =
			file_utility::get_file_names_in_directory(".\\");
	}
	else {
		/* For each directory in command line */
		for (int i = 1; i < argc; i++) {
			dir_path = argv[i];
			file_utility::fix_path(dir_path);
			files_in_dirs[dir_path] =
				file_utility::get_file_names_in_directory(argv[i]);
		}
	}

	// Main loop
	class plot_files plot_files;
	class plot_files merged_plot_files;
	// Iterate directories.
	for (auto &it_path : files_in_dirs) {
		logger::print_and_log("\n");
		logger::print_and_log("-> DIRECTORY: " + it_path.first + "\n");
		if (it_path.second.size() == 0) {
			logger::print_and_log("\n");
			logger::print_and_log("No mining logs found at "
				+ it_path.first + "\n");
		}
		// Iterate files in directories.
		for (size_t i = 0; i < it_path.second.size(); i++) {
			// Only consider .log extensions, and exclude own logs.
			if (it_path.second[i].find(".log") != std::string::npos
				&& it_path.second[i].find(log_file_prefix.c_str())
				== std::string::npos)
			{
				plot_files = mining_log_analyzer::analyze_plot_files_in_log(
					it_path.first + it_path.second[i]);
				mining_log_analyzer::print_plot_file_stats(plot_files);
				merged_plot_files = plot_files::merge(
					merged_plot_files, plot_files);
			}
		}
	}

	titles::print_title({"SUMMARY"});
	mining_log_analyzer::print_plot_file_stats(merged_plot_files);
	titles::print_end_titles();
	std::cout << std::endl;
	std::cout << "Press a key to exit...";
	std::cin.get();
	return EXIT_SUCCESS;
}
