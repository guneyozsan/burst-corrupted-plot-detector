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

#include "console_gui.h"

#include <iostream>

 /*
 * Prints the content right aligned in a horizontal slot of given size.
 */
void print_right_aligned(const std::string& content, const size_t& slot_size) {
	size_t whitespace_count = slot_size - content.length();
	for (size_t i = 0; i < whitespace_count; i++) {
		std::cout << " ";
	}
	std::cout << content;
}

/*
* Prints "-" the same size with given content to serve as underliner.
*/
std::string underline(const std::string& content) {
	std::string underliner;
	for (size_t i = 0; i < content.length(); i++) {
		underliner.append("-");
	}
	return underliner;
}

/*
* Moves cursor back.
*/
std::string backspace(const size_t size) {
	std::string backspace;
	for (size_t i = 0; i < size; i++) {
		backspace.append("\b");
	}
	return backspace;
}

/*
* Prints whitespace of given size.
*/
std::string whitespace(const size_t size) {
	std::string backspace;
	for (size_t i = 0; i < size; i++) {
		backspace.append(" ");
	}
	return backspace;
}
