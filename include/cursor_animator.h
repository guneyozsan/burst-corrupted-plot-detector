#pragma once

#include <string>
#include <vector>

struct animating_cursor {
	animating_cursor() {};
	animating_cursor(const std::vector<std::string> &frames) {
		for (size_t i = 0; i < frames.size(); i++) {
			this->frames.push_back(frames[i]);
		}
	}
	std::string current_frame() {
		return frames[currentFrame];
	}
	void progress_to_next_frame() {
		currentFrame = (currentFrame + 1) % frames.size();
	}
private:
	std::vector<std::string> frames;
	int currentFrame = 0;
};

class cursor_animator {
public:
	float anim_speed;
	animating_cursor cursor;

	cursor_animator(const animating_cursor &animating_cursor,
		const float &anim_speed)
	{
		this->cursor = animating_cursor;
		this->anim_speed = anim_speed;
		std::cout << whitespace(cursor.current_frame().length());
	}

	void animate() {
		if (time_for_next_frame()) {
			cursor.progress_to_next_frame();
			std::cout << move_cursor_back(cursor.current_frame().length())
				<< cursor.current_frame();
		}
		update_time();
	}

	void print(std::string content) {
		std::cout << move_cursor_back(cursor.current_frame().length())
			<< content << cursor.current_frame();
	}

	/*
	* Clears last frame. Use this when you are donw with the animation.
	*/
	void finalize() {
		std::cout << move_cursor_back(cursor.current_frame().length())
			<< whitespace(cursor.current_frame().length());
	}

private:
	float anim_time = 0;
	int total_frame_count = 0;

	bool time_for_next_frame() {
		if (anim_time > total_frame_count) {
			total_frame_count++;
			return true;
		}
		else {
			return false;
		}
	}

	void update_time() {
		anim_time += anim_speed;
	}
};