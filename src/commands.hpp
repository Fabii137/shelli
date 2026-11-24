#pragma once

#include <string>
#include "commands/result.hpp"

CommandResult handle_command(const std::string& input, int last_status);
