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
string_utility::replace_all(
	const char &original_char, const char &replacement,
	std::string &string_body)
{
	std::string replacement_str;
	replacement_str = replacement;
	for (size_t i = 0; i < string_body.size(); ++i) {
		if (string_body[i] == original_char) {
			string_body.replace(i, 1, replacement_str);
		}
	}
}

// Checks if the string contains only numeric characters.
bool
string_utility::is_numbers_only(const std::string &s)
{
	if (s.size() == 0) {
		return false;
	}

	for (size_t i = 0; i < s.size(); i++) {
		if (!std::isdigit(s[i])) {
			return false;
		}
	}

	return true;
}

// Truncates a string representation of a number to the given precision.
// Does not extend numbers with less precision.
void
string_utility::round_with_precision(
	std::string &str_number, const int &precision)
{
	if (precision < 0) {
		throw std::invalid_argument("precision cannot be negative");
	}

	// Check if number has decimals.
	size_t dot_index = str_number.find(".");
	if (dot_index == std::string::npos) {
		if (!string_utility::is_numbers_only(str_number)) {
			throw std::invalid_argument("string is not a valid number.");
		}

		// Add decimal separator and zeros if number precision is less than
		// given precision.
		if (precision > 0) {
			str_number += ".";
			for (int i = 0; i < precision; i++) {
				str_number += "0";
			}
		}
		return;
	}
	else {
		if (!string_utility::is_numbers_only(str_number.substr(0, dot_index))
			|| !string_utility::is_numbers_only(
				str_number.substr(dot_index + 1)))
		{
			throw std::invalid_argument("string is not a valid number.");
		}

		if (str_number.size() > INT_MAX) {
			throw std::overflow_error(
				"string size should be less than INT_MAX.");
		}

		int deficit_digit_count =
			(int)dot_index + precision - ((int)str_number.size() - 1);
		
		// Add zeros if number precision is less than given precision.
		if (deficit_digit_count > 0) {
			for (int i = 0; i < deficit_digit_count; i++) {
				str_number += "0";
			}
		}
		else {
			// Start rounding from smallest digit, right to left until
			// precision point.
			for (size_t i = str_number.size() - 1;
				i > dot_index + precision; i--)
			{
				if (str_number[i] - '0' >= 5) {
					if (i == dot_index + 1) {
						str_number[i - 2] += 1;
					}
					else {
						str_number[i - 1] += 1;
					}
				}
				str_number[i] = '0';
			}

			str_number = str_number.substr(0, dot_index + precision + 1);
				
			// Truncate dot if precision is 0.
			if (precision == 0) {
				str_number = str_number.substr(0, str_number.size() - 1);
			}
		}
	}
}
