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

#include "mining_log_analyzer.h"

#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

#include "console_gui.h"
#include "cursor_animator.h"
#include "logger.h"
#include "string_utility.h"

/*
Analyzes the Burst log file and returns a plot_file object with analysis results.
Looks for deadlines conflicting with server.
*/
plot_files
mining_log_analyzer::analyze_plot_files_in_log(const std::string &file_name)
{
	// User feedback
	logger::log("\n");
	logger::log("MINING LOG: " + file_name + "\n");
	logger::print("\n");
	logger::print("SCANNING LOG -> " + file_name + "\n");

	const unsigned char confirmed_deadline_cursor = 219;
	const unsigned char corrupted_deadline_cursor = 177;
	std::string healthy_cursor;
	healthy_cursor = confirmed_deadline_cursor;
	std::string corrupted_cursor;
	corrupted_cursor = corrupted_deadline_cursor;
	logger::print(healthy_cursor + " = healthy, " + corrupted_cursor
		+ " = conflicting\n");
	logger::print("DEADLINES ->  ");
	cursor_animator::set_animation({ "-", "\\", "|", "/" }, 15.0f);

	// Plot information
	std::string found_deadline;
	std::string confirmed_deadline;
	std::string plot_file_name;
	plot_files plot_files;

	// Crawling utility
	const std::string found_deadline_keyword = "found deadline=";
	const std::string found_deadline_end_keyword = " nonce";
	const std::string confirmed_deadline_keyword = "confirmed deadline: ";
	const std::string file_name_keyword = "file: ";
	std::size_t start_position = 0;
	std::size_t end_position = 0;
	std::size_t current_position = 0;
	std::size_t plot_file_position = 0;

	// File utility
	std::ifstream file(file_name);
	std::string line;

	// Main loop
	while (std::getline(file, line)) {
		cursor_animator::update_animation();

		// Extract found deadline.
		current_position = line.find(
			found_deadline_keyword, current_position + 1);
		if (current_position != std::string::npos) {
			end_position = line.find(
				found_deadline_end_keyword, current_position + 1);
			start_position = current_position + found_deadline_keyword.size();
			found_deadline = line.substr(
				start_position, end_position - start_position);

			// Extract file name.
			plot_file_position = line.find(
				file_name_keyword, end_position
				+ found_deadline_end_keyword.size())
				+ file_name_keyword.size();
			plot_file_name = line.substr(plot_file_position, line.size());
			if (!plot_file::suits_file_name_format(plot_file_name))
				plot_file_name = "Error in mining log";
			plot_files.add(plot_file_name);
			plot_files.add_found_deadline(plot_file_name, found_deadline);
		}

		// Extract confirmed deadline.
		current_position = line.find(
			confirmed_deadline_keyword, current_position + 1);
		if (current_position != std::string::npos) {
			end_position = line.size();
			start_position = current_position
				+ confirmed_deadline_keyword.size();
			confirmed_deadline = line.substr(
				start_position, end_position - start_position);
		}

		// Check if found deadline and confirmed deadline conflict.
		if (confirmed_deadline != "") {
			std::string confirmed_plot_file_name =
				plot_files.find_plot_file_with_deadline(confirmed_deadline);
			if (confirmed_plot_file_name == "") {
				cursor_animator::print(corrupted_deadline_cursor);
			}
			else {
				plot_files.remove_deadline(
					confirmed_plot_file_name, confirmed_deadline);
				cursor_animator::print(confirmed_deadline_cursor);
			}
			confirmed_deadline = "";
		}
	}
	cursor_animator::finalize();
	plot_files.calculate_corrupted_count();
	return plot_files;
}

