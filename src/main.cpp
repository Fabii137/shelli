#include <cstring>
#include <iostream>
#include <print>
#include "commands.hpp"

int main() {
	int last_status = 0;

	std::print("$ ");

	while (true) {
		std::string input;
		if (!std::getline(std::cin, input)) {
			std::println();
			break;
		}

		auto result = handle_command(input, last_status);
		if (result.should_exit) {
			return result.status;
		}

		last_status = result.status;

		std::print("$ ");
	}
}