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

#include "logger.h"

#include <fstream>
#include <iostream>
#include <string>

#include "console_gui.h"

extern std::ofstream log_file;

std::string logger::log_file_name;
std::ofstream log_file;

void
logger::set_log_file_name(const std::string &file_name)
{
	logger::log_file_name = file_name;
}

std::string
logger::get_log_file_name()
{
	return log_file_name;
}

void
logger::log(const std::string &content)
{
	log_file.open(log_file_name, std::ios::in | std::ios::app);
	log_file << content;
	log_file.close();
}

void
logger::print(const std::string &content)
{
	std::cout << content;
}

void
logger::print_and_log(const std::string &content)
{
	std::cout << content;
	log(content);
}
