#include "shell.hpp"
#include <cstdlib>
#include <print>
#include <iostream>
#include "commands.hpp"
#include <filesystem>
#include <unistd.h>
#include <pwd.h>

static std::string get_username() {
	uid_t uid = getuid();
	passwd* pw = getpwuid(uid);
	if (pw) {
		return std::string(pw->pw_name);
	}

	return "";
}

static void print_prompt() {
	std::string username = get_username();
	if (!username.empty()) {
		std::print("{}:", username);
	}

	std::string path = std::filesystem::current_path();
	std::string home = getenv("HOME");

	if (path.starts_with(home)) {
		path.erase(0, home.size());
		path.insert(0, 1, '~');
	}

	std::print("{}$ ", path);
}

int Shell::run() {
	print_prompt();

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

		print_prompt();
	}

	return 0;
}