/*
Displays the stats available in a plot_file object in a nicely formatted way.
*/
void
mining_log_analyzer::print_plot_file_stats(const plot_files &plot_files)
{
	std::vector<plot_file> plot_files_list = plot_files.get_vector();

	const std::string total_title = "OVERALL";
	const std::string corrupted_title = "CONFLICTING";
	const std::string healthy_title = "HEALTHY    ";
	const std::string percentage_title = "    %";
	const std::string plot_file_title = "PLOT FILE";
	const std::string title_gap = "   ";
	const std::string conflict_marker = "  X ->";
	const std::string no_conflict_marker = "      ";
	
	if (plot_files_list.size() > 0) {
		// Print titles for stats table
		logger::print_and_log("\n");
		logger::print_and_log(
			title_gap + corrupted_title
			+ title_gap + percentage_title + " "
			+ title_gap + healthy_title
			+ title_gap+ percentage_title + " "
			+ no_conflict_marker + plot_file_title
			+ "\n");
		logger::print_and_log(
			title_gap + console_gui::underline(corrupted_title)
			+ console_gui::underline(title_gap) + console_gui::underline(percentage_title) + " "
			+ title_gap + console_gui::underline(healthy_title)
			+ console_gui::underline(title_gap) + console_gui::underline(percentage_title) + " "
			+ no_conflict_marker + console_gui::underline(plot_file_title)
			+ "\n");

		// Print stats for each plot file.
		int corrupted_count;
		int healthy_count;
		int deadline_count;
		std::string corrupted_count_string;
		std::string healthy_count_string;
		std::string corrupted_percentage_of_plot;
		std::string healthy_percentage_of_plot;
		std::string marker;
		int total_corrupted = 0;
		int total_healthy = 0;

		for (size_t i = 0; i < plot_files_list.size(); i++) {
			marker = no_conflict_marker;

			corrupted_count =
				plot_files_list[i].mining_stats.get_corrupted_count();
			healthy_count =
				plot_files_list[i].mining_stats.get_healthy_count();

			if (plot_files_list[i].mining_stats.get_corrupted_count() == 0) {
				corrupted_count_string = "-";
			}
			else {
				corrupted_count_string = std::to_string(corrupted_count);
				marker = conflict_marker;
			}

			if (plot_files_list[i].mining_stats.get_healthy_count() == 0)
				healthy_count_string = "-";
			else
				healthy_count_string = std::to_string(healthy_count);

			if (string_utility::is_numbers_only(corrupted_count_string))
				total_corrupted += std::stoi(corrupted_count_string);

			if (string_utility::is_numbers_only(healthy_count_string))
				total_healthy += std::stoi(healthy_count_string);
			
			deadline_count = corrupted_count + healthy_count;
			corrupted_percentage_of_plot
				= std::to_string(
					100.0f * (float)corrupted_count / (float)deadline_count);
			healthy_percentage_of_plot
				= std::to_string(
					100.0f * (float)healthy_count / (float)deadline_count);
			const int precision = 1;
			string_utility::round_with_precision(
				corrupted_percentage_of_plot, precision);
			string_utility::round_with_precision(
				healthy_percentage_of_plot, precision);

			logger::print_and_log(
				title_gap
				+ console_gui::align_right(
					corrupted_count_string, corrupted_title.length())
				+ title_gap 
				+ console_gui::align_right(
					corrupted_percentage_of_plot, percentage_title.length()) + " "
				+ title_gap
				+ console_gui::align_right(
					healthy_count_string, healthy_title.length())
				+ title_gap
				+ console_gui::align_right(
					healthy_percentage_of_plot, percentage_title.length()) + " "
				+ marker + plot_files_list[i].name + "\n");
		}

		// Calculate percentages of total corrupted and healthy deadlines
		// in a log file.
		std::string total_corrupted_percentage;
		std::string total_healthy_percentage;

		if (total_corrupted + total_healthy == 0) {
			total_corrupted_percentage = "0";
			total_healthy_percentage = "0";
		}
		else {
			int total_deadlines = total_corrupted + total_healthy;
			total_corrupted_percentage
				= std::to_string(
					100.0f * (float)total_corrupted / (float)total_deadlines);
			total_healthy_percentage
				= std::to_string(
					100.0f * (float)total_healthy / (float)total_deadlines);
			const int precision = 1;
			string_utility::round_with_precision(
				total_corrupted_percentage, precision);
			string_utility::round_with_precision(
				total_healthy_percentage, precision);
		}

		// Print total stats.
		logger::print_and_log(
			title_gap
			+ console_gui::underline(corrupted_title + title_gap + percentage_title) + " "
			+ title_gap + console_gui::underline(healthy_title + title_gap + percentage_title) + " "
			+ no_conflict_marker + console_gui::underline(plot_file_title)
			+ "\n");
		logger::print_and_log(
			title_gap
			+ console_gui::align_right(
				std::to_string(total_corrupted), corrupted_title.length())
			+ title_gap
			+ console_gui::align_right(
				total_corrupted_percentage, percentage_title.length()) + "%"
			+ title_gap
			+ console_gui::align_right(
				std::to_string(total_healthy), healthy_title.length())
			+ title_gap
			+ console_gui::align_right(
				total_healthy_percentage, percentage_title.length()) + "%"
			+ no_conflict_marker
			+ total_title
			+ "\n");
	}
	else {
		logger::print_and_log("No deadlines detected.\n");
	}
}
