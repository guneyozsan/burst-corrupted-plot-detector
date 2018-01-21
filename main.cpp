#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		std::cout << files_in_dir[i].d_name << std::endl;
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
	std::ifstream file(file_name);

	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line.c_str() << std::endl;
	}
}
