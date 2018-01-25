#pragma once
#include <vector>

#ifdef _MSC_VER
#include "dirent.h"
#else
#include <dirent.h>
#endif // _MSC_VER

std::vector<dirent> get_files_in_directory(const char *dirname);
