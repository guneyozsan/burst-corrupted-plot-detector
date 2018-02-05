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

 /* Right aligns the text in a given horizontal slot. */
std::string
console_gui::align_right(
	const std::string &content, const size_t &slot_size)
{
	std::string slot = "";
	if (slot_size >= content.length()) {
		size_t whitespace_count = slot_size - content.length();
		for (size_t i = 0; i < whitespace_count; i++) {
			slot += " ";
		}
		slot += content;
	}
	else {
		slot = content.substr(content.length() - slot_size);
	}
	return slot;
}

/* Prints "-" the same size with given content to serve as underliner. */
std::string
console_gui::underline(const std::string &content) {
	std::string underliner;
	for (size_t i = 0; i < content.length(); i++) {
		underliner.append("-");
	}
	return underliner;
}

/* Moves cursor back given size. Doesn't delete printed output. */
std::string
console_gui::move_cursor_back(const size_t &size) {
	std::string backspace;
	for (size_t i = 0; i < size; i++) {
		backspace.append("\b");
	}
	return backspace;
}

/* Prints whitespace of given size. */
std::string
console_gui::whitespace(const size_t &size) {
	std::string backspace;
	for (size_t i = 0; i < size; i++) {
		backspace.append(" ");
	}
	return backspace;
}

/* Centers the text in a given horizontal slot. */
std::string
console_gui::center(const std::string text, size_t width)
{
	if (text.size() > INT_MAX) {
		throw std::overflow_error("text size cannot be greater than INT_MAX.");
	}

	if (width > INT_MAX) {
		throw std::overflow_error("with cannot be greater than INT_MAX.");
	}

	int text_position = (int)(width - text.size()) / 2;
	std::string whitespace = console_gui::whitespace(text_position);
	std::string centered_text = whitespace + text + whitespace;
	if (centered_text.size() < width) {
		centered_text += " ";
	}
	return centered_text;
}
