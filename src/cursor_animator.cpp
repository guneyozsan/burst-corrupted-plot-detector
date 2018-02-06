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

float cursor_animator::animation_period;
clock_t cursor_animator::last_update_time;

/* Updates cursor frame according to the frames per second set. */
void
cursor_animator::update_animation()
{
	if ((clock() - last_update_time) > animation_period) {
		animating_cursor::progress_to_next_frame();
		std::cout 
			<< console_gui::move_cursor_back(
				animating_cursor::get_current_frame().length()
			)
			<< animating_cursor::get_current_frame();
		last_update_time = clock();
	}
}

/* Clears last frame. Use this when you are done with the animation. */
void
cursor_animator::finalize()
{
	std::cout 
		<< console_gui::move_cursor_back(
			animating_cursor::get_current_frame().length()
		)
		<< console_gui::whitespace(
			animating_cursor::get_current_frame().length()
		);
}

/* Sets cursor animation and speed. */
void
cursor_animator::set_animation(
	const std::vector<std::string> &frame_sequence,
	const float &anim_speed)
{
	set_animation_sequence(frame_sequence);
	set_speed(anim_speed);
	last_update_time = clock();
}

/* Sets cursor animation to given frame sequence. */
void
cursor_animator::set_animation_sequence(
	const std::vector<std::string> &frame_sequence)
{
	animating_cursor::set_animation(frame_sequence);
}

/* Sets animation speed. */
void
cursor_animator::set_speed(
	const float &frames_per_second)
{
	cursor_animator::animation_period = 1000 / frames_per_second;
}
