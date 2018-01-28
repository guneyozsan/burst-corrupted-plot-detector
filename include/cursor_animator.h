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

#pragma once

#include "animating_cursor.h"
#include <ctime>
#include <string>
#include <vector>

class cursor_animator {
private:
	static float animation_period;
	static clock_t last_update_time;
public:
	static void set_animation(
		const std::vector<std::string> &frame_sequence,
		const float &anim_speed
	);
	static void set_animation_sequence(
		const std::vector<std::string> &frame_sequence
	);
	static void set_speed(const float &anim_speed);
	static void update_animation();
	template<typename T> static void print(T const &content);
	static void finalize();
};

/* Prints content moves animating cursor to the end. */
template<typename T> static void
cursor_animator::print(T const &content) {
	std::cout 
		<< move_cursor_back(animating_cursor::current_frame().length())
		<< content 
		<< animating_cursor::current_frame();
}
