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

#include "cursor_animator.h"

#include "console_gui.h"
#include "console_gui.h"
#include <iostream>
#include <string>
#include <vector>

float cursor_animator::anim_time;
float cursor_animator::anim_speed;
int cursor_animator::total_frame_count;

void
cursor_animator::update_animation() {
	if (is_time_for_next_frame()) {
		animating_cursor::progress_to_next_frame();
		std::cout << move_cursor_back(animating_cursor::current_frame().length())
			<< animating_cursor::current_frame();
	}
	update_time();
}

void
cursor_animator::finalize() {
	std::cout << move_cursor_back(animating_cursor::current_frame().length())
		<< whitespace(animating_cursor::current_frame().length());
}

bool
cursor_animator::is_time_for_next_frame() {
	if (anim_time > total_frame_count) {
		total_frame_count++;
		return true;
	}
	else {
		return false;
	}
}

void
cursor_animator::update_time() {
	anim_time += anim_speed;
}

void
cursor_animator::set_animation(
	const std::vector<std::string> &frame_sequence,
	const float &anim_speed)
{
	set_animation_sequence(frame_sequence);
	set_speed(anim_speed);
}

void
cursor_animator::set_animation_sequence(
	const std::vector<std::string> &frame_sequence)
{
	animating_cursor::set_animation(frame_sequence);
}

void
cursor_animator::set_speed(
	const float &anim_speed)
{
	cursor_animator::anim_speed = anim_speed;
}
