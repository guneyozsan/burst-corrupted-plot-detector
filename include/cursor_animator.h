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

#include <string>
#include <vector>

class cursor_animator {
private:
	struct animating_cursor {
	private:
		std::vector<std::string> frames;
		int currentFrame = 0;
	public:
		animating_cursor();
		animating_cursor(const std::vector<std::string> &cursor_frames);
		
		/* Returns the current frame. */
		std::string current_frame();
		
		/* Advances the cursor animation to the next frame. */
		void progress_to_next_frame();
	};

	float anim_time = 0;
	float anim_speed;
	int total_frame_count = 0;
	animating_cursor cursor;

	bool is_time_for_next_frame();
	void update_time();
public:
	cursor_animator(
		const std::vector<std::string> &cursor_frames,
		const float &anim_speed);
	
	/* Animates cursor. */
	void update_animation();

	/* Prints content moves animating cursor to the end. */
	void print(std::string content);

	/* Clears last frame. Use this when you are done with the animation. */
	void finalize();
};
