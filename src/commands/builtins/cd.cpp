#include "cd.hpp"
#include <unistd.h>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <iostream>
#include <filesystem>

int cd(const std::vector<std::string>& args) {
	if (args.size() > 2) {
		std::cerr << "cd: too many arguments\n";
		return 1;
	}

	std::filesystem::path path = args.size() > 1 ? args[1] : std::getenv("HOME");

	if (chdir(path.c_str()) != 0) {
		std::cerr << "cd: " << strerror(errno) << '\n';
		return 1;
	}

	return 0;
}