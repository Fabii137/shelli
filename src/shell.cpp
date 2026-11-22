#include "shell.hpp"
#include <print>
#include <iostream>
#include "commands.hpp"

int Shell::run() {
	std::print("$ ");

	while (true) {
		std::string input;
		if (!std::getline(std::cin, input)) {
			std::println();
			break;
		}

		auto result = handle_command(input, last_status_);
		if (result.should_exit) {
			return result.status;
		}

		last_status_ = result.status;

		std::print("$ ");
	}

	return 0;
}