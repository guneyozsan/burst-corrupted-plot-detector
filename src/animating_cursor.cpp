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

#include "animating_cursor.h"

#include "console_gui.h"
#include <iostream>

std::vector<std::string> animating_cursor::frames;
int animating_cursor::currentFrame;

std::string
animating_cursor::current_frame() {
	return frames[currentFrame];
}

void
animating_cursor::progress_to_next_frame() {
	currentFrame = (currentFrame + 1) % frames.size();
}

void
animating_cursor::set_animation(
	const std::vector<std::string> &frame_sequence
)
{
	frames.clear();
	for (size_t i = 0; i < frame_sequence.size(); i++) {
		frames.push_back(frame_sequence[i]);
	}
}
