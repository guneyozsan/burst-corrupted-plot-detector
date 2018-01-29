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

#include "file_utility.h"
#include "logger.h"
#include "mining_log_analyzer.h"
#include "string_utility.h"
#include "time_utility.h"

int main(int argc, char *argv[]) {
	// Initialize logging to file.
	std::string formatted_time = time_utility::format_time(time_utility::now(), "%F-%T");
	// Replace characters not suitable for a file name.
	string_utility::replace_all(':', '_', formatted_time);
	std::string log_file_prefix = "Burst-mining-log-analysis-";
	logger::set_log_file_name(log_file_prefix + formatted_time + ".log");

	std::vector<dirent> files_in_dir;

	/* List current working directory if no arguments on command line */
	if (argc == 1) {
		files_in_dir = get_files_in_directory(".");
	}
	else {
		/* For each directory in command line */
		int i = 1;
		while (i < argc) {
			files_in_dir = get_files_in_directory(argv[i]);
			i++;
		}
	}

	for (int i = 0; i < files_in_dir.size(); i++) {
		std::vector<plot_file> plot_files;
		if (strstr(files_in_dir[i].d_name, ".log") 
			&& !strstr(files_in_dir[i].d_name, log_file_prefix.c_str()))
		{
			plot_files = analyze_plot_files_in_log(files_in_dir[i].d_name);
			print_plot_file_stats(plot_files);
		}
	}

	logger::log("\n");
	logger::log("\n");
	logger::log("-- END OF LOG --");
	logger::log("\n");
	return EXIT_SUCCESS;
}
