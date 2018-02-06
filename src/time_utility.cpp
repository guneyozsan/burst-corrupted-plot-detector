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

#include "time_utility.h"

/* Returns cross platform type safe localtime. */
std::tm
time_utility::localtime_cross_platform(const std::time_t &calendar_time) {
	std::tm date_time{};
#if defined(__unix__)
	localtime_r(&calendar_time, &date_time);
#elif defined(_MSC_VER)
	localtime_s(&date_time, &calendar_time);
#else
	static std::mutex mtx;
	std::lock_guard<std::mutex> lock(mtx);
	date_time = *std::localtime(&calendar_time);
#endif
	return date_time;
}

/*
Returns formatted version of the given calendar time.
default = "YYYY-MM-DD HH:MM:SS"
*/
std::string
time_utility::format_time(const std::tm &time, const std::string &format) {
	struct tm date_time = time;
	char buffer[64];
	return { buffer,
		std::strftime(buffer, sizeof(buffer), format.c_str(), &date_time)};
}

/* Returns current time in tm. */
std::tm
time_utility::now() {
	return localtime_cross_platform(std::time(nullptr));
}
