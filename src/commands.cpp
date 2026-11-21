#include "commands.hpp"

#include <cstring>
#include <format>
#include <iostream>
#include <ostream>
#include <unistd.h>
#include <vector>
#include <string>
#include "commands/alias.hpp"
#include "commands/expansions.hpp"
#include "commands/builtins.hpp"
#include <sys/wait.h>

static std::vector<std::string> split_command(std::string input) {
	static constexpr const char delimiter[] = " \t\n";

	char* token = std::strtok(input.data(), delimiter);
	std::vector<std::string> result;
	while (token) {
		result.push_back(token);
		token = std::strtok(nullptr, delimiter);
	}

	return result;
}

static int run_command(const std::vector<std::string>& args) {
	pid_t pid = fork();
	if (pid == -1) {
		std::cerr << "Failed to fork: " << std::strerror(errno) << "\n";
		return 1;
	}

	if (pid > 0) {
		// parent process
		int status;
		int ret;
		while ((ret = waitpid(pid, &status, 0)) == -1 && errno == EINTR) {
			// retry on interrupt
		}
		if (ret == -1) {
			std::cerr << "waitpid failed: " << std::strerror(errno) << "\n";
			return 1;
		}

		if (WIFEXITED(status)) {
			return WEXITSTATUS(status);
		}

		if (WIFSIGNALED(status)) {
			return 128 + WTERMSIG(status);
		}

		return 1;
	} else {
		// child process
		std::vector<char*> c_args;
		for (auto& arg : args) {
			// TODO: avoid const_cast
			c_args.push_back(const_cast<char*>(arg.data()));
		}
		c_args.push_back(nullptr);

		execvp(c_args[0], c_args.data());
		std::cerr << std::format("Failed to execute command '{}': {}\n", c_args[0],
		    std::strerror(errno));

		_exit(127);
	}

	return 0;
}

CommandResult handle_command(const std::string& input, int last_status) {
	std::vector<std::string> args = split_command(input);
	if (args.empty()) {
		return { .status = last_status };
	}

	expand_args(args, last_status);

	if (auto alias = get_alias(args[0])) {
		auto alias_args = split_command(*alias);
		// copy args from original command after alias
		alias_args.insert(alias_args.end(), args.begin() + 1, args.end());
		args = std::move(alias_args);
	}

	if (args[0] == "exit") {
		return { .should_exit = true };
	}

	if (is_builtin(args[0])) {
		return { .status = run_builtin(args) };
	}

	return { .status = run_command(args) };
}