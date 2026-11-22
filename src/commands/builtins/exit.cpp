#include "exit.hpp"
#include "commands/result.hpp"
#include <cerrno>
#include <iostream>
#include <stdexcept>

CommandResult builtin_exit(const std::vector<std::string>& args) {
	if (args.size() > 2) {
		std::cerr << "exit: too many arguments\n";
		return { .status = E2BIG };
	}

	int code;
	if (args.size() == 2) {
		try {
			size_t pos;
			code = std::stoi(args[1], &pos);
			if (pos != args[1].size()) {
				throw std::runtime_error("");
			}

			if (code < 0 || code > 255) {
				std::cerr << "exit: '" << code << "' is not a valid exit code\n";
				return { .status = EINVAL };
			}
		} catch (...) {
			std::cerr << "exit: '" << args[1] << "' is not a valid integer\n";
			return { .status = EINVAL };
		}
	}

	return { .status = code, .should_exit = true };
}