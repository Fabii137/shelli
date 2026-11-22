#pragma once

#include <string>
#include <vector>
#include "commands/result.hpp"

bool is_builtin(const std::string& command);
CommandResult run_builtin(const std::vector<std::string>& args);