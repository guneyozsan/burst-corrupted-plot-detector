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
			console_gui::center(titles[i], separator.size()) + "\n"
		);
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
	logger::print_and_log(console_gui::center(VERSION, separator.size()) + "\n");
	logger::print_and_log(console_gui::center("by Guney Ozsan", separator.size()) + "\n");
	print_title({
			"ANALYSIS", 
			"** Summary stats are at the end of the log file. **"
		});
}

/* Prints end titles. */
void
titles::print_end_titles() {
	std::string version;
	version = VERSION;
	logger::print_and_log("\n");
	logger::print_and_log(separator + "\n");
	logger::print_and_log("\n");
	logger::print_and_log("Burst Corrupted Plot Detector " + version + " by Guney Ozsan\n");
	logger::print_and_log("Latest version: https://github.com/guneyozsan/burst-corrupted-plot-detector/releases\n");
	logger::print_and_log("\n");
	logger::print(
		console_gui::center(
			"** This log is also saved to a file near the executable. **",
			separator.size()
		)
		+ "\n"
	);
	logger::print("\n");
	logger::print_and_log(
		console_gui::center("-- END OF LOG --\n", separator.size()) + "\n"
	);
}
