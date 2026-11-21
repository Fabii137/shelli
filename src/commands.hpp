#pragma once

#include <string>

struct CommandResult {
	int status = 0;
	bool should_exit = false;
};

CommandResult handle_command(const std::string& input, int last_status);