#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#ifdef _MSC_VER
#include "include/dirent.h"
#else
#include <dirent.h>
#endif // _MSC_VER

static std::vector<dirent> get_files_in_directory(const char *dirname);
static void find_corrupted_plots(const char *file_name);

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
		find_corrupted_plots(files_in_dir[i].d_name);
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
static void find_corrupted_plots(const char *file_name) {
	std::string found_deadline;
	std::string confirmed_deadline;
	std::string plot_file;
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
	while (std::getline(file, line))
	{
		// Extract found deadlines.
		position = line.find(found_deadline_keyword, position + 1);
		if (position != std::string::npos) {
			end_position = line.find(found_deadline_end_keyword, position + 1);
			start_position = position + found_deadline_keyword.size();
			found_deadline = line.substr(start_position, end_position - start_position);
			// Extract file name.
			plot_file_position = line.find(file_keyword, end_position + found_deadline_end_keyword.size()) + file_keyword.size();
			plot_file = line.substr(plot_file_position, line.size());
		}

		// Extract confirmed deadlines.
		position = line.find(confirmed_deadline_keyword, position + 1);
		if (position != std::string::npos) {
			end_position = line.size();
			start_position = position + confirmed_deadline_keyword.size();
			confirmed_deadline = line.substr(start_position, end_position - start_position);
		}

		if (found_deadline != "" && confirmed_deadline != "") {
			if (found_deadline != confirmed_deadline) {
				std::cout << "Found deadline     : ";
				std::cout << found_deadline << std::endl;
				std::cout << "Confirmed deadline : ";
				std::cout << confirmed_deadline << std::endl;
				std::cout << "FILE               : ";
				std::cout << plot_file << std::endl;
			}
			found_deadline = "";
			confirmed_deadline = "";
		}
	}
}
