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
#include <iostream>
#include <string>
#include <vector>

cursor_animator::animating_cursor::animating_cursor() {}

cursor_animator::animating_cursor::animating_cursor(
	const std::vector<std::string> &cursor_frames)
{
	for (size_t i = 0; i < cursor_frames.size(); i++) {
		this->frames.push_back(cursor_frames[i]);
	}
}

std::string 
cursor_animator::animating_cursor::current_frame() {
	return frames[currentFrame];
}

void 
cursor_animator::animating_cursor::progress_to_next_frame() {
	currentFrame = (currentFrame + 1) % frames.size();
}

cursor_animator::cursor_animator(
	const std::vector<std::string> &cursor_frames, const float &anim_speed)
{
	this->cursor = animating_cursor(cursor_frames);
	this->anim_speed = anim_speed;
	std::cout << whitespace(cursor.current_frame().length());
}

void
cursor_animator::update_animation() {
	if (is_time_for_next_frame()) {
		cursor.progress_to_next_frame();
		std::cout << move_cursor_back(cursor.current_frame().length())
			<< cursor.current_frame();
	}
	update_time();
}

void
cursor_animator::finalize() {
	std::cout << move_cursor_back(cursor.current_frame().length())
		<< whitespace(cursor.current_frame().length());
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
