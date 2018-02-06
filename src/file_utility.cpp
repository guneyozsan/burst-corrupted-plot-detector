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

#ifdef _MSC_VER
#include "dirent.h"
#else
#include <dirent.h>
#endif // _MSC_VER

#include "logger.h"
#include "string_utility.h"

/* Returns the list of files in a directory. */
std::vector<std::string>
file_utility::get_file_names_in_directory(const char *dir_name)
{
	DIR *dir;
	struct dirent *dir_entry;
	std::vector<std::string> file_entries;

	/* Open directory stream */
	dir = opendir(dir_name);
	if (dir != NULL) {
		/* Add all files within the directory */
		while ((dir_entry = readdir(dir)) != NULL) {
			if (dir_entry->d_type == DT_REG) {
				file_entries.push_back(dir_entry->d_name);
			}
		}

		closedir(dir);
	}
	else {
		std::string dir_path;
		dir_path = dir_name;
		logger::print_and_log("Cannot open directory " + dir_path + "\n");
	}
	return file_entries;
}

/*
Fixes paths for directly concatenating with file names.
Replaces forward slashes with backslashes and if missing 
adds a backslash to the end.
*/
void
file_utility::fix_path(std::string &path)
{
	string_utility::replace_all('/', '\\', path);
	if (path[path.size() - 1] != '\\') {
		path += "\\";
	}
}
