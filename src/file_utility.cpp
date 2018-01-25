#include "file_utility.h"

/*
* List files within a directory.
*/
std::vector<dirent> get_files_in_directory(const char *dir_name) {
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
