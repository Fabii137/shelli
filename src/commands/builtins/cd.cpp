#include "cd.hpp"
#include "commands/result.hpp"
#include <unistd.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <filesystem>

CommandResult cd(const std::vector<std::string>& args) {
	if (args.size() > 2) {
		std::cerr << "cd: too many arguments\n";
		return { .status = E2BIG };
	}

	std::filesystem::path path = args.size() > 1 ? args[1] : std::getenv("HOME");

	if (chdir(path.c_str()) != 0) {
		std::cerr << "cd: " << strerror(errno) << '\n';
		return { .status = EINVAL };
	}

	return { .status = 0 };
}