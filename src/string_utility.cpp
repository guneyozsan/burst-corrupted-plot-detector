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

#include "string_utility.h"

#include <string>

// Replaces all occurences of a character with the given character.
void
string_utility::replace_all(const char &original_char, const char &replacement, std::string &string_body) {
	std::string replacement_str;
	replacement_str = replacement;
	for (size_t i = 0; i < string_body.size(); ++i) {
		if (string_body[i] == original_char) {
			string_body.replace(i, 1, replacement_str);
		}
	}
}
