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

#include "titles.h"

#include "console_gui.h"
#include "logger.h"
#include "version.h"

std::string
titles::separator = "------------------------------------------------------------";

/*
Prints a pre-formatted section title.
Prints each string in vector to a new line. */
void
titles::print_title(std::vector<std::string> titles) {
	logger::print_and_log("\n");
	logger::print_and_log(separator + "\n");
	logger::print_and_log("\n");

	for (size_t i = 0; i < titles.size(); i++) {
		logger::print_and_log(
			console_gui::center(titles[i], separator.size()) + "\n");
	}

	logger::print_and_log("\n");
	logger::print_and_log(separator + "\n");
}

/* Prints opening titles. */
void
titles::print_opening_titles() {
	logger::print_and_log("\n");
	logger::print_and_log("    _ ) |  |_ \\  __|__ __|   \\  |_ _|  \\ |_ _|  \\ |  __|\n");
	logger::print_and_log("    _ \\ |  |  /\\__ \\   |    |\\/ |  |  .  |  |  .  | (_ |\n");
	logger::print_and_log("   ___/\\__/_|_\\____/  _|   _|  _|___|_|\\_|___|_|\\_|\\___|\n");
	logger::print_and_log("\n");
	logger::print_and_log("  __|  _ \\ _ \\ _ \\ |  |_ \\__ __|__| _ \\   _ \\|     _ \\__ __|\n");
	logger::print_and_log(" (    (   |  /   / |  |__/   |  _|  |  |  __/|    (   |  |  \n");
	logger::print_and_log("\\___|\\___/_|_\\_|_\\\\__/_|    _| ___|___/  _| ____|\\___/  _|  \n");
	logger::print_and_log("\n");
	logger::print_and_log("             _ \\ __|__ __|__|  __|__ __|_ \\ _ \\\n");
	logger::print_and_log("             |  |_|    |  _|  (      | (   |  /\n");
	logger::print_and_log("            ___/___|  _| ___|\\___|  _|\\___/_|_\\\n");
	logger::print_and_log("\n");
	logger::print_and_log(
		console_gui::center(version, separator.size()) + "\n");
	logger::print_and_log(
		console_gui::center("by Guney Ozsan", separator.size()) + "\n");
	print_title({
			"ANALYSIS", 
			"** Summary stats are at the end of the log file. **"});
}

/* Prints end titles. */
void
titles::print_end_titles() {
	logger::print_and_log("\n");
	std::cout << "This log is also saved near the executable." << std::endl;
	logger::print_and_log(separator + "\n");
	std::cout << "Burst Corrupted Plot Detector " << version
		<< " by Guney Ozsan" << std::endl;
	std::cout
		<< "Latest version: "
		<< "https://github.com/guneyozsan/burst-corrupted-plot-detector/releases"
		<< std::endl;
	logger::log("\n");
	logger::log(
		console_gui::center("-- END OF LOG --\n", separator.size()) + "\n");
}
