#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#include "include/dirent.h"
#else
#include <dirent.h>
#endif // _MSC_VER

static void list_directory(const char *dirname);

int main(int argc, char *argv[]) {
	int i;

	/* For each directory in command line */
	i = 1;
	while (i < argc) {
		list_directory(argv[i]);
		i++;
	}

	/* List current working directory if no arguments on command line */
	if (argc == 1) {
		list_directory(".");
	}
	return EXIT_SUCCESS;
}

/*
* List files and directories within a directory.
*/
static void
list_directory(
	const char *dirname)
{
	DIR *dir;
	struct dirent *ent;

	/* Open directory stream */
	dir = opendir(dirname);
	if (dir != NULL) {

		/* Print all files and directories within the directory */
		while ((ent = readdir(dir)) != NULL) {
			if (ent->d_type == DT_REG)
			{
				printf("%s\n", ent->d_name);
			}
		}

		closedir(dir);

	}
	else {
		/* Could not open directory */
		printf("Cannot open directory %s\n", dirname);
		exit(EXIT_FAILURE);
	}
}
