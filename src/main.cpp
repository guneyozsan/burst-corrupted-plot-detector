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

#include <map>
#include <string>
#include <vector>

#include "file_utility.h"
#include "logger.h"
#include "mining_log_analyzer.h"
#include "string_utility.h"
#include "time_utility.h"

int main(int argc, char *argv[]) {
	// Initialize logging to file.
	std::string formatted_time =
		time_utility::format_time(time_utility::now(), "%F-%T");
	// Replace characters not suitable for a file name.
	string_utility::replace_all(':', '_', formatted_time);
	std::string log_file_prefix = "Burst-mining-log-analysis-";
	logger::set_log_file_name(log_file_prefix + formatted_time + ".log");

	// Get the list of files in directory or arguments.
	std::map<std::string, std::vector<std::string>> files_in_dirs;
	std::string dir_path;

	/* List current working directory if no arguments on command line */
	if (argc == 1) {
		dir_path = ".\\";
		files_in_dirs[dir_path] = file_utility::get_file_names_in_directory(".\\");
	}
	else {
		/* For each directory in command line */
		for (int i = 1; i < argc; i++) {
			dir_path = argv[i];
			file_utility::fix_path(dir_path);
			files_in_dirs[dir_path] = file_utility::get_file_names_in_directory(argv[i]);
		}
	}

	// Main loop
	std::vector<plot_file> plot_files;
	for (auto &it_path : files_in_dirs) {
		if (it_path.second.size() == 0) {
			logger::print_and_log("\n");
			logger::print_and_log("No mining logs found at " + it_path.first + "\n");
		}
		for (size_t i = 0; i < it_path.second.size(); i++) {
			if (it_path.second[i].find(".log") != std::string::npos
				&& it_path.second[i].find(log_file_prefix.c_str()) == std::string::npos)
			{
				plot_files = analyze_plot_files_in_log(it_path.first + it_path.second[i]);
				print_plot_file_stats(plot_files);
			}
		}
	}

	// Finalize logger
	logger::log("\n");
	logger::log("\n");
	logger::log("-- END OF LOG --");
	logger::log("\n");

	return EXIT_SUCCESS;
}
